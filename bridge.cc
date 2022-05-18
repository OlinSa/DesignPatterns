#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class DrawAPI {
 public:
  virtual void drawCircle(int radius, int x, int y) = 0;
};

class RedCircle : public DrawAPI {
 public:
  void drawCircle(int radius, int x, int y) override {
    std::cout << "Draw red circle! x=" << x << " y=" << y
              << " radius=" << radius << std::endl;
  }
};

class GreenCircle : public DrawAPI {
 public:
  void drawCircle(int radius, int x, int y) override {
    std::cout << "Draw green circle! x=" << x << " y=" << y
              << " radius=" << radius << std::endl;
  }
};

class Shape {
 public:
  Shape(DrawAPI* drawAPI) { this->drawAPI = drawAPI; }
  virtual ~Shape() {}
  virtual void draw() = 0;

 protected:
  DrawAPI* drawAPI;
};

class Circle : public Shape {
 public:
  Circle(int radius, int x, int y, DrawAPI* drawAPI) : Shape(drawAPI) {
    this->radius = radius;
    this->x = x;
    this->y = y;
  }
  void draw() override { drawAPI->drawCircle(radius, x, y); }

 private:
  int radius;
  int x;
  int y;
};

int main(int argc, char* argv[]) {
  RedCircle redDrawApi;
  GreenCircle greenDrawApi;
  Shape* redCircle = new Circle(100, 100, 10, &redDrawApi);
  Shape* greenCircle = new Circle(100, 100, 10, &greenDrawApi);

  redCircle->draw();
  greenCircle->draw();

  delete redCircle;
  delete greenCircle;
  return 0;
}