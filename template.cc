#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Game {
 public:
  virtual void initialize() = 0;
  virtual void startPlay() = 0;
  virtual void stopPlay() = 0;
  void play() {
    initialize();
    startPlay();
    stopPlay();
  }
};

class Cricket : public Game {
 public:
  void initialize() override { std::cout << "Cricket initialize" << std::endl; }
  void startPlay() override { std::cout << "Cricket startPlay" << std::endl; }
  void stopPlay() override { std::cout << "Cricket stopPlay" << std::endl; }
};

class FootBall : public Game {
 public:
  void initialize() override {
    std::cout << "FootBall initialize" << std::endl;
  }
  void startPlay() override { std::cout << "FootBall startPlay" << std::endl; }
  void stopPlay() override { std::cout << "FootBall stopPlay" << std::endl; }
};

int main(int argc, char* argv[]) {
  std::shared_ptr<Game> game = std::make_shared<Cricket>();
  game->play();
  game = std::make_shared<FootBall>();
  game->play();
  return 0;
}