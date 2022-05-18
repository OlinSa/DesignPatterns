#include <assert.h>

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Shape {
 public:
  virtual void draw() = 0;
  virtual Shape* clone() = 0;

  std::string getType() { return this->type; }

  std::string getId() { return this->id; }

  void setId(std::string id) { this->id = id; }

 protected:
  std::string type;

 private:
  std::string id;
};

class Rectangle : public Shape {
 public:
  Rectangle() { type = "Rectangle"; }
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
  Shape* clone() override { return new Rectangle(*this); }
};

class Square : public Shape {
 public:
  Square() { type = "Square"; }
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
  Shape* clone() override { return new Square(*this); }
};

class Circle : public Shape {
 public:
  Circle() { type = "Circle"; }
  void draw() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
  Shape* clone() override { return new Circle(*this); }
};

class ShapeCache {
 public:
  static Shape* getShape(std::string shape_id) {
    auto it = ShapeCache::shape_map.find(shape_id);
    return it != shape_map.end() ? it->second->clone() : nullptr;
  }
  static void loadCache() {
    shared_ptr<Circle> circle = std::make_shared<Circle>();
    circle->setId("1");
    ShapeCache::shape_map.insert(std::pair<std::string, std::shared_ptr<Shape>>(
        circle->getId(), circle));

    shared_ptr<Square> square = std::make_shared<Square>();
    square->setId("2");
    ShapeCache::shape_map.insert(std::pair<std::string, std::shared_ptr<Shape>>(
        square->getId(), square));

    shared_ptr<Rectangle> rectangle = std::make_shared<Rectangle>();
    rectangle->setId("3");
    ShapeCache::shape_map.insert(std::pair<std::string, std::shared_ptr<Shape>>(
        rectangle->getId(), rectangle));
  }

 private:
  static std::map<std::string, std::shared_ptr<Shape>> shape_map;
};

std::map<std::string, std::shared_ptr<Shape>> ShapeCache::shape_map;

int main(int argc, char* argv[]) {
  ShapeCache::loadCache();
  Shape* sp10 = ShapeCache::getShape("1");
  Shape* sp11 = ShapeCache::getShape("1");
  Shape* sp20 = ShapeCache::getShape("2");

  std::cout << "sp10(" << sp10 << ")"
            << " type=" << sp10->getId() << " id=" << sp10->getId()
            << std::endl;
  std::cout << "sp11(" << sp11 << ")"
            << " type=" << sp11->getId() << " id=" << sp11->getId()
            << std::endl;
  std::cout << "sp20(" << sp20 << ")"
            << " type=" << sp20->getId() << " id=" << sp20->getId()
            << std::endl;

  return 0;
}