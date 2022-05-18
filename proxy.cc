#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Image {
 public:
  virtual void display() = 0;
};

class RealImage : public Image {
 public:
  RealImage(std::string filename) {
    this->filename = filename;
    loadFromDisk(filename);
  }
  void display() override {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }

 private:
  void loadFromDisk(std::string filename) {
    std::cout << "Load " + filename + "from disk" << std::endl;
  }
  std::string filename;
};

class ProxyImage : public Image {
 public:
  ProxyImage(std::string filename) {
    real_image = std::make_shared<RealImage>(filename);
  }
  void display() override { real_image->display(); }

 private:
  std::shared_ptr<RealImage> real_image;
};

int main(int argc, char *argv[]) {
  std::shared_ptr<Image> image = std::make_shared<ProxyImage>("test_10msb.jpg");
  image->display();

  return 0;
}