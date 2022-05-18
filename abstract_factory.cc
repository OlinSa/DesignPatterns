#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Shape {
 public:
  virtual ~Shape() {}
  virtual void draw() = 0;
};

class Color {
 public:
  virtual ~Color() {}
  virtual void fill() = 0;
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

class Red : public Color {
 public:
  void fill() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};

class Green : public Color {
 public:
  void fill() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};

class Blue : public Color {
 public:
  void fill() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
};

class AbstractoryFactory {
 public:
  virtual shared_ptr<Color> getColor(std::string color) { return nullptr; }
  virtual shared_ptr<Shape> getShape(std::string shape) { return nullptr; }
};

class ShapeFactory : public AbstractoryFactory {
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

class ColorFactory : public AbstractoryFactory {
 public:
  shared_ptr<Color> getColor(std::string color) {
    if (color.empty()) {
      return nullptr;
    }
    if (0 == color.compare("Red")) {
      return std::make_shared<Red>();
    }
    if (0 == color.compare("Green")) {
      return std::make_shared<Green>();
    }
    if (0 == color.compare("Blue")) {
      return std::make_shared<Blue>();
    }
    return nullptr;
  }
};

class FactoryProducer {
 public:
  static std::shared_ptr<AbstractoryFactory> getFactory(
      std::string factory_name) {
    if (0 == factory_name.compare("Shape")) {
      return std::make_shared<ShapeFactory>();
    }
    if (0 == factory_name.compare("Color")) {
      return std::make_shared<ColorFactory>();
    }
    return nullptr;
  }
};

int main(int argc, char *argv[]) {
  std::shared_ptr<AbstractoryFactory> factory = nullptr;
  std::shared_ptr<Shape> shape = nullptr;
  std::shared_ptr<Color> color = nullptr;

  factory = FactoryProducer::getFactory("Shape");
  assert(factory != nullptr);
  shape = factory->getShape("Circle");
  assert(shape != nullptr);
  shape->draw();
  shape = factory->getShape("Rectangle");
  assert(shape != nullptr);
  shape->draw();
  shape = factory->getShape("Square");
  assert(shape != nullptr);
  shape->draw();

  factory = FactoryProducer::getFactory("Color");
  assert(factory != nullptr);
  color = factory->getColor("Red");
  assert(color != nullptr);
  color->fill();
  color = factory->getColor("Green");
  assert(color != nullptr);
  color->fill();
  color = factory->getColor("Blue");
  assert(color != nullptr);
  color->fill();

  return 0;
}