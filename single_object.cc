#include <assert.h>

#include <iostream>
#include <memory>
#include <mutex>

using namespace std;

class SingeleObject {
 public:
  static SingeleObject* getInstance() {
    if (SingeleObject::instance == nullptr) {
      SingeleObject::mtx.lock();
      if (SingeleObject::instance == nullptr) {
        SingeleObject::instance = new SingeleObject();
      }
      SingeleObject::mtx.unlock();
    }
    return SingeleObject::instance;
  }
  void showMessage() {
    std::cout << typeid(*this).name() << ":" << __FUNCTION__ << std::endl;
  }
  static SingeleObject* instance;
  static std::mutex mtx;

 private:
  SingeleObject() {}
  ~SingeleObject() {}
};
SingeleObject* SingeleObject::instance = nullptr;
std::mutex SingeleObject::mtx;

int main(int argc, char* argv[]) {
  SingeleObject* obj = SingeleObject::getInstance();
  obj->showMessage();
  return 0;
}