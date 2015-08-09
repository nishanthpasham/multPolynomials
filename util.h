#include "InfInt.h"
#include <iostream>
#include <vector>
#include <ctime>
//#include <random>
#include <limits>

namespace util 
{
	InfInt rng (std::vector<int> v);
	void randInBinary(std::vector <int> binaryvector);
	void genRandNums(std::vector <unsigned long long int> &vect);
	void printRandNumsVect(std::vector <unsigned long long int> &vect);
}