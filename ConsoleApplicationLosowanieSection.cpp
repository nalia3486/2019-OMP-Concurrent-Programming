// ConsoleApplicationLosowanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <windows.h>
#include <corecrt_math_defines.h>

#define TABSIZE1 150
#define TABSIZE2 300
#define TABSIZE3 450
#define TABSIZE 600
#define TABVALUE 6

#define _MATH_DEFINES_DEFINED

// Czas rozpoczecia 
clock_t startTime;

// Czas zakonczenia 
clock_t endTime;

using namespace std;

int tab[TABSIZE];
int tabPom[TABSIZE];
int tabValue1 = 0; int tabValue2 = 0; int tabValue3 = 0; int tabValue4 = 0; int tabValue5 = 0; int tabValue6 = TABSIZE;
double result1, result2, result3, result4, result5, result6;
double S;
double logZ600;

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

//inicjowanie macierzy
void addValuesToMatrix() {
	for (int i = 0; i < TABSIZE; i++) {
		tab[i] = 6;
	}
}

double logZSilnii(int x) {
	double wynik = 0;
	for (int i = 1; i <= x; i++) {
		wynik += log(i);
	}
	return wynik;
}

int main()
{
	start();

	addValuesToMatrix();

	logZ600 = logZSilnii(TABSIZE);

	for (int j = 1; j <= 100; j++) {
		cout << endl << "Uderzenie numer: " << j << "     ";

#pragma omp parallel sections default(none)
		{
#pragma omp section
			{
				for (int i = 0; i < TABSIZE1; i++) {
					int x = rand() % 20 + 1;
					if (x == 1) {
						int after = rand() % 6 + 1;
						tab[i] = after;
					}
				}
			}
#pragma omp section
			{
				for (int i = TABSIZE1; i < TABSIZE2; i++) {
					int x = rand() % 20 + 1;
					if (x == 1) {
						int after = rand() % 6 + 1;
						tab[i] = after;
					}
				}
			}
#pragma omp section
			{
				for (int i = TABSIZE2; i < TABSIZE3; i++) {
					int x = rand() % 20 + 1;
					if (x == 1) {
						int after = rand() % 6 + 1;
						tab[i] = after;
					}
				}
			}
#pragma omp section
			{
				for (int i = TABSIZE3; i < TABSIZE; i++) {
					int x = rand() % 20 + 1;
					if (x == 1) {
						int after = rand() % 6 + 1;
						tab[i] = after;
					}
				}
			}
		}

#pragma omp parallel sections default(none)
		 {
#pragma omp section
			 {
				 tabValue1 = 0;
				 tabValue2 = 0;

				 for (int i = 0; i <= TABSIZE; i++) {
					 if (tab[i] == 1)  tabValue1++;
					 else if (tab[i] == 2)  tabValue2++;
				 }

				 result1 = logZSilnii(tabValue1);
				 result2 = logZSilnii(tabValue2);
			 }
#pragma omp section
			 {
				 tabValue3 = 0;
				 tabValue4 = 0;

				 for (int i = 0; i <= TABSIZE; i++) {
					 if (tab[i] == 3)  tabValue3++;
					 else if (tab[i] == 4)  tabValue4++;
				 }

				 result3 = logZSilnii(tabValue3);
				 result4 = logZSilnii(tabValue4);
			 }
#pragma omp section
			 {
				 tabValue5 = 0;

				 for (int i = 0; i <= TABSIZE; i++) {
					 if (tab[i] == 5)  tabValue5++;
				 }
				 result5 = logZSilnii(tabValue5);
			 }
#pragma omp section
			 {
				 tabValue6 = 0;

				 for (int i = 0; i <= TABSIZE; i++) {
					 if (tab[i] == 6)  tabValue6++;
				 }
				 result6 = logZSilnii(tabValue6);
			 }
		 }


		 int suma = tabValue1 + tabValue2 + tabValue3 + tabValue4 + tabValue5 + tabValue6;
		 cout <<  tabValue1 << " " << tabValue2 << " " << tabValue3 << " " 
			 << tabValue4 << " " << tabValue5 << " " << tabValue6 << " " << suma;
		 
		 S = logZ600 - (result1+ result2 + result3 + result4 + result5 + result6);
		 cout << "      Entropia: " << S << endl;
	}

	
	end();
}