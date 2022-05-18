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

class ShapeMarker {
 public:
  ShapeMarker() {
    circle = std::make_shared<Circle>();
    rectangle = std::make_shared<Rectangle>();
    square = std::make_shared<Square>();
  }
  void drawCircle() { circle->draw(); }
  void drawRectangle() { rectangle->draw(); }
  void drawSquare() { square->draw(); }

 private:
  std::shared_ptr<Shape> circle;
  std::shared_ptr<Shape> rectangle;
  std::shared_ptr<Shape> square;
};

int main(int argc, char* argv[]) {
  ShapeMarker marker;
  marker.drawCircle();
  marker.drawRectangle();
  marker.drawSquare();
  return 0;
}