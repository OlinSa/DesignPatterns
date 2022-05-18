#include <assert.h>

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Computer;
class Mouse;
class Keyboard;
class Monitor;
class ComputerPartVisitor {
 public:
  virtual void visit(std::shared_ptr<Computer> computer) = 0;
  virtual void visit(std::shared_ptr<Mouse> mouse) = 0;
  virtual void visit(std::shared_ptr<Keyboard> keyboard) = 0;
  virtual void visit(std::shared_ptr<Monitor> monitor) = 0;
  virtual ~ComputerPartVisitor() = default;
};

class ComputerPartDisplayVisitor : public ComputerPartVisitor {
 public:
  virtual void visit(std::shared_ptr<Computer> computer) override {
    std::cout << "Displaying Computer." << std::endl;
  }
  virtual void visit(std::shared_ptr<Mouse> mouse) override {
    std::cout << "Displaying Mouse." << std::endl;
  }
  virtual void visit(std::shared_ptr<Keyboard> keyboard) override {
    std::cout << "Displaying Keyboard." << std::endl;
  }
  virtual void visit(std::shared_ptr<Monitor> monitor) override {
    std::cout << "Displaying Monitor." << std::endl;
  }
};

class ComputerPart {
 public:
  virtual void accept(
      std::shared_ptr<ComputerPartVisitor> computerPartVisitor) = 0;
  virtual ~ComputerPart() = default;
};

class Keyboard : public ComputerPart {
 public:
  virtual void accept(
      std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override {
    computerPartVisitor->visit(std::make_shared<Keyboard>(*this));
  }
};

class Monitor : public ComputerPart {
 public:
  virtual void accept(
      std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override {
    computerPartVisitor->visit(std::make_shared<Monitor>(*this));
  }
};

class Mouse : public ComputerPart {
 public:
  virtual void accept(
      std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override {
    computerPartVisitor->visit(std::make_shared<Mouse>(*this));
  }
};

class Computer : public ComputerPart {
 public:
  virtual void accept(
      std::shared_ptr<ComputerPartVisitor> computerPartVisitor) override {
    vector<std::shared_ptr<ComputerPart>> parts = {std::make_shared<Mouse>(),
                                                   std::make_shared<Keyboard>(),
                                                   std::make_shared<Monitor>()};
    for (const auto& part : parts) {
      part->accept(computerPartVisitor);
    }
    computerPartVisitor->visit(std::make_shared<Computer>(*this));
  }
};

int main(int argc, char* argv[]) {
  std::shared_ptr<ComputerPart> computer = std::make_shared<Computer>();
  computer->accept(std::make_shared<ComputerPartDisplayVisitor>());
}