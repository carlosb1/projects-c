#ifndef _TIMER_CHRONO_H
#define _TIMER_CHRONO_H

#include <cstdio>
#include <string>
#include <ctime>
#include <chrono>


namespace utils {
	class ChronoTimer
	{	
	private:
		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point stop;
	public:
		inline void init() {
   			start = std::chrono::high_resolution_clock::now();
		};
		inline double now () {
			stop = std::chrono::high_resolution_clock::now();
			std::chrono::high_resolution_clock::time_point tmpStart = start;
   			start = std::chrono::high_resolution_clock::now();
			return  std::chrono::duration_cast<std::chrono::milliseconds>(stop - tmpStart).count();
		};
	};

	}


#endif



