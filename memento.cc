#include <assert.h>

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Memento {
 public:
  Memento(std::string state) { this->state = state; }
  std::string getState() { return this->state; }

 private:
  std::string state;
};

class Originator {
 public:
  Memento saveStateoMemento() { return Memento(state); }
  void getStateFromMemento(Memento menento) { state = menento.getState(); }

  std::string getState() { return state; }
  void setState(std::string state) { this->state = state; }

 private:
  std::string state;
};

class CareTaker {
 public:
  void add(const Memento& memo) { memos.push_back(memo); }
  Memento get(int index) { return memos.at(index); }

 private:
  std::vector<Memento> memos;
};

int main(int argc, char* argv[]) {
  std::shared_ptr<Originator> originator = std::make_shared<Originator>();
  std::shared_ptr<CareTaker> careTaker = std::make_shared<CareTaker>();
  originator->setState("State #1");
  originator->setState("State #2");
  careTaker->add(originator->saveStateoMemento());
  originator->setState("State #3");
  careTaker->add(originator->saveStateoMemento());
  originator->setState("State #4");

  std::cout << "Current state:" + originator->getState() << std::endl;
  originator->getStateFromMemento(careTaker->get(0));
  std::cout << "First saved state:" + originator->getState() << std::endl;
  originator->getStateFromMemento(careTaker->get(1));
  std::cout << "Second saved state:" + originator->getState() << std::endl;
  return 0;
}