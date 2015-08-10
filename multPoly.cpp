#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <limits>
#include <stdlib.h>
#include <string>
#include "InfInt.h"
using namespace std;

const int BASE10 = 10;
InfInt *INFINTBASE10 = new InfInt(10);
InfInt *BIGBASE = new InfInt("73786976294838206473");
const int numberOfRandNumsGenPerRequired = 4;
// unsigned long long l = 10;
// const InfInt *MYBASEBY8 = new InfInt (l);
// const InfInt MYBASE = basePower(*MYBASEBY8, 0);

// Generates a vector of random nums. Each Random Vector is in the range 0 to 18446744073709551615, 1/4 the needed limit.
void genRandNums(std::vector<std::vector<std::vector<unsigned long long int> > > &randNumbs, int noOfPolysToBeMult, int polyDegree) 
{
	std::default_random_engine generator(time(0));
	std::uniform_int_distribution<unsigned long long int> distribution (0, std::numeric_limits<unsigned long long int>::max());//std::numeric_limits<unsigned long long int>::max()
	std::cout << "Generating a vector of random numbers of size: " << noOfPolysToBeMult * polyDegree * numberOfRandNumsGenPerRequired << std::endl;
	for(int i=0; i<noOfPolysToBeMult; i++) {
		for(int j=0; j<polyDegree; j++) {
			for(int k=0; k<numberOfRandNumsGenPerRequired; k++) {
				randNumbs[i][j][k] = distribution(generator);
			}
		}
	}
}

//utility function to print the generated Rand Nums 
void printRandNumsVect(std::vector<std::vector<std::vector<unsigned long long int> > > &randNumbs, int noOfPolysToBeMult, int polyDegree) {
	std::cout << "Printing the randNumbs Vector" << std::endl;
	for(int i=0; i<noOfPolysToBeMult; i++) {
		for(int j=0; j<polyDegree; j++) {
			for(int k=0; k<numberOfRandNumsGenPerRequired; k++) {
				std::cout << randNumbs[i][j][k] << std::endl;
			}
		}
	}
}

void printPolys(std::vector<string> &v) {
	std::cout << "The polynomials are ";
	for(int i=0; i<v.size(); i++) 
	{
		cout << v.at(i) << ", ";
	}
	std::cout << std::endl;
}

int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();

    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1; // If len1 >= len2
}

// returns the length of the number
int getLength(unsigned long long num) 
{
	int length = 1;
	while (num / BASE10 != 0) {
		num /= BASE10;
		length++;
	}
	return length;
}

string add (string a, string b)
{
	InfInt *aa = new InfInt(a);
	InfInt *bb = new InfInt(b);
	return (*aa + *bb).toString();
}

InfInt basePower (InfInt base, int power) 
{
	if(power == 0)
		return InfInt::one;
	InfInt *result = new InfInt(1);
	for(int i=0; i<power; i++) {
		*result *= base;
	}
	return *result;
}

InfInt karatsubaMult(string x, string y)
{
	InfInt *result = new InfInt(1);
	int m = makeEqualLength(x, y);

	if(m == 0)
		return *result;

	size_t sz = 0;

	// m2 + m2Rest = m
	int m2 = m/2;
	int m2Rest = m - m2;

	if( m2 < 5 ) {
		InfInt *inf1 = new InfInt(x);
		InfInt *inf2 = new InfInt(y);
		*result = (*inf1) * (*inf2);
		return *result;
	}

	string xl = x.substr(0, m2);
	string xr = x.substr(m2, m2Rest);
	string yl = y.substr(0, m2);
	string yr = y.substr(m2, m2Rest);

	InfInt z0 = karatsubaMult(xr, yr);
	InfInt z1 = karatsubaMult(add(xl, xr), add(yl, yr));
	InfInt z2 = karatsubaMult(xl, yl);
	*result = (z2 * basePower(*BIGBASE, 2*m2) + ((z1-z2-z0) * basePower(*BIGBASE, m2)) + z0);

	return *result;
}

void generateVectorOfInfInts (std::vector<std::vector<std::vector<unsigned long long int> > > &randNumbs, std::vector<std::vector<std::vector <InfInt> > > &randInfInts, int noOfPolysToBeMult, int polyDegree)
{
	for(int i=0; i<noOfPolysToBeMult; i++) {
		for(int j=0; j<polyDegree; j++) {
			for(int k=0; k<numberOfRandNumsGenPerRequired; k++) {
				InfInt *p = new InfInt (randNumbs[i][j][k]);
				randInfInts[i][j][k] = *p;
				delete p;
			}
		}
	}
}

