#include "hello.h"

std::ostream &hello::greetings(std::ostream &out) {
  return out << "Hello, world!";
}

std::string hello::version() { return std::string(PROJECT_VERSION); }
