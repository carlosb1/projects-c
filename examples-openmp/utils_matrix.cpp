#include <iostream>
#include <vector>
#include <random>
#include "utils_matrix.h"


namespace utils {
	namespace matrix {
		void mult (const std::vector<float> &  matrixOne, const std::vector<float> & matrixTwo, std::vector<float> & result, int size) {
			for (int row = 0; row < size; ++row) {
				for (int col = 0; col < size; ++col) {
					for (int k = 0; k <size; ++k) {
						result[(size*row)+col] += matrixOne[(size*row)+k] * matrixTwo[(size*k)+col];
					}
				}
			}
		}

		void mult_1 (const std::vector<float> &  matrixOne, const std::vector<float> & matrixTwo, std::vector<float> & result, int size) {
			for (int row = 0; row < size; ++row) {
				#pragma omp parallel for
				for (int col = 0; col < size; ++col) {
					#pragma omp simd
					for (int k = 0; k <size; ++k) {
						result[(size*row)+col] += matrixOne[(size*row)+k] * matrixTwo[(size*k)+col];
					}
				}
			}
		}
		
		void mult_2 ( float *  matrixOne, float * matrixTwo,  float * result, int size)  {
			for (int row = 0; row < size; ++row) {
				for (int col = 0; col < size; ++col) {
					for (int k = 0; k < size; ++k) {
						(*(result+(size*row)+col)) += (*(matrixOne+(size*row)+k)) * (*(matrixTwo+(size*k)+col));
					}
				}
			}
		}

		void mult_3 ( float *  matrixOne, float * matrixTwo,  float * result, int size)  {
			for (int row = 0; row < size; ++row) {
				#pragma omp parallel for
				for (int col = 0; col < size; ++col) {
					#pragma omp simd aligned(result:16) aligned(matrixOne:16) aligned(matrixTwo:16)
					for (int k = 0; k < size; ++k) {
						(*(result+(size*row)+col)) += (*(matrixOne+(size*row)+k)) * (*(matrixTwo+(size*k)+col));
					}
				}
			}
		}
		


	}

}
