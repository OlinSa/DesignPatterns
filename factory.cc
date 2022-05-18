#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Shape {
 public:
  virtual ~Shape() {}
  virtual void draw() = 0;
};

class Circle : public Shape {
 public:
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};
class Rectangle : public Shape {
 public:
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};
class Square : public Shape {
 public:
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};

class ShapeFactory {
 public:
  shared_ptr<Shape> getShape(std::string shape_type) {
    if (shape_type.empty()) {
      return nullptr;
    }
    if (0 == shape_type.compare("Circle")) {
      return std::make_shared<Circle>();
    }
    if (0 == shape_type.compare("Rectangle")) {
      return std::make_shared<Rectangle>();
    }
    if (0 == shape_type.compare("Square")) {
      return std::make_shared<Square>();
    }
    return nullptr;
  }
};

int main(int argc, char *argv[]) {
  ShapeFactory factory;
  std::shared_ptr<Shape> shape = nullptr;

  shape = factory.getShape("Circle");
  assert(shape != nullptr);
  shape->draw();
  shape = factory.getShape("Rectangle");
  assert(shape != nullptr);
  shape->draw();
  shape = factory.getShape("Square");
  assert(shape != nullptr);
  shape->draw();
  return 0;
}