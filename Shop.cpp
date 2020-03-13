#include "Shop.h"
#include "Model.h"
#include <random>
#include <thread>
#include <future>

void Worker::Launch() {
  std::poisson_distribution<unsigned int> Distribution(Rate);
  // TODO: Have all these as private fields?
  std::default_random_engine RandomEngine;
  std::async([this, &Distribution, &RandomEngine]() {
    while (true) {
      // TODO: Learn multithreading :( Like, use atomics or something...
      {
        std::lock_guard<std::mutex>(this->Lock);
        if (TheState == ACCEPT) {
          continue;
        }
      }
      Model::DurationT Pause(Distribution(RandomEngine));
      std::this_thread::sleep_for(Pause);
      {
        std::lock_guard<std::mutex>(this->Lock);
        TheState == WAITING;
      }
    }
  });
}

Submittable::State Worker::Submit() {
  std::lock_guard<std::mutex>(this->Lock);
  if (TheState == ACCEPT) {
    TheState == BUSY;
    return ACCEPT;
  }
  return TheState;
}

void Shop::Launch() {
  FirstWorker.Launch();
  SecondWorker.Launch();
}

Submittable::State Shop::Submit() {
  auto FirstWorkerLoad = FirstWorker.Submit();
  if (FirstWorkerLoad == WAITING)
    SecondWorker.Submit();
  return FirstWorkerLoad;
}
