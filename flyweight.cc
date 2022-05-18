#include <assert.h>

#include <iostream>
#include <map>
#include <memory>

using namespace std;

class Shape {
 public:
  virtual void draw() = 0;
};

class Circle : public Shape {
 public:
  Circle(std::string color) { this->color = color; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
  void setRadius(int radius) { this->radius = radius; }
  void draw() override {
    std::cout << "draw circle!color" << color << " (x=" << x << ",y=" << y
              << ")"
              << " r=" << radius << std::endl;
  }

 private:
  std::string color;
  int x, y, radius;
};

class ShapeFacotry {
 public:
  static std::shared_ptr<Circle> getCorcle(std::string color) {
    std::shared_ptr<Circle> circle = circle_map.find(color) != circle_map.end()
                                         ? circle_map[color]
                                         : nullptr;
    if (circle == nullptr) {
      circle = std::make_shared<Circle>(color);
      circle_map[color] = circle;
      std::cout << "create color=" << color << std::endl;
    }
    return circle;
  }

 private:
  static std::map<std::string, std::shared_ptr<Circle>> circle_map;
};

std::map<std::string, std::shared_ptr<Circle>> ShapeFacotry::circle_map;

int main(int argc, char* argv[]) {
  std::string colors[] = {"Red", "Green", "Blue", "White", "Black"};
  for (int i = 0; i < 20; i++) {
    std::shared_ptr<Circle> circle =
        ShapeFacotry::getCorcle(colors[i % (colors->length())]);
    circle->setX(i);
    circle->setY(i);
    circle->setRadius(100);
    circle->draw();
  }
  return 0;
}