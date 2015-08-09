#ifndef KARATSUBAMULTIPLICATION_H_
#define KARATSUBAMULTIPLICATION_H_

#include <iostream>
#include <string>
#include "InfInt.h"
#include "util.h"
#include <stdlib.h>
using namespace std;

int getLength(unsigned long long num); // returns the number of digits a number has
int makeEqualLength(string &str1, string &str2);
string add (string a, string b);
InfInt powerBase10 (int power);
InfInt karatsubaMult(string x, string y);

#endif