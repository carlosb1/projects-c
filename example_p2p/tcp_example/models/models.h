#ifndef MODELS
#include <string>
#include "cereal/archives/json.hpp"

class Message {
	private: 
		std::string operation;		
	public:
		Message(std::string operation_): operation(operation_) {};

		inline std::string getOperation() {
			return this->operation;	
		}
		template <class Archive> void serialize(Archive & archive) {
			archive(operation);
		}

};

// Adding operators
std::ostream & operator<< (std::ostream  &strm, Message &message) {
		return strm << "data( x="<< message.getOperation() << ")";
}




#endif
