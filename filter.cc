#include <assert.h>

#include <algorithm>  // std::find
#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Person {
 public:
  Person(std::string name, std::string gender, std::string marital_status) {
    this->name = name;
    this->gender = gender;
    this->marital_status = marital_status;
  }
  Person(const Person& person) {
    this->name = person.name;
    this->gender = person.gender;
    this->marital_status = person.marital_status;
  }
  bool operator==(const Person& persion) {
    return (!this->name.compare(persion.name)) &&
           (!this->gender.compare(persion.gender)) &&
           (!this->marital_status.compare(persion.marital_status));
  }

  std::string name;
  std::string gender;
  std::string marital_status;
};

class Criteria {
 public:
  virtual std::list<Person> meetCriteria(std::list<Person> persions) {
    return std::list<Person>();
  }
};

class CirteriaMale : public Criteria {
 public:
  std::list<Person> meetCriteria(std::list<Person> persons) override {
    std::list<Person> l;
    for (Person person : persons) {
      if (0 == person.gender.compare("Male")) {
        l.push_back(person);
      }
    }
    return l;
  }
};

class CirteriaFemale : public Criteria {
 public:
  std::list<Person> meetCriteria(std::list<Person> persons) override {
    std::list<Person> l;
    for (Person person : persons) {
      if (0 == person.gender.compare("Female")) {
        l.push_back(person);
      }
    }
    return l;
  }
};

class CirteriaSingle : public Criteria {
 public:
  std::list<Person> meetCriteria(std::list<Person> persons) override {
    std::list<Person> l;
    for (Person person : persons) {
      if (0 == person.marital_status.compare("Single")) {
        l.push_back(person);
      }
    }
    return l;
  }
};

class AndCriteria : public Criteria {
 public:
  AndCriteria(std::shared_ptr<Criteria> criteria,
              std::shared_ptr<Criteria> other_criteria) {
    this->criteria = criteria;
    this->other_criteria = other_criteria;
  }

  std::list<Person> meetCriteria(std::list<Person> persons) override {
    std::list<Person> firstCriteriaPersion = criteria->meetCriteria(persons);
    return other_criteria->meetCriteria(firstCriteriaPersion);
  }

 private:
  std::shared_ptr<Criteria> criteria;
  std::shared_ptr<Criteria> other_criteria;
};

class OrCriteria : public Criteria {
 public:
  OrCriteria(std::shared_ptr<Criteria> criteria,
             std::shared_ptr<Criteria> other_criteria) {
    this->criteria = criteria;
    this->other_criteria = other_criteria;
  }

  std::list<Person> meetCriteria(std::list<Person> persons) override {
    std::list<Person> firstCriteriaPersion = criteria->meetCriteria(persons);
    std::list<Person> otherCriteriaPersion =
        other_criteria->meetCriteria(persons);

    for (Person person : otherCriteriaPersion) {
      auto it = std::find(firstCriteriaPersion.begin(),
                          firstCriteriaPersion.end(), person);
      if (it == firstCriteriaPersion.end()) {
        firstCriteriaPersion.push_back(person);
      }
    }
    return firstCriteriaPersion;
  }

 private:
  std::shared_ptr<Criteria> criteria;
  std::shared_ptr<Criteria> other_criteria;
};

void printPerson(const list<Person>& persons) {
  for (Person person : persons) {
    std::cout << "Person:[Name:" + person.name + ", Gender:" + person.gender +
                     ", marital status:" + person.marital_status + "]"
              << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char* argv[]) {
  list<Person> persons;
  persons.push_back(Person("Robert", "Male", "Single"));
  persons.push_back(Person("John", "Male", "Married"));
  persons.push_back(Person("Laura", "Female", "Married"));
  persons.push_back(Person("Diana", "Female", "Single"));
  persons.push_back(Person("Mike", "Male", "Single"));
  persons.push_back(Person("Bobby", "Male", "Single"));

  std::shared_ptr<Criteria> male = std::make_shared<CirteriaMale>();
  std::shared_ptr<Criteria> female = std::make_shared<CirteriaFemale>();
  std::shared_ptr<Criteria> single = std::make_shared<CirteriaSingle>();
  std::shared_ptr<Criteria> singleMale =
      std::make_shared<AndCriteria>(single, male);
  std::shared_ptr<Criteria> singleOrFemale =
      std::make_shared<OrCriteria>(single, female);

  std::cout << "Males:" << std::endl;
  printPerson(male->meetCriteria(persons));

  std::cout << "Females:" << std::endl;
  printPerson(female->meetCriteria(persons));

  std::cout << "singleMale:" << std::endl;
  printPerson(singleMale->meetCriteria(persons));

  std::cout << "singleOrFemale:" << std::endl;
  printPerson(singleOrFemale->meetCriteria(persons));

  return 0;
}