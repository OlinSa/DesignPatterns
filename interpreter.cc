#include <assert.h>

#include <iostream>
#include <memory>

using namespace std;

class Expression {
 public:
  virtual bool interpret(std::string context) = 0;
};
class TerminalExpression : public Expression {
 public:
  TerminalExpression(std::string data) { this->data = data; }
  bool interpret(std::string context) override {
    return std::string::npos != context.find(this->data);
  }

 private:
  std::string data;
};

class OrExpression : public Expression {
 public:
  OrExpression(std::shared_ptr<Expression> expr1,
               std::shared_ptr<Expression> expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
  }
  bool interpret(std::string context) override {
    return expr1->interpret(context) || expr2->interpret(context);
  }

 private:
  std::shared_ptr<Expression> expr1;
  std::shared_ptr<Expression> expr2;
};

class AndExpression : public Expression {
 public:
  AndExpression(std::shared_ptr<Expression> expr1,
                std::shared_ptr<Expression> expr2) {
    this->expr1 = expr1;
    this->expr2 = expr2;
  }
  bool interpret(std::string context) override {
    return expr1->interpret(context) && expr2->interpret(context);
  }

 private:
  std::shared_ptr<Expression> expr1;
  std::shared_ptr<Expression> expr2;
};

int main(int argc, char *argv[]) {
  std::shared_ptr<Expression> robert =
      std::make_shared<TerminalExpression>("Rober");
  std::shared_ptr<Expression> john =
      std::make_shared<TerminalExpression>("John");
  std::shared_ptr<Expression> isMale =
      std::make_shared<OrExpression>(robert, john);

  std::shared_ptr<Expression> julie =
      std::make_shared<TerminalExpression>("Julie");
  std::shared_ptr<Expression> married =
      std::make_shared<TerminalExpression>("Married");
  std::shared_ptr<Expression> isMarriedWoman =
      std::make_shared<AndExpression>(julie, married);

  std::cout << "John is male? " << isMale->interpret("John") << std::endl;
  std::cout << "Julie is a married women? "
            << isMarriedWoman->interpret("Married Julie") << std::endl;
  return 0;
}