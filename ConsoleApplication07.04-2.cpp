// ConsoleApplication07.04-2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

//przyklad darka
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

#define rozm 10

double A[rozm][rozm];
double B[rozm][rozm];
double C[rozm][rozm];
double pomAB[rozm][rozm];
double pomBC[rozm][rozm];
double S1[rozm][rozm];
double S2[rozm][rozm];

int main()
{
	//generowanie tablic
	time_t czas = clock();
	cout << "Generowanie... " << endl;
#pragma omp parallel sections default(none)
	{
#pragma omp section 
		{
			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					A[i][j] = ((double)i) / ((double)i + (double)j + 10);
					cout << "A: " << A[i][j] << endl;
					
				}
			}
		}
#pragma omp section
		{
			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					B[i][j] = ((double)i + (double)j) / ((double)i + (double)j + 20);
					cout << "B: " << B[i][j] << endl;
				}
			}
		}
#pragma omp section
		{
			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					C[i][j] = ((double)j) / ((double)i + (double)j + 30);
					cout << "C: " << C[i][j] << endl;
				}
			}
		}

	}

	cout << "Obliczenie a*b i b*c... " << endl;

#pragma omp parallel sections default(none)
	{

#pragma omp section
		{
			//B*C

			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					double sumBC = 0;
					for (int k = 0; k < rozm; k++)
					{
						sumBC = sumBC + (B[i][k] * C[k][j]);

					}
					/*int pom = sumBC * 10000;
					pom /= 10;
					double pom2 = pom;*/
					pomBC[i][j] = sumBC;
				}
			}
		}

#pragma omp section
		{
			//A*B

			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					double sumBC = 0;
					for (int k = 0; k < rozm; k++)
					{
						sumBC = sumBC + (A[i][k] * B[k][j]);

					}
					/*int pom = sumBC * 10000;
					pom /= 10;
					double pom2 = pom;*/
					pomAB[i][j] = sumBC;
				}
			}
		}

	}

	cout << "Obliczenie a*bc i ab*c..." << endl;

#pragma omp parallel sections default(none)
	{
#pragma omp section
		{
			//A*(BC)
			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					double sumABC = 0;
					for (int k = 0; k < rozm; k++)
					{
						sumABC = sumABC + (A[i][k] * pomBC[k][j]);

					}
					/*int pom = sumABC * 10000;
					pom /= 10;
					double pom2 = pom;*/
					S1[i][j] = sumABC;
				}
			}
		}
#pragma omp section
		{
			//AB*C
			for (int i = 0; i < rozm; i++)
			{
				for (int j = 0; j < rozm; j++)
				{
					double sumABC = 0;
					for (int k = 0; k < rozm; k++)
					{
						sumABC = sumABC + (pomAB[i][k] * C[k][j]);

					}
					//int pom = sumABC * 10000;
					//pom /= 10;
					//double pom2 = pom;
					S2[i][j] = sumABC;
				}
			}
		}
	}

	cout << "Czas wykonania: " << clock() - czas;


	//cout.precision(15);
	//for (int i = 0;i < rozm;i++)
	//{
	//	for (int j = 0;j < rozm;j++)
	//	{
	//		cout << S1[i][j] << "\t";
	//	}
	//	cout << endl;
	//}






	//cout << endl << endl << endl;
	//cout.precision(15);
	/*for (int i = 0;i < rozm;i++)
	{
		for (int j = 0;j < rozm;j++)
		{
			cout << S2[i][j] << "\t";
		}
		cout << endl;
	}*/

	int czy_rowne = 1;

	for (int i = 0; i < rozm; i++)
	{
		for (int j = 0; j < rozm; j++)
		{
			if ((float)S1[i][j] != (float)S2[i][j])
			{
				//cout << S1[i][j] << " rozne " << S2[i][j] << " roznica " << S1[i][j] - S2[i][j] << endl;
				czy_rowne = 0;
			}
			else
			{
				//cout << S1[i][j] << " = " << S2[i][j] << endl;
			}
		}
		//cout << endl;
	}

	cout << endl << "Porownanie " << endl;

	if (czy_rowne == 1)
	{
		cout << endl << endl << "Rowne";
	}
	else
	{
		cout << endl << endl << "Nie rowne";
	}

	_getch();
	return 0;
}