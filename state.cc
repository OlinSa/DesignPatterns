#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class State;

class Context {
 public:
  void setState(State* state) { this->state = state; }

  State* getState() { return this->state; }

 private:
  State* state;
};

class State {
 public:
  virtual void doAction(std::shared_ptr<Context> context) = 0;
};

class StartState : public State {
 public:
  void doAction(std::shared_ptr<Context> context) {
    std::cout << "Player is in start state" << std::endl;
    context->setState(this);
  }
};

class StopState : public State {
 public:
  void doAction(std::shared_ptr<Context> context) {
    std::cout << "Player is in stop state" << std::endl;
    context->setState(this);
  }
};

int main(int argc, char* argv[]) {
  std::shared_ptr<Context> context = std::make_shared<Context>();

  std::shared_ptr<StartState> startState = std::make_shared<StartState>();
  std::shared_ptr<StopState> stopState = std::make_shared<StopState>();

  startState->doAction(context);
  std::cout << "state=" << context->getState() << std::endl;
  stopState->doAction(context);
  std::cout << "state=" << context->getState() << std::endl;
  return 0;
}