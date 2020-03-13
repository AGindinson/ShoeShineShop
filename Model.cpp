#include "Model.h"
#include "Shop.h"
#include <iostream>
#include <memory>
#include <random>
#include <thread>

Model::Model() : TheShop(std::make_unique<Shop>(
    Params.FirstChairRate, Params.SecondChairRate)) {}

Model::Model(ModelParams Params) : Params(std::move(Params)),
    TheShop(std::make_unique<Shop>(
        Params.FirstChairRate, Params.SecondChairRate)) {}

void Model::Execute(const DurationT &ExecutionDuration) {
  // TODO: See if the duplicating routine can be removed by
  //       inheriting Submittable yet again
  std::poisson_distribution<unsigned int> CustomerArrivalDist(
      Params.CustomerRate);
  std::default_random_engine RandomEngine;
  auto ExecutionEndTime = std::chrono::steady_clock::now() + ExecutionDuration;
  TheShop->Launch();
  do {
    DurationT CustomerArrivalInterval(CustomerArrivalDist(RandomEngine));
    std::this_thread::sleep_for(CustomerArrivalInterval);
    ++Records.TotalCustomerCount;
    if (TheShop->Submit() == Submittable::State::ACCEPT)
      ++Records.DeclinedCustomerCount;
  } while (std::chrono::steady_clock::now() < ExecutionEndTime);
}

void Model::PrintRecords() {
  std::cout << "Model records:\n";
  double DeclineRatio =
      Records.DeclinedCustomerCount / Records.TotalCustomerCount;
  std::cout << "Decline ratio: " << DeclineRatio << "\n";
}