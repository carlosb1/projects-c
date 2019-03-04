#include "models.h"
#include <iostream>

int main() {
	Message message{std::string("hello world")};
	std::cout << message.getOperation();
}
