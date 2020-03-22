// ProgOb2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Produkt {
private:
	string nazwa;
	float cena;
public:
	Produkt(string nazwa, float cena) {
		this->nazwa = nazwa;
		this->cena = cena;
	}

	void WypiszInformacje();
};

void Produkt::WypiszInformacje() {
	cout << "nazwa produktu: " << nazwa << endl;
	cout << "cena: " << cena << endl;
	cout << "---------" << endl;
};

int main()
{
	Produkt *p1 = new Produkt("laptop", 2000);
	Produkt *p2 = new Produkt("myszka", 40);
	Produkt *p3 = new Produkt("monitor", 800);

	p1->WypiszInformacje();
	p2->WypiszInformacje();
	p3->WypiszInformacje();

	delete p1;
	delete p2;
	delete p3;


	int numbers[] = { 1,4,3 };
	unique_ptr <int> pointer(numbers);

	cout << ++(*pointer) << endl;

	//pointer++;
	//*pointer = 10;
	cout << *pointer << endl;
	cout << numbers[0] << " " << numbers[1] << " " << numbers[2];

	int liczba;

	cin >> liczba;

	int * tab = new int [liczba];

	for (int i = 0; i < liczba; i++) {
		tab[i] = i + 10;
	}

	for (int i = 0; i < liczba; i++) {
		cout << tab[i] << endl;
	}
	system("Pause");

	delete[] tab;

	return 0;
}
