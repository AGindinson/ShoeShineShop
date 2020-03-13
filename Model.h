#ifndef SHOESHINESHOP_MODEL_H
#define SHOESHINESHOP_MODEL_H

#include "Shop.h"
#include <chrono>
#include <memory>

struct ModelParams {
  static constexpr unsigned int MagicDefaultRate = 1;
  unsigned int CustomerRate = MagicDefaultRate;
  unsigned int FirstChairRate = MagicDefaultRate;
  unsigned int SecondChairRate = MagicDefaultRate;
};

class Model {
public:
  Model();
  Model(ModelParams Params);

  using DurationT = std::chrono::duration<unsigned int>;
  void Execute(const DurationT &ExecutionDuration);
  void PrintRecords();

private:
  std::unique_ptr<Shop> TheShop;
  ModelParams Params;
  struct RecordStorage {
    unsigned int TotalCustomerCount = 0;
    unsigned int DeclinedCustomerCount = 0;
  } Records;
};

#endif //SHOESHINESHOP_MODEL_H
