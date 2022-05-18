#include <assert.h>

#include <iostream>
#include <list>
#include <memory>
using namespace std;

class Packing {
 public:
  virtual std::string pack() = 0;
};

class Item {
 public:
  virtual std::string name() = 0;
  virtual std::shared_ptr<Packing> pacing() = 0;
  virtual float price() = 0;
};

class Wrapper : public Packing {
 public:
  std::string pack() { return "Wrapper"; }
};

class Bottle : public Packing {
 public:
  std::string pack() { return "Bottle"; }
};

class Burger : public Item {
 public:
  std::shared_ptr<Packing> pacing() { return std::make_shared<Wrapper>(); }
};

class ColdDrink : public Item {
 public:
  std::shared_ptr<Packing> pacing() { return std::make_shared<Bottle>(); }
};

class VegBurger : public Burger {
 public:
  std::string name() override { return "VegBurger"; }

  float price() override { return 25.0f; }
};

class ChickenBurger : public Burger {
 public:
  std::string name() override { return "ChickenBurger"; }

  float price() override { return 50.5f; }
};

class Coke : public ColdDrink {
 public:
  std::string name() override { return "Coke"; }

  float price() override { return 30.0f; }
};

class Pepsi : public ColdDrink {
 public:
  std::string name() override { return "Pepsi"; }

  float price() override { return 35.0f; }
};

class Meal {
 public:
  void addItem(std::shared_ptr<Item> item) { items.push_back(item); }
  float getCost() {
    float cost = 0.0f;
    for (std::shared_ptr<Item> item : items) {
      cost += item->price();
    }
    return cost;
  }
  void showItem() {
    for (std::shared_ptr<Item> item : items) {
      std::cout << "Item:" + item->name();
      std::cout << ",Packing:" + item->pacing()->pack();
      std::cout << ", Price:" << item->price() << std::endl;
    }
  }

 private:
  std::list<std::shared_ptr<Item>> items;
};

class MealBuilder {
 public:
  std::shared_ptr<Meal> prepareVegMeal() {
    std::shared_ptr<Meal> meal = std::make_shared<Meal>();
    meal->addItem(std::make_shared<VegBurger>());
    meal->addItem(std::make_shared<Coke>());
    return meal;
  }
  std::shared_ptr<Meal> prepareNonVegmeal() {
    std::shared_ptr<Meal> meal = std::make_shared<Meal>();
    meal->addItem(std::make_shared<ChickenBurger>());
    meal->addItem(std::make_shared<Pepsi>());
    return meal;
  }
};

int main(int argc, char* argv[]) {
  MealBuilder meal_builder;
  std::shared_ptr<Meal> vegMeal = meal_builder.prepareVegMeal();
  std::cout << "Veg Meal! cost=" << vegMeal->getCost() << std::endl;
  vegMeal->showItem();

  std::shared_ptr<Meal> non_vegMeal = meal_builder.prepareNonVegmeal();
  std::cout << "Non Veg Meal! cost=" << non_vegMeal->getCost() << std::endl;
  non_vegMeal->showItem();
  return 0;
}