void generatePolynomials(std::vector<string> &polynomials, std::vector<std::vector<std::vector<InfInt> > > &randInfInts, int noOfPolysToBeMult, int polyDegree)
{
	int num = noOfPolysToBeMult * (polyDegree+1) * numberOfRandNumsGenPerRequired;
	//change polynomials.size() below
	// if(randInfInts.size() != (polyDegree+1) * noOfPolysToBeMult * numberOfRandNumsGenPerRequired) 
	// {
	// 	// throw error
	// }
	for(int i=0; i<noOfPolysToBeMult; i++) 
	{
		//TODO: can the polynomial be generated using Karastuba?
		InfInt *polyInfInt = new InfInt(0);
		
		for(int j=0; j<(polyDegree+1); j++)
		{
			InfInt *term = new InfInt(1);
			for(int k = 0; k< numberOfRandNumsGenPerRequired; k++) {
				*term *=  randInfInts[i][j][k];
			}
			// InfInt *term = new InfInt((randNumbs.at((i+1)*k)) * (randNumbs.at((i+1)*(k+1))) * (randNumbs.at((i+1)*(k+2))) * (randNumbs.at((i+1)*(k+3))) * basePower (MYBASE, j));
			*term *= basePower (*BIGBASE, j);
			*polyInfInt += (*term);
			delete term;
		}
		polynomials.push_back((*polyInfInt).toString());
		delete polyInfInt;
	}

	string output("");
	for(int i=0; i<polynomials.size(); i++) 
	{
		output += polynomials.at(i);
		output += ", ";
	}

	std::cout << "The following " << polynomials.size() << " polynomials are generated for karatsuba multiplication" << output << std::endl;
}

template <typename Type>
void resizeVectors (std::vector<std::vector<std::vector <Type> > > &array3D, int xsize, int ysize, int zsize) 
{
	array3D.resize(xsize);
  	for (int i = 0; i < xsize; ++i) {
    	array3D[i].resize(ysize);

    	for (int j = 0; j < ysize; ++j)
      		array3D[i][j].resize(zsize);
  	}
}

int main () 
{
	// std::vector <unsigned long long int> vect (10);
	// genRandNums(vect);
	// printRandNumsVect(vect);
	
	// string s1("1234"), s2("123");
	// makeEqualLength(s1, s2);
	// std::cout << s1 << " " << s2 << std::endl;
	
	// std::cout << "The length is: " << getLength(0) << std::endl;

	// std::cout << "Addition of " << s1 << " and " << s2 << " = " << add(s1, s2) << std::endl;

	// InfInt *ten = new InfInt(10);
	// std::cout << "Ten power 5 is " << basePower(*ten, 5) << std::endl;

	// InfInt multRes = karatsubaMult(s1, s2);
	// std::cout << "karatsubaMult of " << s1 << " and " << s2 << " = " << multRes << std::endl;

	// size_t sz = 0;
	// std::vector<unsigned long long int> randNumbs(3);
	// std::vector<InfInt> randInfInts;
	// randNumbs.at(0) = stoull(s1, &sz, 0);
	// randNumbs.at(1) = stoull("123", &sz, 0);
	// randNumbs.at(2) = stoull(multRes.toString(), &sz, 0);

	// std::cout << "randNumbs are " << randNumbs.at(0) << " " << randNumbs.at(1) << " " << randNumbs.at(2) << std::endl;
	// generateVectorOfInfInts(randNumbs, randInfInts);
	// std::cout << "randInfInts are " << randInfInts.at(0) << " " << randInfInts.at(1) << " " << randInfInts.at(2) << std::endl;

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

	std::vector<std::vector<std::vector<unsigned long long int> > > randNumbs;
	resizeVectors(randNumbs, noOfPolysToBeMult, polyDegree+1, numberOfRandNumsGenPerRequired);
	genRandNums(randNumbs, noOfPolysToBeMult, polyDegree+1);
	printRandNumsVect(randNumbs, noOfPolysToBeMult, polyDegree+1);
	std::vector<std::vector<std::vector<InfInt> > > randInfInts;
	resizeVectors(randInfInts, noOfPolysToBeMult, polyDegree+1, numberOfRandNumsGenPerRequired);
	generateVectorOfInfInts(randNumbs, randInfInts, noOfPolysToBeMult, polyDegree+1);
	std::vector<string> polynomials;
	generatePolynomials(polynomials, randInfInts, noOfPolysToBeMult, polyDegree+1);
	printPolys(polynomials);

	InfInt *result = new InfInt(1);
	for(int i=0; i< polynomials.size()-1; i++){
		*result *= karatsubaMult(polynomials.at(i), polynomials.at(i+1));
	}

	std::cout << "The result of the multiplication is " << *result << std::endl;

	// size_t sz = 0;
	// string s1("010");
	// string s2("100");
	// // std::cout << "string " << s1 << " in long long is " << stoull(s1, &sz, 0) << std::endl;
	// std::cout << "010 x 100 is " << karatsubaMult(s1, s2) << std::endl;
 	return 0;
}
