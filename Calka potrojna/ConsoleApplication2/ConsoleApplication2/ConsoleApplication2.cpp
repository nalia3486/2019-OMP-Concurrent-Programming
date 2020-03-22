// ConsoleApplication2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <omp.h>
#include <stdio.h>
int main()
{
	// Ustaw liczbę wątków na 15
	omp_set_num_threads(15);
	// Wypisze się jeden raz
	printf("Hello World! Kod szeregowy\n");
	// Poniższy blok wykona się w 15 wątkach
#pragma omp parallel
	{
		printf("Hello, jestem watkiem nr %d\n", omp_get_thread_num());
	}
}

