#include "Shop.h"
#include "Model.h"
#include <random>
#include <thread>
#include <future>

void Worker::Launch() {
  while (true) {
    std::poisson_distribution<unsigned int> Distribution(Rate);
    // TODO: Have all these as private fields?
    std::default_random_engine RandomEngine;
    // TODO: Learn multithreading :( Like, use atomics or something...
    {
      std::lock_guard<std::mutex>(this->Lock);
      if (TheState == ACCEPT)
        continue;
    }
    Model::DurationT Pause(Distribution(RandomEngine));
    std::this_thread::sleep_for(Pause);
    if (NextWorker) {
      std::lock_guard<std::mutex>(this->Lock);
      TheState = WAITING;
      do {} while (NextWorker->Submit() != ACCEPT);
    }
    {
      std::lock_guard<std::mutex>(this->Lock);
      TheState = ACCEPT;
    }
  }
}

Submittable::State Worker::Submit() {
  std::lock_guard<std::mutex>(this->Lock);
  if (TheState == ACCEPT) {
    TheState = BUSY;
    return ACCEPT;
  }
  return TheState;
}

void Shop::Launch() {
  std::thread FirstWorkerThread([&](){
    FirstWorker.Launch();
  });
  std::thread SecondWorkerThread([&](){
    SecondWorker.Launch();
  });
  FirstWorkerThread.detach();
  SecondWorkerThread.detach();
}

Submittable::State Shop::Submit() {
  return FirstWorker.Submit();
}
