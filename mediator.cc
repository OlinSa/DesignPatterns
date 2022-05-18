#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;
class User;
class ChatRoom {
 public:
  void static show(User* user, std::string message) {
    std::cout << "ChatRoot outmessage" << message << std::endl;
  }
};

class User {
 public:
  User(std::string name) { this->name = name; }
  void sendMessage(std::string message) { ChatRoom::show(this, message); }
  std::string getName() { return name; }

 private:
  std::string name;
};

int main(int argc, char* argv[]) {
  std::shared_ptr<User> rober = std::make_shared<User>("Robert");
  std::shared_ptr<User> john = std::make_shared<User>("John");

  rober->sendMessage("Hello");
  john->sendMessage("Hello");

  return 0;
}