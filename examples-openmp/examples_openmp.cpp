#include <iostream>
#include "utils_matrix.h"
#include "chronotimer.h"
#include <type_traits.h>


void fillRandomMatrix(std::vector<float> & matr, int size) {	
			
	const int minUnif = 0;
	const int maxUnif = 10;
		
	/* set up random configuration */
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution <> dis(minUnif,maxUnif);
	
	for (int row = 0; row < size; ++row) {
		for (int col  = 0; col < size; ++col) {
			matr[(row*size)+col] = dis(gen); 
		}
	}
}
void fillRandomMatrixArray(float *arr_matr, int size) {
	const int minUnif = 0;
	const int maxUnif = 10;
		
	/* set up random configuration */
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution <> dis(minUnif,maxUnif);
	for (int row = 0; row < size; ++row) {
		for (int col = 0; col < size; ++col) {
			*(arr_matr+(row*size)+col) = dis(gen); 	
		}
	}

}

/*

void printMatrix(std::vector<float> & matr) {
	for (auto rows = matr.begin(); rows != matr.end(); ++rows) {
		std::cout << "[";
		for (auto value = (*rows).begin(); value != (*rows).end(); ++value) {
			std::cout << (*value) << ", ";
		}
		std::cout << "]" << std::endl;
	}
}

*/


void simpleMult(const int size) {
	utils::ChronoTimer timer;
	/* set Up simple matrix */
	std::vector<float> matr1 = std::vector<float>(size*size);
	
	timer.init();
	fillRandomMatrix(matr1,size);
	std::printf("simple fill values: time: %f ms\n",timer.now() / 1000);
	
	std::vector<float> matr2 = std::vector<float>(size*size);
	
	timer.init();
	fillRandomMatrix(matr2,size);
	std::printf("simple fill values 2: time: %f ms\n",timer.now() / 1000);
	
	std::vector<float> result = std::vector<float>(size*size);

	timer.init();
	utils::matrix::mult(matr1,matr2,result,size);
	std::printf("simple: time: %f ms\n",timer.now() / 1000);

}

void openMPMult1(const int size)  {
	utils::ChronoTimer timer;
	/* set Up simple matrix */
	std::vector<float> matr1 =std::vector<float>(size*size);

	timer.init();
	fillRandomMatrix(matr1,size);
	std::printf("openmp fill values: time: %f ms\n",timer.now() / 1000);
	
	std::vector<float> matr2 = std::vector<float>(size*size);
	
	timer.init();
	fillRandomMatrix(matr2,size);
	std::printf("openmp fill values 2: time: %f ms\n",timer.now() / 1000);
	
	std::vector<float> result = std::vector<float>(size*size); 
	timer.init();
	utils::matrix::mult_1(matr1,matr2,result,size);
	std::printf("openmp mult_1: time: %f ms\n",timer.now() / 1000);
}

void arrayMult(const int size) {
	utils::ChronoTimer timer;
	
	
	float *p_matr1 = new float[size*size];
	float *p_matr2 = new float[size*size];
	float *p_result = new float[size*size];
	

	timer.init();
	fillRandomMatrixArray(p_matr1,size);
	std::printf("array : time: %f ms\n",timer.now() / 1000);
	
	timer.init();
	fillRandomMatrixArray(p_matr2,size);
	std::printf("array 2: time: %f ms\n",timer.now() / 1000);

	timer.init();
	utils::matrix::mult_2(p_matr1,p_matr2,p_result,size);
	std::printf("array mult_2: time: %f ms\n",timer.now() / 1000);
	
	delete [] p_matr1;
	delete [] p_matr2;
	delete [] p_result;
}

//typedef typename std::aligned_storage<sizeof(float),alignof(float)>::type my_storage_typee;

void arrayOpenMPMult(const int size) {
	utils::ChronoTimer timer;
	
	
	float *p_matr1 = new float[size*size];
	float *p_matr2 = new float[size*size];
	float *p_result = new float[size*size];
	

	timer.init();
	fillRandomMatrixArray(p_matr1,size);
	std::printf("array openMP : time: %f ms\n",timer.now() / 1000);
	
	timer.init();
	fillRandomMatrixArray(p_matr2,size);
	std::printf("array openMP 2: time: %f ms\n",timer.now() / 1000);

	timer.init();
	utils::matrix::mult_3(p_matr1,p_matr2,p_result,size);
	std::printf("array openMP mult_3: time: %f ms\n",timer.now() / 1000);

	
	delete [] p_matr1;
	delete [] p_matr2;
	delete [] p_result;
}
int main () { 
	const int size =  1000;

	simpleMult(size);
	openMPMult1(size);
	arrayMult(size);
	arrayOpenMPMult(size);

}
