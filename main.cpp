#include "Model.h"
#include <iostream>

int main() {
  ModelParams InputParams;

  std::cout << "Enter the expected customer arrival rate:\n";
  std::cin >> InputParams.CustomerRate;
  std::cout << "Enter the expected first chair job completion rate:\n";
  std::cin >> InputParams.FirstChairRate;
  std::cout << "Enter the expected second chair job completion rate:\n";
  std::cin >> InputParams.SecondChairRate;

  Model TheModel(std::move(InputParams));
  // TODO: Accept the time as an argument
  const Model::DurationT Duration(60);
  TheModel.Execute(Duration);
  TheModel.PrintRecords();
  return 0;
}
