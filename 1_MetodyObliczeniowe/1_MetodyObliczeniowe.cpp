// ConsoleApplication1.cpp: Definiuje punkt wejœcia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


int main()
{
	int it = 0;
	float p = 1;
	float eps = 1;

	while ((eps + p) > 1)
	{
		it++;
		eps /= 2;
	}
	cout << "Ilosc iteracji dla float: " << it - 1 << endl
		<< "Najmniejsza liczba dla float: " << eps << endl;




	int it1 = 0;
	double p1 = 1;;
	double eps1 = 1;
	while ((eps1 + p1) > 1)
	{
		it1++;
		eps1 /= 2;
	}
	cout << "Ilosc iteracji dla double: " << it1 - 1 << endl
		<< "Najmniejsza liczba dla double: " << eps1 << endl;

	return 0;
}