#ifndef SHOESHINESHOP_SHOP_H
#define SHOESHINESHOP_SHOP_H

#include <mutex>

class Submittable {
public:
  Submittable() : TheState(State::ACCEPT) {}
  enum State { ACCEPT, BUSY, WAITING };
  virtual State Submit() = 0;
  virtual void Launch() = 0;
protected:
  virtual ~Submittable() = default;
  State TheState;
  std::mutex Lock;
};

class Worker : public Submittable {
public:
  Worker() : Rate(0), NextWorker(nullptr) {}
  Worker(Worker *NextWorker = nullptr) : Rate(0), NextWorker(NextWorker) {}
  Worker(const unsigned int Rate, Worker *NextWorker = nullptr)
      : Rate(Rate), NextWorker(NextWorker) {}

  State Submit() override;
  void Launch() override;
  Worker *getNextWorker() { return NextWorker; }
private:
  const unsigned int Rate;
  Worker *NextWorker;
};

// TODO: Template away the magic number 2
class Shop : public Submittable {
public:
  Shop(const unsigned int FirstChairRate, const unsigned int SecondChairRate) :
      FirstWorker(FirstChairRate, &SecondWorker),
      SecondWorker(SecondChairRate) {}
  State Submit() override;
  void Launch() override;
private:
  Worker FirstWorker, SecondWorker;
};
#endif //SHOESHINESHOP_SHOP_H
