// ConsoleApplication12.04-calka.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <corecrt_math_defines.h>

#define _MATH_DEFINES_DEFINED

// Czas rozpoczecia 
clock_t startTime;

// Czas zakonczenia 
clock_t endTime;

using namespace std;

double f1(double x, double y)
{
	return pow(M_E, (-x * x - y * y)) / sqrt(x * x + y + x * y);
}
void start()
{
	startTime = clock();
}

void end()
{
	endTime = clock();
	double result = (double)(endTime - startTime) / 1000.0;
	printf("Czas wynosi %f\n", result);
}
int main()
{
	double xp, xk, yp, yk, xh, yh, xy, calka;
	int n;

	start();

	// przedzialy x
	xp = 3;
	xk = 4;

	//przedzialy y
	yp = 1;
	yk = 2;

	// im wieksze n tym wieksza dokladnosc
	n = 1000;
	int n1 = 250, n2 = 500, n3 = 750;

	//h oznacza krok całkowania
	xh = (xk - xp) / (double)n;
	yh = (yk - yp) / (double)n;

	xy = xh * yh;

	calka = 0;

	for (int j = 1; j <= n; j++)
	{
		double x = xp + j * xh;

#pragma omp parallel sections reduction(+:calka) default(none)
		{
#pragma omp section 
			{
				for (int i = 1; i < n1; i++)
				{
					double y = yp + i * yh;
					//sumujemy wszystkie
					calka += f1(x, y)*xy;
				}
			}

#pragma omp section 
			{
				for (int i = n1; i < n2; i++)
				{
					double y = yp + i * yh;
					//sumujemy wszystkie
					calka += f1(x, y)*xy;
				}
			}

#pragma omp section 
			{
				for (int i = n2; i < n3; i++)
				{
					double y = yp + i * yh;
					//sumujemy wszystkie
					calka += f1(x, y)*xy;
				}
			}

#pragma omp section 
			{
				for (int i = n3; i <= n; i++)
				{
					double y = yp + i * yh;
					//sumujemy wszystkie
					calka += f1(x, y)*xy;
				}
			}
		}
	}

	end();

	cout << "Wynik calkowania: " << calka << endl;

	return 0;
}
