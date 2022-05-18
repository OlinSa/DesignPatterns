#include <assert.h>

#include <iostream>
#include <list>
#include <memory>
using namespace std;

class Employee {
 public:
  Employee(std::string name, std::string dept, int salary) {
    this->name = name;
    this->dept = dept;
    this->salary = salary;
  }
  void add(std::shared_ptr<Employee> e) { subdrinates.push_back(e); }
  void remove(std::shared_ptr<Employee> e) { subdrinates.remove(e); }
  std::list<shared_ptr<Employee>> getSubOrdinates() { return subdrinates; }
  void print() {
    std::cout << "name:" + name + ",dept:" << dept << ",salary:" << salary
              << std::endl;
  }

 private:
  std::string name;
  std::string dept;
  int salary;
  std::list<shared_ptr<Employee>> subdrinates;
};

int main(int argc, char *argv[]) {
  std::shared_ptr<Employee> ceo =
      std::make_shared<Employee>("John", "CEO", 30000);
  std::shared_ptr<Employee> head_sales =
      std::make_shared<Employee>("Robert", "Head Sales", 20000);
  std::shared_ptr<Employee> head_marketing =
      std::make_shared<Employee>("Michel", "Head Marketing", 20000);
  std::shared_ptr<Employee> clerk1 =
      std::make_shared<Employee>("Laura", "Maretking", 10000);
  std::shared_ptr<Employee> clerk2 =
      std::make_shared<Employee>("Bob", "Mareting", 10000);
  std::shared_ptr<Employee> salesExecutive1 =
      std::make_shared<Employee>("Richard", "Sales", 10000);
  std::shared_ptr<Employee> salesExecutive2 =
      std::make_shared<Employee>("Rob", "Sales", 10000);

  ceo->add(head_sales);
  ceo->add(head_marketing);

  head_sales->add(salesExecutive1);
  head_sales->add(salesExecutive2);

  head_marketing->add(clerk1);
  head_marketing->add(clerk2);

  ceo->print();
  for (std::shared_ptr<Employee> head_employee : ceo->getSubOrdinates()) {
    std::cout << "  ";
    head_employee->print();
    for (std::shared_ptr<Employee> e : head_employee->getSubOrdinates()) {
      std::cout << "    ";
      e->print();
    }
    std::cout << std::endl;
  }

  return 0;
}