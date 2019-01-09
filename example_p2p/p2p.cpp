#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
#include <utility>
#include <bitset>
#include <limits>


class Node {
	public: 
		std::size_t my_id;
		std::vector<std::size_t> finger_table;
		std::size_t predecessor_id;
		std::string name;
		Node(const std::string & name) {
			this->name = name;
			this->my_id = std::hash<std::string>{}(name);
			this->predecessor_id = 0;
			this->finger_table.push_back(0);
	
		}
		Node() {
			this->my_id = 0;
			this->predecessor_id = 0;
			this->finger_table.push_back(0);
		}
	
		inline std::size_t getSuccessorId() const {
			return this->finger_table[0];
		}
		inline void setSuccessorId(const std::size_t successor_id) {
			this->finger_table[0] = successor_id;
		}
		//TODO CHANGE PLACE FOR THIS FUNCTION
		void set_up_finger_table(const std::unordered_map<std::size_t, std::shared_ptr<Node>> & nodes, const std::size_t last_node_id) {
			this->finger_table.clear();
			auto id_to_analyse = this->my_id;
			for (int i=0; i < 32; i++) {
				id_to_analyse = (id_to_analyse << 1) % (std::numeric_limits<unsigned long>::max());
				this->finger_table.push_back(id_to_analyse);	
			}
		}
	
};

// Adding operators
std::ostream & operator<< (std::ostream  &strm, const Node &node) {
		return strm << "Node( my_id="<< node.my_id << " successor_id="<< node.getSuccessorId() << " predecessor_id="<<node.predecessor_id<< ")";
}



class App {
	private:
		std::size_t last_node_id{0};
		std::shared_ptr<Node> first;
		std::unordered_map<std::size_t,std::shared_ptr<Node>> nodes;
	public:
		inline std::size_t getLastNodeId() {
			return this->last_node_id;
		}
		inline std::shared_ptr<Node> getFirst() {
			return this->first;
		}
		inline std::unordered_map<std::size_t,std::shared_ptr<Node>> getNodes()  {
			return this->nodes;
		}
		App() {
		
		};
		void join(const Node & node) {
			auto node_to_save = std::make_shared<Node>(node);	
			std::cout <<"##############################\n";
			if (nodes.find(node.my_id) != nodes.end()) {
					std::clog << "It was added the node\n";
					return;
			}

			if (last_node_id < node_to_save->my_id) {
				this->last_node_id = node_to_save->my_id;
			}
			if (!this->first.get()) {
				this->first = node_to_save;
				this->nodes[node.my_id] = node_to_save;
				std::clog << "new node  :"<< *node_to_save  << "\n";
				return;
			}

			std::pair<bool, std::shared_ptr<Node>> result_search = this->search(node_to_save);
			
			auto found = result_search.first;
			auto possible_successor = result_search.second;
			
			if (!found) {
				assert(possible_successor->getSuccessorId() == 0);
				possible_successor->setSuccessorId(node_to_save->my_id);
				node_to_save->predecessor_id = possible_successor->my_id;
			}
			else {
				//Check if it is the first node
				if (possible_successor->predecessor_id != 0) {
					auto predecessor_node = this->nodes[possible_successor->predecessor_id];
					predecessor_node->setSuccessorId(node_to_save->my_id);
				} else {
					this->first = node_to_save;
				}
				auto old_predecesor_id = possible_successor->predecessor_id;
				possible_successor->predecessor_id = node_to_save->my_id;
				node_to_save->predecessor_id = old_predecesor_id;
				node_to_save->setSuccessorId(possible_successor->my_id);	
			}
			
			std::clog << "new node  :"<< *node_to_save  << "\n";
			this->nodes[node.my_id] = node_to_save;
		}

		std::pair<bool, std::shared_ptr<Node>> search(std::shared_ptr<Node> & node_to_search) {
			auto id_to_search = (*node_to_search).my_id;
			
			auto node_to_compare = this->first;
			while (node_to_compare->my_id < node_to_search->my_id) {
					if (node_to_compare->getSuccessorId() == 0) {
						 break;
					}
					node_to_compare = calculate_next_node_to_search(node_to_search, node_to_compare); 
			}
			if (node_to_compare->my_id < node_to_search->my_id) {
				return std::make_pair(false, node_to_compare);
			} else {
				return std::make_pair(true, node_to_compare);
			}
		}

		std::shared_ptr<Node> calculate_next_node_to_search(std::shared_ptr<Node> & node_to_search, std::shared_ptr<Node> & node_to_compare) {
			/*
			for (int i = node_to_compare->finger_table.size(); i >= 0; i--) {
				if (node_to_search <= node_to_compare->finger_table[i]) {
					return this->nodes[node_to_compare->finger_table[i]];
				}

			}
			return node_to_search;
			*/
			return this->nodes[node_to_compare->getSuccessorId()];
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
	
	node.set_up_finger_table(app.getNodes(), app.getLastNodeId());
	node2.set_up_finger_table(app.getNodes(), app.getLastNodeId());
	node3.set_up_finger_table(app.getNodes(), app.getLastNodeId());
	node4.set_up_finger_table(app.getNodes(), app.getLastNodeId());
	node5.set_up_finger_table(app.getNodes(), app.getLastNodeId());

	/*
	std::cout <<"@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
	auto toNode = app.getFirst();
	bool exit = false;
	while (!exit) {
		std::cout << *toNode << "\n";
		std::cout <<"--------------------------\n";
		if (toNode->getSuccessorId() == 0) {
			break;
		}
		toNode = app.getNodes()[toNode->getSuccessorId()];
	}
	*/

}
