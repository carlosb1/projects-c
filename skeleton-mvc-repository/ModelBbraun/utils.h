#ifndef BBRAUN_UTILS
#define BBRAUN_UTILS
#include <string>
namespace bbraun {
	template<class T> std::string  to_string(T elem)  {
		std::ostringstream stm;
		stm << elem;
		return stm.str();
	}
};
#endif