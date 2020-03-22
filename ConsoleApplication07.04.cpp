// ConsoleApplication07.04.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <omp.h>
#include <stdio.h>
#include <iostream>

#define N 6
using namespace std;
int main()
{
	//dodawanie dwóch tabel
	int a[] = { 6,5,4,3,2,1 };
	int b[] = { 6,5,4,3,2,1 };
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		a[i] = a[i] + b[i];
		printf("i: %d  a[i]: %d\n", i, a[i]);
	}



