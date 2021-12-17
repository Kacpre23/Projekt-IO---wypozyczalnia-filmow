#include <stdio.h>
#include <string>
//Biblioteki do kolorów:
#include <windows.h> //słabe rozwiązanie które raczej (chociaż są wyjątki) będzie działać tylko na Windowsie :/
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie działają
#include <cctype> //Biblioteka do zmiany wielkości liter
int stan_uz = 1; //zmienna stan_uz określa czy użytkownik jest zalogowany, czy nie. Odblokowuje to nowe opcje w menu. Domyślnie ustawione na 0 - niezalogowany

HANDLE kolor; //zmienna przetrzymująca nasze kolorki (tak działa w windowsie)

using namespace std;


void menu (int stan_uz) {
	bool stan = true; //wykorzystywane do pętli for
	do {
		stan = true;	
		SetConsoleTextAttribute (kolor, 10); //kolor komunikatów systemu
		cout << "Testowa wersja menu (wiele moze jeszcze ulec zmianie)\n" << endl;
		SetConsoleTextAttribute (kolor, 15); //domyślny kolor
		cout << "Prosze wybrac odpowiednia opcje za pomoca litery podanej w nawiasie kwadratowym: "	 << endl;	
		cout << "\n[L]  Logowanie;\n[R]  Rejestracja;\n[Z]  Zmiana hasla;\n[W]  Wyszukaj film;\n[K]  Kategorie filmów;\n[P]  Proponowane filmy;\n[U]  Lista życzeń;\n[D]  Dane kontaktowe;" << endl;
		char wybor;
		SetConsoleTextAttribute (kolor, 8);
		cout << "\n\nTwój wybór: "; 
		SetConsoleTextAttribute (kolor, 15);
		cin >> wybor;
		if (stan_uz == 1) { //Zalogowany uzytkownik
				switch(toupper(wybor)) {
					SetConsoleTextAttribute (kolor, 15);
	
		//===================UWAGA! Funckie nie przyjmują zmiennych!===================//
		
					case 'L':
						cout << "Jesteś już zalogowanym użytkownikiem" << endl;
						SetConsoleTextAttribute (kolor, 8);
						system("pause");
						system("cls");
						stan = false;
						break;
					case 'R':
						cout << "Jesteś zarejestrowanym użytkownikiem" << endl;
						SetConsoleTextAttribute (kolor, 8);
						system("pause");
						system("cls");
						stan = false;
						break;
					case 'Z':
		//				zmiana_hasla();
						break;
					case 'W':
		//				wyszukaj(); 			
						break;
					case 'K':
		//				wyszukaj(); 
						break;
					case 'P':
		//				proponowane(stan_uz);
						break;
					case 'U':
		//				lista_zyczen();  <- Do wyrzucenia?
						break;
					case 'D':
		//				dane_kontaktowe();
					break;
					default:
						system("cls");
						SetConsoleTextAttribute (kolor, 10); 
						cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
						SetConsoleTextAttribute (kolor, 8);
						system("pause");
						system("cls");
						stan = false;
						break;
				}
	

		} else if (stan_uz == 0 ) { //Uzytkownik nie jest zalogowany
			switch(wybor) {
				case 'L':
	//				logowanie();
					break;
				case 'R':
	//				rejestracja();
					break;
				case 'Z':
	//				zmiana_hasla();
					break;
				case 'W':		
	//				wyszukaj();
					break;
				case 'K':
	//				wyszukaj();
					break;
				case 'P':
	//				proponowane(stan_uz);
					break;
				case 'U':
					cout << "Odmowa dostępu. Usługa dostępna wyłącznie dla zalogowanych użytkowników" << endl;
					stan = false;
					break;
				case 8:
	//				dane_kontaktowe();
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
