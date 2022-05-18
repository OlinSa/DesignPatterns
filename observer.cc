#include <assert.h>

#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Observer {
 public:
  virtual void update(int state) {}
};

class Subject {
 public:
  void setState(int state) { notifyAllObservers(state); }
  void addObserver(std::shared_ptr<Observer> obj) { observers.push_back(obj); }

 private:
  void notifyAllObservers(int state) {
    for (std::shared_ptr<Observer> o : observers) {
      o->update(state);
    }
  }
  std::list<shared_ptr<Observer>> observers;
};

class BinaryObserver : public Observer {
 public:
  void update(int state) {
    std::cout << "BinaryObserver received message: state=" << state
              << std::endl;
  }
};
class OctalObserver : public Observer {
 public:
  void update(int state) {
    std::cout << "OctalObserver received message: state=" << state << std::endl;
  }
};
class HexObserver : public Observer {
 public:
  void update(int state) {
    std::cout << "HexObserver received message: state=" << state << std::endl;
  }
};

int main(int argc, char *argv[]) {
  std::shared_ptr<Subject> sub = std::make_shared<Subject>();
  sub->addObserver(std::make_shared<BinaryObserver>());
  sub->addObserver(std::make_shared<OctalObserver>());
  sub->addObserver(std::make_shared<HexObserver>());

  sub->setState(1);
  return 0;
}