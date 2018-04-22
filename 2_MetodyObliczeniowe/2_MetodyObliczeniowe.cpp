#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

template<typename T>
T eps()
{
	T e = 1.0;
	int lmant = 0;
	while (e + 1 > 1) {
		e *= 0.5;
		lmant++;
	};
	e *= 2;
	lmant--;
	cout << "\nEpsilon: " << e << endl;
	cout << "Liczba mantys: " << lmant << endl;
	return e;
}

long double expFunc(double x)
{
	return ((1 - exp(-x)) / x);
}

double epsilon = eps<double>();

double taylor(double x)
{
	double elem = 1.0;
	double sum = 0.0;
	int n = 1;
	while (fabs(elem) >= epsilon)
	{
		sum += elem;
		elem *= (-x) / (1 + n);
		n++;
		if (sum > 1E307 || sum != sum) //NaN
		{
			break;
			exit(0);
		}
	}
	return sum;
}

int main() {
	fstream ffrom, fto;
	double l, x, fx, cpFx, error;
	ffrom.open("oneminexp_ref.txt", fstream::in);
	fto.open("result.txt", fstream::out);
	cout.precision(20);
	cout.setf(ios_base::left);
	cout.setf(ios_base::scientific);
	fto.precision(20);
	fto.setf(ios_base::left);
	fto.setf(ios_base::scientific);
	int i = 0;
	if (ffrom.good() && fto.good())
	{
		while (!ffrom.eof())
		{
			ffrom >> l;
			ffrom >> x;
			ffrom >> fx;
			if (i % 10 == 0)
			{
				if (x <= 1)
				{
					cpFx = taylor(x);
				}
				else cpFx = expFunc(x);
				error = abs((cpFx - fx) / fx);
				cout << setw(30) << x;
				fto << setw(30) << x;
				cout << setw(30) << cpFx;
				fto << setw(30) << cpFx;
				cout << setw(30) << fx;
				fto << setw(30) << fx;
				cout << setw(30) << error;
				fto << setw(30) << error;
				cout << "\n";
				fto << "\n";
			}
			i++;
		}
	}
	ffrom.close();
	fto.close();

	system("PAUSE");
	return 0;
}
