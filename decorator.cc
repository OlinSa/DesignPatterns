#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Shape {
 public:
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

class ShapeDecorator : public Shape {
 public:
  ShapeDecorator(std::shared_ptr<Shape> shapeDecorator) {
    this->shapeDecorator = shapeDecorator;
  }
  void draw() override { shapeDecorator->draw(); }

 protected:
  std::shared_ptr<Shape> shapeDecorator;
};

class RedShapeDecorator : public ShapeDecorator {
 public:
  RedShapeDecorator(std::shared_ptr<Shape> shapeDecorator)
      : ShapeDecorator(shapeDecorator) {}
  void draw() override {
    shapeDecorator->draw();
    setRedBorder(shapeDecorator);
  }
  void setRedBorder(std::shared_ptr<Shape> decorateShape) {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};

int main(int argc, char* argv[]) {
  std::shared_ptr<Shape> circle = std::make_shared<Circle>();
  std::shared_ptr<Shape> rectangle = std::make_shared<Rectangle>();
  std::shared_ptr<ShapeDecorator> red_circle =
      std::make_shared<RedShapeDecorator>(circle);
  std::shared_ptr<ShapeDecorator> red_rectangle =
      std::make_shared<RedShapeDecorator>(rectangle);

  std::cout << "Circle with normal border" << std::endl;
  circle->draw();
  std::cout << "Circle with red border" << std::endl;
  red_circle->draw();
  std::cout << "Circle with red rectangle" << std::endl;
  red_rectangle->draw();
  return 0;
}