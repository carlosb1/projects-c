#include <vector>
#include <random>

namespace utils {
	namespace matrix {

		/**
		 * simple test
		 */
		void mult (const std::vector<float> &  matrixOne, const std::vector<float> & matrixTwo, std::vector<float> & result, int size) ;
		
		/** 
		 * We apply openmp optimization
		 * */
		void mult_1 (const std::vector<float> &  matrixOne, const std::vector<float> & matrixTwo, std::vector<float> & result, int size);

		/**
		 * We apply dynamic arrays
		 */
		void mult_2 (float *  matrixOne, float * matrixTwo, float * result, int size);
		
		/**
		 * It is applied openmp and aligned
		 */
		void mult_3 (float *  matrixOne, float * matrixTwo, float * result, int size);

		inline int calculatePadding(const int sizeMatrix) {
		   	int nepc = 64 / sizeof(float);
		        return  ((sizeMatrix - 1)/nepc + 1) * nepc;
		}
		

	}

}
