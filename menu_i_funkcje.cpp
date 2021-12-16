#include <stdio.h>
#include <string>
//Biblioteki do kolorów:
#include <windows.h> //słabe rozwiązanie które raczej (chociaż są wyjątki) będzie działać tylko na Windowsie :/
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie działają

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
		cout << "Prosze wybrac odpowiednia opcje za pomoca cyfry z zakresu od x do y: "	 << endl;	
		cout << "\n1. Logowanie;\n2. Rejestracja;\n3. Zmiana hasla;\n4. Wyszukaj film;\n5. Kategorie filmów;\n6. Proponowane filmy;\n7. Lista życzeń;\n8. Dane kontaktowe;" << endl;
		int wybor;
		SetConsoleTextAttribute (kolor, 8);
		cout << "\n\nTwój wybór: "; 
		SetConsoleTextAttribute (kolor, 15);
		cin >> wybor;
		if (stan_uz == 1) { //Zalogowany uzytkownik
				switch(wybor) {
					SetConsoleTextAttribute (kolor, 15);
	
		//===================UWAGA! Funckie nie przyjmują zmiennych!===================//
		
					case 1:
						cout << "Jesteś już zalogowanym użytkownikiem" << endl;
						stan = false;
						break;
					case 2:
						cout << "Jesteś zarejestrowanym użytkownikiem" << endl;
						stan = false;
						break;
					case 3:
		//				zmiana_hasla();
						break;
					case 4:
		//				wyszukaj(); 			
						break;
					case 5:
		//				wyszukaj(); 
						break;
					case 6:
		//				proponowane(stan_uz);
						break;
					case 7:
		//				lista_zyczen();  <- Do wyrzucenia?
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
				case 1:
	//				logowanie();
					break;
				case 2:
	//				rejestracja();
					break;
				case 3:
	//				zmiana_hasla();
					break;
				case 4:		
	//				wyszukaj();
					break;
				case 5:
	//				wyszukaj();
					break;
				case 6:
	//				proponowane(stan_uz);
					break;
				case 7:
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
