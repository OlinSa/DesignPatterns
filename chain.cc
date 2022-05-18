#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class AbstractLogger {
 public:
  static const int DEBUG_LEVEL;
  static const int INFO_LEVEL;
  static const int ERROR_LEVEL;

  void setNextLogger(std::shared_ptr<AbstractLogger> logger) {
    this->next_logger = logger;
  }
  void logMessage(int level, std::string message) {
    if (this->level <= level) {
      write(message);
    }
    if (next_logger != nullptr) {
      next_logger->logMessage(level, message);
    }
  }

  virtual void write(std::string message) = 0;

 protected:
  int level;

 private:
  std::shared_ptr<AbstractLogger> next_logger;
};

const int AbstractLogger::DEBUG_LEVEL = 1;
const int AbstractLogger::INFO_LEVEL = 2;
const int AbstractLogger::ERROR_LEVEL = 3;

class ConsoleLogger : public AbstractLogger {
 public:
  ConsoleLogger(int level) { this->level = level; }

  void write(std::string message) override {
    std::cout << "[" << level << "]"
              << " ConsoleLogger output<<" << message << std::endl;
  }
};

class ErrorLogger : public AbstractLogger {
 public:
  ErrorLogger(int level) { this->level = level; }

  void write(std::string message) override {
    std::cout << "[" << level << "]"
              << " ErrorLogger output<<" << message << std::endl;
  }
};

class FileLogger : public AbstractLogger {
 public:
  FileLogger(int level) { this->level = level; }

  void write(std::string message) override {
    std::cout << "[" << level << "]"
              << " FileLogger output<<" << message << std::endl;
  }
};

int main(int argc, char *argv[]) {
  std::shared_ptr<AbstractLogger> error_logger =
      std::make_shared<ErrorLogger>(AbstractLogger::ERROR_LEVEL);
  std::shared_ptr<AbstractLogger> file_logger =
      std::make_shared<FileLogger>(AbstractLogger::DEBUG_LEVEL);
  std::shared_ptr<AbstractLogger> console_logger =
      std::make_shared<ConsoleLogger>(AbstractLogger::INFO_LEVEL);

  error_logger->setNextLogger(file_logger);
  file_logger->setNextLogger(console_logger);

  std::shared_ptr<AbstractLogger> logger_chain = error_logger;
  logger_chain->logMessage(AbstractLogger::INFO_LEVEL,
                           "This is an information.");
  logger_chain->logMessage(AbstractLogger::DEBUG_LEVEL,
                           "This is a debug level information.");

  logger_chain->logMessage(AbstractLogger::ERROR_LEVEL,
                           "This is an error information.");

  return 0;
}