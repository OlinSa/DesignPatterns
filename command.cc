#include <assert.h>

#include <iostream>
#include <list>
#include <memory>

using namespace std;

class Order {
 public:
  virtual void execute() = 0;
};

class Stock {
 public:
  void buy() {
    std::cout << "Stock [ Name: " << name << ", Qantity: " << quantity
              << " ] bought" << std::endl;
  }
  void sell() {
    std::cout << "Stock [ Name: " << name << ", Qantity: " << quantity
              << " ] Sold" << std::endl;
  }

 private:
  std::string name = "ABC";
  int quantity = 10;
};

class BuyStock : public Order {
 public:
  BuyStock(std::shared_ptr<Stock> stock) { this->stock = stock; }
  void execute() override { this->stock->buy(); }

 private:
  std::shared_ptr<Stock> stock;
};

class SellStock : public Order {
 public:
  SellStock(std::shared_ptr<Stock> stock) { this->stock = stock; }
  void execute() override { this->stock->sell(); }

 private:
  std::shared_ptr<Stock> stock;
};

class Broker {
 public:
  void takeOrder(std::shared_ptr<Order> order) { order_list.push_back(order); }
  void placeOrders() {
    for (std::shared_ptr<Order> order : order_list) {
      order->execute();
    }
    order_list.clear();
  }

 private:
  std::list<std::shared_ptr<Order>> order_list;
};

int main(int argc, char *argv[]) {
  std::shared_ptr<Stock> stock = std::make_shared<Stock>();

  std::shared_ptr<BuyStock> buystock_order = std::make_shared<BuyStock>(stock);
  std::shared_ptr<SellStock> sellstock_order =
      std::make_shared<SellStock>(stock);

  std::shared_ptr<Broker> broker = std::make_shared<Broker>();
  broker->takeOrder(buystock_order);
  broker->takeOrder(sellstock_order);

  broker->placeOrders();

  return 0;
}