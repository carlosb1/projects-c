#include <iostream>
#include <functional>


struct Node {
	std::size_t my_id;
	std::size_t successor_id;
	std::size_t predecessor_id;
	Node(const std::string & name) {
		this->my_id = std::hash<std::string>{}(name);
	}
	
};

int main () {
	Node node("hello world");
	std::cout << "My hash: "<<(node).my_id;
}
