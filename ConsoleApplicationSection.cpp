// ConsoleApplicationLosowanie.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <time.h>
#include <windows.h>

#define TABSIZE 600
#define TABVALUE 6
#define TABCOUNT 7

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
#pragma omp parallel for
	for (int i = 0; i < TABSIZE; i++) {
		tab[i] = 6;
	}
}
void hitTheTable() {
#pragma omp parallel for
	for (int i = 0; i < TABSIZE; i++) {
		int x = rand() % 20 + 1;
		//cout << " Wylosowano: " << x << endl;
		if (x == 1) {
			int before = tab[i];
			int after = rand() % 6 + 1;
			tab[i] = after;
			tabValue[before - 1]--; //before-1, bo tablica jest od 0
			tabValue[after - 1]++;
			//cout << "Zamieniono: " << before << " na: " << after << endl;
		}
	}
}

void countAll() {
	int tabCount[TABCOUNT] = { 0,0,0,0,0,0,0 };
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

	//cout << endl << "TABCOUNT" << endl;
	for (int i = 0; i < TABCOUNT; i++) {
		cout << tabCount[i] << " ";
	}
	cout << endl;

	//cout << "TABVALUE" << endl;

	for (int i = 0; i < TABVALUE; i++) {
		cout << tabValue[i] << " ";
	}
	cout << endl << endl;
}

int main()
{
	start();

	addValuesToMatrix();

	for (int j = 1; j <= 100; j++) {
		//cout << "Uderzenie numer: " << j << endl;
		hitTheTable();
		//countAll();

		for (int i = 0; i < TABVALUE; i++) {
			cout << tabValue[i] << " ";
		}
		cout << endl;
	}
	end();
}