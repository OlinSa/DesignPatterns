#include <assert.h>

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Iterator {
 public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
};

template <typename T>
class Container {
 public:
  virtual std::shared_ptr<Iterator<T>> getIterrator() = 0;
};

template <typename T>
class NameRespository : public Container<T> {
  template <typename S>
  friend class NameIterator;

 public:
  std::shared_ptr<Iterator<T>> getIterrator() override {
    return std::make_shared<NameIterator<T>>(this);
  }
  template <typename S>
  class NameIterator : public Iterator<S> {
   public:
    NameIterator(NameRespository* c) : index(0), contain(c) {}
    bool hasNext() override {
      if (!contain) return false;
      return index < contain->names.size();
    }
    S next() override {
      if (hasNext()) {
        return contain->names.at(index++);
      }
      return T();
    }

   private:
    unsigned int index = 0;
    NameRespository* contain;
  };

 private:
  std::vector<std::string> names = {"Robert", "John", "Julie", "Lora"};
};

int main(int argc, char* argv[]) {
  std::shared_ptr<NameRespository<std::string>> namerepo =
      std::make_shared<NameRespository<std::string>>();
  std::shared_ptr<Iterator<std::string>> iter = namerepo->getIterrator();
  for (std::shared_ptr<Iterator<std::string>> iter = namerepo->getIterrator();
       iter->hasNext();) {
    std::string o = iter->next();
    std::cout << o << std::endl;
  }

  return 0;
}