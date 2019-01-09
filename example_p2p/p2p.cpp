#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
#include <utility>

struct Node {
	std::size_t my_id;
	std::size_t successor_id;
	std::size_t predecessor_id;
	std::string name;
	Node(const std::string & name) {
		this->name = name;
		this->my_id = std::hash<std::string>{}(name);
		this->successor_id = 0;
		this->predecessor_id = 0;
	
	}
	Node() {
		this->my_id = 0;
		this->successor_id = 0;
		this->predecessor_id = 0;
	}
	
};

// Adding operators
std::ostream & operator<< (std::ostream  &strm, const Node &node) {
		return strm << "Node( my_id="<< node.my_id << " successor_id="<< node.successor_id<< " predecessor_id="<<node.predecessor_id<< ")";
}



class App {
	private:
		std::shared_ptr<Node> first; 
		std::unordered_map<std::size_t,std::shared_ptr<Node>> nodes;
	public:
		inline std::shared_ptr<Node> getFirst() {
			return this->first;
		}
		inline std::unordered_map<std::size_t,std::shared_ptr<Node>> getNodes()  {
			return this->nodes;
		}
		App() {
			//this->first =  std::make_shared<Node>();
		
		};
		void join(const Node & node) {
			auto node_to_save = std::make_shared<Node>(node);	
			std::cout <<"##############################\n";
			//TODO change for an empty 
			if (!this->first.get()) {
				this->first = node_to_save;
				this->nodes[node.my_id] = node_to_save;
			
				std::clog << "my id is :"<< node_to_save->my_id << "\n";
				std::clog << "my predecessor_id is :"<< node_to_save->predecessor_id << "\n";
				std::clog << "my successor_id is :"<< node_to_save->successor_id << "\n";
				return;
			}
			if (nodes.find(node.my_id) != nodes.end()) {
					std::clog << "It was added the node\n";
					return;
			}
			std::pair<bool, std::shared_ptr<Node>> result_search = this->search(node_to_save);
			
			auto found = result_search.first;
			auto possible_successor = result_search.second;
			
			std::clog << "It founds my successor: "<< found <<"\n";
			if (!found) {
				assert(possible_successor->successor_id == 0);
				possible_successor->successor_id = node_to_save->my_id;
				node_to_save->predecessor_id = possible_successor->my_id;
			}
			else {
				//Check if it is the first node
				if (possible_successor->predecessor_id != 0) {
					auto predecessor_node = this->nodes[possible_successor->predecessor_id];
					predecessor_node->successor_id = node_to_save->my_id;
				} else {
					this->first = node_to_save;
				}
				auto old_predecesor_id = possible_successor->predecessor_id;
				possible_successor->predecessor_id = node_to_save->my_id;
				node_to_save->predecessor_id = old_predecesor_id;
				node_to_save->successor_id = possible_successor->my_id;	
			}
			
			std::clog << "my id is :"<< node_to_save->my_id << "\n";
			std::clog << "my predecessor_id is :"<< node_to_save->predecessor_id << "\n";
			std::clog << "my successor_id is :"<< node_to_save->successor_id << "\n";

			this->nodes[node.my_id] = node_to_save;
		}

		std::pair<bool, std::shared_ptr<Node>> search(std::shared_ptr<Node> & node_to_search) {
			auto id_to_search = (*node_to_search).my_id;
			
			auto node_to_compare = this->first;
			while (node_to_compare->my_id < node_to_search->my_id) {
					if (node_to_compare->successor_id == 0) {
						 break;
					}
					node_to_compare = this->nodes[node_to_compare->successor_id]; 
			}
			if (node_to_compare->my_id < node_to_search->my_id) {
				return std::make_pair(false, node_to_compare);
			} else {
				return std::make_pair(true, node_to_compare);
			}
		}
};	

int main () {
	Node node("hello world");
	Node node2("hello world1");
	Node node3("hello world2");
	Node node4("hello world3");
	Node node5("hello world4");
	App app;
	app.join(node);	
	app.join(node2);	
	app.join(node3);	
	app.join(node4);	
	app.join(node5);	
	
	std::cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	auto toNode = app.getFirst();
	bool exit = false;
	while (!exit) {
		std::cout << *toNode << "\n";
		std::cout <<"--------------------------\n";
		if (toNode->successor_id == 0) {
			break;
		}
		toNode = app.getNodes()[toNode->successor_id];
	}

}
