#include <iostream>
#include <signal.h>
#include "TCPClient.h"
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


TCPClient tcp;

void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}

int main(int argc, char *argv[])
{
	signal(SIGINT, sig_exit);

	tcp.setup("127.0.0.1",11999);
	while(1)
	{
		std::stringstream ss; 
		{
			cereal::JSONOutputArchive oarchive(ss);
			MyData mydata;
			mydata.x = 1;	
			mydata.y = 2;	
			mydata.z = 3;
			oarchive(mydata);
		}
		std::cout << ss.str() << "\n";
		tcp.Send(ss.str());
		string rec = tcp.receive();
		if( rec != "" )
		{
			cout << "Server Response:" << rec << endl;
		}
		sleep(1);
	}
	return 0;
}
