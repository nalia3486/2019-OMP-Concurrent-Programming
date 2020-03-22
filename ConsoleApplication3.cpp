// ConsoleApplication3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <ctime>

using namespace std;

#define n 5

static double A[n][n], B[n][n], C[n][n];
static double S1[n][n] = { 0,0 }, S2[n][n] = { 0,0 };
static double W1[n][n] = { 0,0 }, W2[n][n] = { 0,0 };
bool rowne = true;
int main()
{
	time_t pocz;
	int i, j, k;
	double pom = 0, pom2 = 0;
	pocz = clock();
#pragma omp parallel
	{
#pragma omp for private(i,j)
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				A[i][j] = (double(i)) / (i + j + 10.0);
				B[i][j] = (double(i + j)) / (i + j + 20.0);
				C[i][j] = (double(j)) / (i + j + 30.0);

			}
		}
	}

#pragma omp parallel
	{

#pragma omp for private(k,i,j,pom2,pom)	
		for (k = 0; k < n; k++)
		{
			for (i = 0; i < n; i++)
			{
				pom = 0, pom2 = 0;

				for (j = 0; j < n; j++)
				{
					pom += B[k][j] * C[j][i];
					pom2 += A[k][j] * B[j][i];

				}
				S1[k][i] = pom;
				S2[k][i] = pom2;
				//cout << S1[k][i] << " ";

			}
		}
	}
#pragma omp parallel
	{

#pragma omp for private(k,i,j,pom2,pom)	
		for (k = 0; k < n; k++)
		{
			for (i = 0; i < n; i++)
			{

				pom = 0;
				pom2 = 0;
				for (j = 0; j < n; j++)
				{
					pom += A[k][j] * S1[j][i];
					pom2 += S2[k][j] * C[j][i];
				}
				W1[k][i] = pom;
				W2[k][i] = pom2;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << W1[j][i] << " = " << W2[j][i] << endl;
			if (float(W1[j][i]) != float(W2[j][i]))
			{
				rowne = false;
			}

		}
	}
	cout << "czas: " << clock() - pocz;
	if (rowne)
		cout << "Sukces";
	else
		cout << "Blad";

	return 0;
}