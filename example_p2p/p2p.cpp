#include <iostream>
#include <functional>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>
#include <utility>
#include <bitset>
#include <limits>
#include <algorithm>


class Node {
	public: 
		std::size_t my_id;
		std::vector<std::size_t> finger_table{std::vector<std::size_t>(32, 0)};
		std::size_t predecessor_id;
		std::string name;
		Node(const std::string & name) {
			this->name = name;
			this->my_id = std::hash<std::string>{}(name);
			this->predecessor_id = 0;
	
		}
		Node() {
			this->my_id = 0;
			this->predecessor_id = 0;
		}
		Node(std::size_t possible_id) {
			this->name = std::string();
			this->my_id = possible_id;
			this->predecessor_id = 0;

		}
	
		inline std::size_t getSuccessorId() const {
			return this->finger_table[0];
		}
		inline void setSuccessorId(const std::size_t successor_id) {
			this->finger_table[0] = successor_id;
		}
		//TODO CHANGE PLACE FOR THIS FUNCTION

	
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
		App() {};
		void join(std::shared_ptr<Node> node_to_save) {
			if (nodes.find(node_to_save->my_id) != nodes.end()) {
					std::clog << "It was added the node\n";
					return;
			}

			if (last_node_id < node_to_save->my_id) {
				this->last_node_id = node_to_save->my_id;
			}
			if (!this->first.get()) {
				this->first = node_to_save;
				this->nodes[node_to_save->my_id] = node_to_save;
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
			
			this->nodes[node_to_save->my_id] = node_to_save;
		}

		std::pair<bool, std::shared_ptr<Node>> search(std::shared_ptr<Node> & node_to_search) {
			auto id_to_search = (*node_to_search).my_id;	
			auto node_to_compare = this->first;

			//TODO change order!
			while ( node_to_search->my_id >= node_to_compare->my_id ) {
				if (node_to_compare->getSuccessorId() == 0) {
					 break;
				}
				node_to_compare = calculate_next_node_to_search(node_to_search, node_to_compare); 
			}
			if ( node_to_search->my_id >= node_to_compare->my_id ) {
				return std::make_pair(false, node_to_compare);
			} else {
				return std::make_pair(true, node_to_compare);
			}
		}

		inline int distance(std::size_t id_to_search, std::size_t id_to_compare) {
			return std::abs((int)(id_to_search -  id_to_compare));	
		}

		std::shared_ptr<Node> calculate_next_node_to_search(std::shared_ptr<Node> & node_to_search, std::shared_ptr<Node> & node_to_compare) {
			auto near = this->nodes[node_to_compare->getSuccessorId()];

			for (int i = 0; i<node_to_compare->finger_table.size(); i++) {
				//TODO check where we find same node
				if (node_to_search->my_id < node_to_compare->finger_table[i])  {
					int distance_to_compare = distance(node_to_search->my_id, node_to_compare->finger_table[1]);
					int current_distance = distance(node_to_search->my_id, near->my_id);
					if (distance_to_compare < current_distance) {
						near = this->nodes[node_to_compare->finger_table[i]];	
					}
					//return this->nodes[node_to_compare->finger_table[i]];	
				}
			}
			return 	near;
		}

		void set_up_finger_table(std::shared_ptr<Node> & node_to_update) {
			std::fill(node_to_update->finger_table.begin()+1, node_to_update->finger_table.end(),0);
			auto id_to_analyse = node_to_update->my_id;
			for (int i=1; i < 32; i++) {
				//id_to_analyse = (id_to_analyse << 1) % (std::numeric_limits<unsigned long>::max());
				//id_to_analyse = (((node_to_update->my_id % this->last_node_id) + 1 ) << i);
				//TODO add search!!
				id_to_analyse = (node_to_update->my_id + (2 << (i - 1))) %  this->last_node_id;

				auto node_to_search = std::make_shared<Node>(id_to_analyse);
				std::pair<bool,std::shared_ptr<Node>> found_node =  this->search(node_to_search);
				std::clog << "node id="<<i << " id_to_analyse="<<id_to_analyse<<" found_node=" <<found_node.second->my_id<<"\n";
				node_to_update->finger_table[i] = found_node.second->my_id;
			}
		}
};	

int main () {
	std::shared_ptr<Node> node = std::make_shared<Node>(1);
	std::shared_ptr<Node> node2 = std::make_shared<Node>(5);
	std::shared_ptr<Node> node3 = std::make_shared<Node>(10);
	std::shared_ptr<Node> node4 = std::make_shared<Node>(50);
	std::shared_ptr<Node> node5 = std::make_shared<Node>(20);
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
		if (toNode->getSuccessorId() == 0) {
			break;
		}
		toNode = app.getNodes()[toNode->getSuccessorId()];
	}


	std::cout << "Added node1= "<< *node <<"\n";
	app.set_up_finger_table(node);	
	std::cout << "Added node2= "<< *node2 <<"\n";
	app.set_up_finger_table(node2);
	std::cout << "Added node3= "<< *node3 <<"\n";
	app.set_up_finger_table(node3);
	std::cout << "Added node4= "<< *node4 <<"\n";
	app.set_up_finger_table(node4);	
	std::cout << "Added node5= "<< *node5 <<"\n";
	app.set_up_finger_table(node5);
}
