#include "pch.h"
#include <iostream>
#include <time.h>
#include <omp.h>
#include <windows.h>
#include <corecrt_math_defines.h>

#define TABSIZE 600
#define TABVALUE 6

#define _MATH_DEFINES_DEFINED

// Czas rozpoczecia 
clock_t startTime;

// Czas zakonczenia 
clock_t endTime;

using namespace std;

int tab[TABSIZE];
int tabValue[TABVALUE] = { 0,0,0,0,0,TABSIZE };

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
#pragma omp parallel for shared(tab)
	for (int i = 0; i < TABSIZE; i++) {
		tab[i] = 6;
	}
}

void hitTheTable() {
#pragma omp parallel for shared(tab)
	for (int i = 0; i < TABSIZE; i++) {
		int x = rand() % 20 + 1;
		if (x == 1) {
			int before = tab[i];
			int after = rand() % 6 + 1;
			tab[i] = after;
#pragma omp critical
			tabValue[before - 1]--; //before-1, bo tablica jest od 0
#pragma omp critical
			tabValue[after - 1]++;
		}
	}
}

void countAll() {
#pragma omp parallel shared(tab) 
	{
	int tabCount[TABVALUE + 1] = { 0,0,0,0,0,0,0 };
	#pragma omp parallel for
	for (int i = 0; i < TABSIZE; i++) {
		switch (tab[i]) {
		case 1: tabCount[0]++; break;
		case 2: tabCount[1]++; break;
		case 3: tabCount[2]++; break;
		case 4: tabCount[3]++; break;
		case 5: tabCount[4]++; break;
		case 6: tabCount[5]++; break;
		}
		tabCount[6]++;
	}
#pragma omp single
	for (int i = 0; i <= TABVALUE; i++) {
		cout << tabCount[i] << " ";
	}
	}
}

double logZSilni(int x) {
	double wynik = 0;
#pragma omp parallel for reduction(+:wynik) shared(x) 
	for (int i = 1; i <= x; i++) {
		wynik += log(i);
	}
	return wynik;
}

void entropia() {
	double result = 0;

#pragma omp parallel for reduction(+:result) default(none)
	for (int i = 0; i < TABVALUE; i++) {
		result += logZSilni(tabValue[i]);
	}

	double S = logZSilni(TABSIZE) - result;
	cout << " Entropia: " << S << endl;
}

int main()
{
	start();

	addValuesToMatrix();

	for (int j = 1; j <= 100; j++) {
		cout << "Uderzenie numer: " << j << " ";
		hitTheTable();
		countAll();
		entropia();
	}
	end();
}