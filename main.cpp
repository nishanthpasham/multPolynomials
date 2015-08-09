
#include <iostream>
#include <vector>
#include "InfInt.h"
#include "util.h"
#include "karatsubaMult.h"

using namespace std;

unsigned long long l = 10;
const InfInt *MYBASEBY8 = new InfInt (l);
InfInt basePower (InfInt base, int power);
const InfInt MYBASE = basePower(*MYBASEBY8, 0);
const int numberOfRandNumsGenPerRequired = 1;

//returns base * 2^mult
InfInt baseMult (InfInt base, int mult) 
{
	if(mult == 0)
		return base;
	InfInt *result = new InfInt();
	for(int i=0; i<mult; i++) {
		*result = base * (InfInt::two);
	}
	return *result;
}

void generatePolynomials(std::vector<string> &polynomials, std::vector<InfInt> randNumbs, int polyDegree)
{
	if(randNumbs.size() != (polyDegree+1) * polynomials.size() * numberOfRandNumsGenPerRequired) 
	{
		// throw error
	}
	for(int i=0; i<polynomials.size(); i++) 
	{
		//TODO: can the polynomial be generated using Karastuba?
		InfInt *polyInfInt = new InfInt();
		for(int j=0; j<=polyDegree; j++)
		{
			int k = numberOfRandNumsGenPerRequired * j;
			// InfInt *term = new InfInt((randNumbs.at((i+1)*k)) * (randNumbs.at((i+1)*(k+1))) * (randNumbs.at((i+1)*(k+2))) * (randNumbs.at((i+1)*(k+3))) * basePower (MYBASE, j));
			InfInt *term = new InfInt(randNumbs.at((i+1)*k) * basePower (MYBASE, j));
			*polyInfInt += (*term);
		}
		polynomials.at(i) = (*polyInfInt).toString();
	}

	string output("");
	for(int i=0; i<polynomials.size(); i++) 
	{
		output += polynomials.at(i);
		output += ",";
	}

	std::cout << "The following " << polynomials.size() << " polynomials are generated for karatsuba multiplication" << output << std::endl;
}

void generateVectorOfInfInts (std::vector<unsigned long long int> &randNumbs, std::vector<InfInt> &randInfInts)
{
	if(randNumbs.size() != randInfInts.size())
		//throw error

	for(int i=0; i<randNumbs.size(); i++) 
	{
		InfInt *p = new InfInt (randNumbs.at(i));
		randInfInts.at(i) = *p;
	}
}

int main() 
{
	int polyDegree, noOfPolysToBeMult = 0;
	std::cout << "Please enter the degree of the polynomial: ";
	std::cin >> polyDegree;
	
	std:: cout << "Please enter the number of polynomials to be multiplied: ";
	std::cin >> noOfPolysToBeMult;

	if(noOfPolysToBeMult == 1) 
	{
		std::cout << "Nothing to multiply. To perform any multiplication at least 2 polynomials are needed. Please try again." << std::endl;
		return 0;
	}
	
	int numOfRandNumsNeeded = (polyDegree+1) * noOfPolysToBeMult * numberOfRandNumsGenPerRequired;
	std::vector<unsigned long long int> randNumbs (numOfRandNumsNeeded);
	std::vector<InfInt> randInfInts (numOfRandNumsNeeded);
	util::genRandNums(randNumbs);
	generateVectorOfInfInts(randNumbs, randInfInts);

	std::vector<string> polynomials (noOfPolysToBeMult);
	generatePolynomials(polynomials, randInfInts, polyDegree);

	InfInt *result = new InfInt(1);
	for(int i=0; i< polynomials.size()-1; i++){
		*result *= karatsubaMult(polynomials.at(i), polynomials.at(i+1));
	}

	std::cout << "The result of the multiplication is " << *result << std::endl;
	return 0;
}