#include <iostream>
#include "cereal/archives/json.hpp"
#include <sstream>

struct MyData{
	int x, y ,z;
	template<class Archive> void serialize(Archive & archive) {
		archive(x, y, z);
	}
};

// Adding operators
std::ostream & operator<< (std::ostream  &strm, const MyData &mydata) {
		return strm << "data( x="<< mydata.x << " y="<< mydata.y << " z="<<mydata.z<< ")";
}




#include "TCPServer.h"

TCPServer tcp;

void * loop(void * m)
{
        pthread_detach(pthread_self());
	while(1)
	{
		srand(time(NULL));
		//char ch = 'a' + rand() % 26;
		//string s(1,ch);
		string str = tcp.getMessage();
		if( str != "" )
		{
			cout << "Message:" << str << endl;
			//tcp.Send(" [client message: "+str+"] ");
			tcp.Send("{ok}");
			
			std::stringstream ss;
			ss << str;
			cereal::JSONInputArchive iarchive(ss);	
			MyData mydata;
			iarchive(mydata);
			//std::cout << mydata << "\n";
			
			tcp.clean();
		}

		usleep(1000);
	}
	tcp.detach();
}

int main()
{
	pthread_t msg;
	tcp.setup(11999);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}
