
#include "karatsubaMult.h"


const int BASE10 = 10;
InfInt *INFINTBASE10 = new InfInt(10);

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
	int length = 0;
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
	InfInt *result = new InfInt();
	for(int i=0; i<power; i++) {
		*result *= base;
	}
	return *result;
}

InfInt karatsubaMult(string x, string y)
{
	InfInt *result = new InfInt(0);
	int m = makeEqualLength(x, y);

	if(m == 0)
		return *result;

	size_t sz = 0;
	if( x.length() == 1 || y.length() == 1 ) {
		result = new InfInt(stoull(x, &sz, 0) * stoull(y, &sz, 0));
		return *result;
	}

	// m2 + m2Rest = m
	int m2 = m/2;
	int m2Rest = m - m2;

	string xl = x.substr(0, m2);
	string xr = x.substr(m2, m2Rest);
	string yl = y.substr(0, m2);
	string yr = y.substr(m2, m2Rest);

	InfInt z0 = karatsubaMult(xr, yr);
	InfInt z1 = karatsubaMult(add(xl, xr), add(yl, yr));
	InfInt z2 = karatsubaMult(xl, yl);
	*result = (z2 * basePower(*INFINTBASE10, 2*m2) + ((z1-z2-z0) * basePower(*INFINTBASE10, m2)) + z0);

	return *result;
}