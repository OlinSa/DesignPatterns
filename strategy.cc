#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Stragy {
 public:
  virtual int doOperation(int num1, int num2) = 0;
};

class OperationAdd : public Stragy {
 public:
  int doOperation(int num1, int num2) override { return num1 + num2; }
};

class OperationSubtract : public Stragy {
 public:
  int doOperation(int num1, int num2) override { return num1 - num2; }
};

class OperationMultiply : public Stragy {
 public:
  int doOperation(int num1, int num2) override { return num1 * num2; }
};

class Context {
 public:
  Context(std::shared_ptr<Stragy> strategy) { this->strategy = strategy; }

  int executeStrategy(int num1, int num2) {
    return strategy->doOperation(num1, num2);
  }

 private:
  std::shared_ptr<Stragy> strategy;
};

int main(int argc, char *argv[]) {
  std::cout << "10+5="
            << std::make_shared<Context>(std::make_shared<OperationAdd>())
                   ->executeStrategy(10, 5)
            << std::endl;
  std::cout << "10-5="
            << std::make_shared<Context>(std::make_shared<OperationSubtract>())
                   ->executeStrategy(10, 5)
            << std::endl;
  std::cout << "10*5="
            << std::make_shared<Context>(std::make_shared<OperationMultiply>())
                   ->executeStrategy(10, 5)
            << std::endl;
  return 0;
}