#include <stdio.h>
#include <string>
//Biblioteki do kolorów:
#include <windows.h> //s³abe rozwi¹zanie które raczej (chocia¿ s¹ wyj¹tki) bêdzie dzia³aæ tylko na Windowsie :/
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie dzia³aj¹

int stan_uz = 1; //zmienna stan_uz okreœla czy u¿ytkownik jest zalogowany, czy nie. Odblokowuje to nowe opcje w menu. Domyœlnie ustawione na 0 - niezalogowany

HANDLE kolor; //zmienna przetrzymuj¹ca nasze kolorki (tak dzia³a w windowsie)

using namespace std;


void menu (int stan_uz) {
	bool stan = true; //wykorzystywane do pêtli for
	do {	
		SetConsoleTextAttribute (kolor, 10); //kolor komunikatów systemu
		cout << "Testowa ¿Ÿæœ¹ wersja menu (wiele moze jeszcze ulec zmianie)\n" << endl;
		SetConsoleTextAttribute (kolor, 15); //kolor komunikatów systemu
		cout << "Prosze wybrac odpowiednia opcje za pomoca cyfry z zakresu od x do y: "	 << endl;		
		int wybor;
		cin >> wybor;
		if (stan_uz == 1) { //Zalogowany uzytkownik
				switch(wybor) {
					SetConsoleTextAttribute (kolor, 15);
					case 1:
						break;
					case 2:
						break;
					default:
						system("cls");
						SetConsoleTextAttribute (kolor, 10); 
						cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
						SetConsoleTextAttribute (kolor, 8);
						system("pause");
						system("cls");
						stan = false;
				}
	

		} else if (stan_uz == 0 ) { //Uzytkownik nie jest zalogowany
			switch(wybor) {
				case 1:
					break;
				case 2:
					break;
				default:
					break;
			}		
		}
	} while (stan == false);
}


int main () {
	setlocale(LC_ALL,"polish");
	kolor = GetStdHandle ( STD_OUTPUT_HANDLE);
	menu(stan_uz);
	
}
