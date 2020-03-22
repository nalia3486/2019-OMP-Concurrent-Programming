// ConsoleApplication12.04-calka.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <corecrt_math_defines.h>

#define _MATH_DEFINES_DEFINED

// Czas rozpoczecia 
clock_t startTime;

// Czas zakonczenia 
clock_t endTime;

using namespace std;

double f1(double x, double y, double z)
{
	return cos(y)*cos(z)*sin(x)/sqrt(1+x*x+y*y+z);
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
	double xp, xk, yp, yk, xh, yh, xy, zp, zk, zh ,calka;

	start();

	// przedzialy x
	xp = 0;
	xk = 1;

	//przedzialy y
	yp = 0;
	yk = 1;

	//przedzialy z
	zp = 0;
	zk = 1;

	// im wieksze n tym wieksza dokladnosc
	int n = 400;

	//h oznacza krok całkowania
	xh = (xk - xp) / (double)n;
	yh = (yk - yp) / (double)n;
	zh = (zk - zp) / (double)n;

	xy = xh * yh * zh;

	calka = 0;

	for (int i = 1; i <= n; i++)
	{
		double x = xp + i * xh;
		for (int j = 1; j <= n; j++)
		{
			double y = yp + j * yh;
#pragma omp parallel for reduction(+:calka) default(none)
			for (int k = 1; k <= n; k++) {
				double z = zp + k * zh;
				calka += f1(x, y, z)*xy;
			}
		}
	}

	end();

	cout << "Wynik calkowania: " << calka << endl;

	return 0;
}
