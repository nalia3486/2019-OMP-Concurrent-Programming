#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <windows.h>
#include <time.h>

//rozmiar macierzy
#define ROZMIAR 300

double A[ROZMIAR][ROZMIAR];
double B[ROZMIAR][ROZMIAR];
double C[ROZMIAR][ROZMIAR];
double D[ROZMIAR][ROZMIAR];

double AB[ROZMIAR][ROZMIAR];
double CD[ROZMIAR][ROZMIAR];
double A_BC[ROZMIAR][ROZMIAR];
double AB_C[ROZMIAR][ROZMIAR];
double BC[ROZMIAR][ROZMIAR];

//trzy sposoby na pomno?enie macierzy
double X1[ROZMIAR][ROZMIAR]; // (A * B) * (C * D)
double X2[ROZMIAR][ROZMIAR]; // A * (B * C) * D
double X3[ROZMIAR][ROZMIAR]; // ((A * B) * C) * D

// Czas rozpoczecia 
clock_t startTime;

// Czas zakonczenia 
clock_t endTime;

using namespace std;

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

bool doubleEquals(double a, double b, double epsilon = 0.000001)
{
	return abs(a - b) < epsilon;
}

//inicjowanie macierzy
void addValuesToMatrix() {
	//#pragma omp parallel for
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			A[i][j] = (double)(i + 2 * j) / (double)(i + 7 * j + 1);
			B[i][j] = (double)(i + 3 * j) / (double)(2 * i + 3 * j + 2);
			C[i][j] = (double)(2 * i + j) / (double)(i + 5 * j + 3);
			D[i][j] = (double)(i + j + 3) / (double)(3 * i + 3 * j + 1);

			X1[i][j] = 0.0;
			X2[i][j] = 0.0;
			X3[i][j] = 0.0;

			AB[i][j] = 0.0;
			A_BC[i][j] = 0.0;
			AB_C[i][j] = 0.0;
			BC[i][j] = 0.0;
			CD[i][j] = 0.0;
		}
	}
}

int main()
{
	cout << "Matrix" << endl;
	start();

	addValuesToMatrix();

	//#pragma omp parallel for
		//mnozenie macierzy. AB
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				AB[i][j] += A[i][k] * B[k][j];
				CD[i][j] += C[i][k] * D[k][j];
			}
		}
	}

	//#pragma omp parallel for
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				BC[i][j] += B[i][k] * C[k][j];
			}
		}
	}






	//potem


	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				X1[i][j] += AB[i][k] * CD[k][j];
			}
		}
	}
	//#pragma omp parallel for
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				AB_C[i][j] += AB[i][k] * C[k][j];
			}
		}
	}

	//#pragma omp parallel for
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				A_BC[i][j] += A[i][k] * BC[k][j];
			}
		}
	}



	//jeszcze pozniej

		//#pragma omp parallel for
		//mnozenie macierzy. Kolejnosc: ((A * B) * C) * D
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				X3[i][j] += AB_C[i][k] * D[k][j];
			}
		}
	}

	//#pragma omp parallel for
//mnozenie macierzy. Kolejnosc: A * (B * C) * D
	for (int i = 0; i < ROZMIAR; i++) {
		for (int j = 0; j < ROZMIAR; j++) {
			for (int k = 0; k < ROZMIAR; k++) {
				X2[i][j] += (A_BC[i][k] * D[k][j]);
			}
		}
	}

	end();

#pragma omp parallel for
	for (int i = 0; i < ROZMIAR; i++) {
		for (int k = 0; k < ROZMIAR; k++) {
			if ((doubleEquals(X2[i][k], X3[i][k])) && (doubleEquals(X1[i][k], X3[i][k]))) {
				//cout << "Success!" << endl;
			}
			else {
				cout << "Failed!" << endl;

				//cout << "i= " << i << " k: " << k << endl;
			}
			//cout << X1[i][k] << endl;
			//cout << X2[i][k] << endl;
			//cout << X3[i][k] << endl;
		}
	}
}
