// ProgOb1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
template <class T>
T sumuj(T a, T b)
{
	T result;
	result = a + b;
	return result;
}

class Zwierze 
{
private: 
	string gatunek;
	string imie;
	int wiek;

public:
	void dodajZwierze() 
	{
		cout << "Dodaj nowe zwierze do bazy" << endl;
		cout << "Podaj gatunek: ";
		cin >> gatunek;

		cout << "Podaj imie: ";
		cin >> imie;

		cout << "Podaj wiek: ";
		cin >> wiek;
	}

	void dajGlos();
};

int main()
{
	Zwierze zwierz;
	zwierz.dodajZwierze();

	cout << sumuj<int>(6, 7) << endl;
	cout << sumuj<double>(6.5, 7.5) << endl;
	cout << sumuj<string>("a", "b") << endl;

}