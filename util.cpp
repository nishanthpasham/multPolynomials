#include "util.h"

namespace utility
{
	InfInt rng (std::vector<int> v) 
	{
		long long num;
		unsigned base = 2;
		for(unsigned i=0; i<v.size(); i++) {
			num += (v.at(i) * (base^i)); 
		}
	return InfInt(num);
	}

	// utility function that generates a rand num in binary format
 	void randInBinary(std::vector <int> binaryvector) 
 	{
		srand(time(NULL));
	
		for(unsigned i=0; i<binaryvector.size(); i++) {
			unsigned randbit=rand()%2;
			binaryvector.at(i) = randbit;
		}
	}

	// Generates a vector of random nums. Each Random Vector is in the range 0 to 18446744073709551615, 1/4 the needed limit.
	void genRandNums(std::vector <unsigned long long int> &vect) 
	{
		std::default_random_engine generator(time(0));
		std::uniform_int_distribution<unsigned long long int> distribution (0, 10);//std::numeric_limits<unsigned long long int>::max()
		std::cout << "Generating a vector of random numbers of size: " << vect.size() << std::endl;
		for(unsigned i=0; i<vect.size(); i++) {
			vect.at(i) = distribution(generator);
		}
	}

	//utility function to print the generated Rand Nums 
	void printRandNumsVect(std::vector <unsigned long long int> &vect) {
		for(unsigned i=0; i<vect.size(); i++) {
			std::cout << vect.at(i) << std::endl;
		}
	}

}

/*
int main () 
{
	std::vector <unsigned long long int> vect (10);
	genRandNums(vect);
	printRandNumsVect(vect);
	return 0;
}
*/