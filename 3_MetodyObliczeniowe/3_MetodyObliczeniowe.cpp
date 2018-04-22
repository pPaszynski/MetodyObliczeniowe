#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <math.h>
#include <iomanip>
#include <windows.h>

using namespace std;

void funSin()
{
	cout << "Funkcja: sin(x / 4) ^ 2 - x" << endl;
}
void funTan()
{
	cout << "\nFunkcja: tg(2x)-x-1" << endl;
}

typedef double(*func_type)(double);

double fSin(double x)
{
	return sin(x / 4.0) * sin(x / 4.0) - x;
}

double fTan(double x)
{
	return tan(2.0 * x) - x - 1.0;
}

double pochSin(double x)
{
	return (1.0 / 4.0) * (sin(x / 2.0) - 4.0);
}

double pochTan(double x)
{
	return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

double fiSin(double x)
{
	return sin(x / 4.0) * sin(x / 4.0);
}

double fiTan(double x)
{
	return tan(2 * x) - 1;
}

double picard(func_type f, double x, int max_iter, double TOLX, double TOLF) {


	double estymator = 0;
	double reziduum = 0;
	double X0 = x;


	for (int i = 0; i < max_iter; i++)
	{
		cout << "Iteracja nr: " << i;
		X0 = f(X0);
		cout << "\t Przyblizenie X: " << X0;

		estymator = fabs(X0 - x);
		x = X0;

		reziduum = fabs(X0);
		cout << "\t Residuum: " << reziduum << "\t Estymator: " << estymator << endl;


		if ((estymator <= TOLX && reziduum <= TOLF) || (reziduum <= TOLF))
			break;
	}
	return X0;
}

double bisekcja(func_type f, double a, double b, int max_iter, double TOLX, double TOLF)
{

	double c = 0;
	double estymator = 0;
	double reziduum = 0;

	for (int i = 0; i < max_iter; i++)
	{
		if ((f(a) * f(b)) > 0)
		{
			cout << "Zly przedzial" << endl;
			return EXIT_FAILURE;
		}
		else if ((f(a) * f(b)) < 0)
		{

			c = (a + b) / 2.0;
			estymator = fabs((b - a) / 2);
			reziduum = fabs(f(c));
			cout << "Iteracja nr: " << i << "\t Pocz_przedz: " << a << "\t Przyblizenie X: " << c << "\t Kon_przedz: " << b << endl;
			cout << "Residuum: " << reziduum << "\t Estymator: " << estymator << endl;
			if ((f(a) * f(c)) < 0)
			{
				b = c;
			}
			else {
				a = c;
			}
		}
		else
		{
			if (!f(b) && !f(a)) {

				cout << endl << "x0: " << a << "\t x1=" << b << endl;
				break;
			}

			if (!f(a) && f(b)) {

				return a;
			}

			if (!f(b) && f(a)) {
				return b;
			}

		}
		if (estymator <= TOLX && reziduum <= TOLF)
			break;
	}
	return c;
}

double newtona(func_type f, func_type p, double x, int max_iter, double TOLX, double TOLF)
{

	double x0 = x;
	double x1 = 0;
	double prevX;
	double y = 0;
	double poch_y = 0;
	for (int i = 0; i < max_iter; i++) {
		y = f(x0);
		poch_y = p(x0);

		if (fabs(poch_y) < TOLF)
			break;

		x1 = x0 - y / poch_y;

		if (fabs(x1 - x0) <= TOLX * fabs(x1))
			break;
		prevX = x0;
		x0 = x1;

		cout << "Iteracja nr: " << i;
		cout << "\t Przyblizenie X: " << x1;
		cout << "\t Residuum: " << fabs(f(x1)) << "\t Estymator: " << fabs(x1 - prevX) << endl;
	}
	return x1;
}

double siecznych(func_type f, double x0, double x1, int max_iter, double TOLX, double TOLF)
{

	double estymator = 0;
	double reziduum = 0;
	double x2 = 0;
	for (int i = 0; i < max_iter; i++) {
		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));
		estymator = fabs(x2 - x1);
		reziduum = fabs(f(x2));
		x0 = x1;
		x1 = x2;

		if (estymator <= TOLX && reziduum <= TOLF || reziduum <= TOLF)
			break;

		cout << "Iteracja nr:" << i;
		cout << "\t Przyblizenie X: " << x2;
		cout << "\t Residuum: " << reziduum << "\t Estymator: " << estymator << endl;
	}

	return x2;
}


int main() {
	cout.setf(ios::scientific);
	const int max_iter = 50;
	double e = 10e-50;


	cout << "PICARD" << endl;
	funSin();
	cout << "Przyblizenie X: " << picard(fiSin, 0.0001, max_iter, e, e) << endl;

	cout << endl << endl << "BISEKCJA" << endl;
	funSin();
	cout << "Przyblizenie X: " << bisekcja(fSin, -0.19, 4.0, max_iter, e, e) << endl;
	funTan();
	cout << "Przyblizenie X: " << bisekcja(fTan, 0.4, 0.6, max_iter, e, e) << endl;

	cout << endl << endl << "NEWTON" << endl;
	funSin();
	cout << "Przyblizenie X: " << newtona(fSin, pochSin, -0.5, max_iter, e, e) << endl;
	funTan();
	cout << "Przyblizenie X: " << newtona(fTan, pochTan, 0.6, max_iter, e, e) << endl;

	cout << endl << endl << "SIECZNE" << endl;
	funSin();
	cout << "Przyblizenie X: " << siecznych(fSin, -0.5, 0.6, max_iter, e, e) << endl;
	funTan();
	cout << "Przyblizenie X: " << siecznych(fTan, 0.4, 0.5, max_iter, e, e) << endl;

	system("pause");
	return 0;
}