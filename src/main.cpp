#include <iostream>

#include "hello.h"

int main() {
	std::cout<< "Version: " <<hello::version()<< "\n";
	hello::greetings(std::cout);
}
