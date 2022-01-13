#include <stdio.h>
#include <string>
//Biblioteki do kolorów:
#include <windows.h> //słabe rozwiązanie które raczej (chociaż są wyjątki) będzie działać tylko na Windowsie :/
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie działają
#include <cctype> //Biblioteka do zmiany wielkości liter
int stan_uz = 0; //zmienna stan_uz określa czy użytkownik jest zalogowany, czy nie. Odblokowuje to nowe opcje w menu. Domyślnie ustawione na 0 - niezalogowany

HANDLE kolor; //zmienna przetrzymująca nasze kolorki (tak działa w windowsie)
using namespace std;

struct node {
	string val;
	node* next;
};

void AddToList(node*& H, string x) {
	node* p = new node;
	p->val = x;
	p->next = H;
	H = p;
}

void Show(node* H) {
	cout << "H -> ";
	node* p = H;
	while (p != NULL) {
		cout << p->val << " -> ";
		p = p->next;
	}
	cout << "NULL" << endl;
}

class Dane_kontaktowe
{
public:
    string imie = "Imie";
    string nazwisko = "Nazwisko";
    string mail = "Mail";
    string numer_tel = "123 123 123";
    string ulica = "Ul. ";
    string kodpocztowy = "00-000";
    string miasto = "Krakow";
    string kraj = "Polska";
    void wyswietl_kontakt()
    {
        SetConsoleTextAttribute(kolor, 15);
        cout << "Cena wypożyczenia każdego filmu wynosi 10zl" << endl;
        cout << "Imie: " << imie << endl << "Nazwisko: " << nazwisko << endl;
        cout << "Mail: " << mail << endl << "Nr telefonu: " << numer_tel << endl;
        cout << "Ulica: " << ulica << endl << "Miasto: " << miasto << endl;
        cout << "Kod pocztowy: " << kodpocztowy << endl << "Kraj: " << kraj << endl;
    }
};

class Klient
{
    string imie;
    string nazwisko;
    string login;
    string haslo;
    string ulica;
    string kodpocztowy;
    string miasto;
    string kraj;
    Klient* nast = NULL;
public:
    friend void menu(int stan_uz);
    Klient() {};
    int Rejestracja(node*& listaloginow) //funkcja rejestrujaca
    {
        SetConsoleTextAttribute(kolor, 15);
        nast = new Klient;
        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Login: ";
        cin >> login;
        cout << endl << "Haslo: ";
        cin >> haslo;
        cout << endl << "Imie: ";
        cin >> imie;
        cout << endl << "Nazwisko: ";
        cin >> nazwisko;
        cout << endl << "Adres zamieszkania";
        cout << endl << "Ulica: ";
        cin >> ulica;
        cout << endl << "Kod pocztowy: ";
        cin >> kodpocztowy;
        cout << endl << "Miasto: ";
        cin >> miasto;
        cout << endl << "Kraj: ";
        cin >> kraj;
        if (Weryfikacja_konta(listaloginow, login) == 0)
        {
            Show(listaloginow);
            AddToList(listaloginow, login);
            cout << "Zarejestrowano" << endl;
            Show(listaloginow);
        }
        else
        {
            delete nast;
            cout << "Blad rejestracji, wpisany login juz istnieje" << endl;
            // tu powrot do menu
        }
        return 0;
    }
    int Zalogowano(int stan)
    {
        return 1;
    }

    int Logowanie() //funkcja logujaca
    {
        string l, h;
        do
        {
            SetConsoleTextAttribute(kolor, 15);
            SetConsoleTextAttribute(kolor, 8);
            cout << endl << "Login: ";
            cin >> l;
            cout << endl << "Haslo: ";
            cin >> h;
            if (l == login && h == haslo)
            {
                cout << endl << "Zalogowano" << endl;
                stan_uz = Zalogowano(stan_uz);
            }
            else
            {
                string x;
                SetConsoleTextAttribute(kolor, 10);
                cout << endl << "Blad logowania, czy chcesz sprobowac jeszcze raz?" << endl;
                SetConsoleTextAttribute(kolor, 8);
                cout << "Wpisz T/N" << endl;
                cin >> x;
                if (x == "T" || x == "t")
                {
                    Logowanie();
                }
                if (x == "N" || x == "n")
                {
                    SetConsoleTextAttribute(kolor, 10);
                    cout << "Anulowano logowanie" << endl;
                    // tu przejscie do menu
                }
            }
        } while (stan_uz == 0);
        return stan_uz;

    }

    int Zmiana_hasla() //funkcja do zmiany hasla
    {
        SetConsoleTextAttribute(kolor, 15);
        string oldhaslo, newhaslo, newhaslo1;
        SetConsoleTextAttribute(kolor, 15);
        cout << "Stare haslo: ";
        SetConsoleTextAttribute(kolor, 8);
        cin >> oldhaslo;
        if (oldhaslo == haslo)
        {
            SetConsoleTextAttribute(kolor, 15);
            cout << endl << "Nowe haslo: ";
            SetConsoleTextAttribute(kolor, 8);
            cin >> newhaslo;
            SetConsoleTextAttribute(kolor, 15);
            cout << endl << "Powtorz nowe haslo: ";
            SetConsoleTextAttribute(kolor, 8);
            cin >> newhaslo1;
            if (newhaslo == newhaslo1)
            {
                SetConsoleTextAttribute(kolor, 10);
                haslo = newhaslo;
                cout << endl << "Haslo zostalo zmienione" << endl;
                
            }
            else
            {
                SetConsoleTextAttribute(kolor, 10);
                cout << endl << "Hasla nie sa sobie rowne" << endl;
            }
        }
        else
        {
            SetConsoleTextAttribute(kolor, 10);
            cout << "Stare haslo nieprawidlowe" << endl;
        }
        return 0;
    }

    int Weryfikacja_konta(node*& listaloginow, string login) //funkcja sprawdzajaca czy dane z rejestracji nie powtarzaja sie z innymi uzytkownikami
    {
        if (listaloginow == NULL)
        {
            return 0;
        }
        if (listaloginow != NULL)
        {
            node* p = listaloginow;
            while (p != NULL)
            {
                if (login == p->val)
                {
                    return 1;
                }
                p = p->next;
            }
            if (p == NULL)
            {
                return 0;
            }
        }
    }
};

Klient Klient;
Dane_kontaktowe Dane_kontaktowe;
node* listaloginow = NULL;

void menu(int stan_uz) {
	bool stan = true; //wykorzystywane do pętli for
	do {
		stan = true;
		SetConsoleTextAttribute(kolor, 10); //kolor komunikatów systemu
		cout << "Testowa wersja menu (wiele moze jeszcze ulec zmianie)\n" << endl;
		SetConsoleTextAttribute(kolor, 15); //domyślny kolor
		cout << "Prosze wybrac odpowiednia opcje za pomoca litery podanej w nawiasie kwadratowym: " << endl;
		cout << "\n[L]  Logowanie;\n[R]  Rejestracja;\n[Z]  Zmiana hasla;\n[W]  Wyszukaj film;\n[K]  Kategorie filmów;\n[P]  Proponowane filmy;\n[U]  Lista życzeń;\n[D]  Dane kontaktowe;" << endl;
		char wybor;
		SetConsoleTextAttribute(kolor, 8);
		cout << "\n\nTwój wybór: ";
		SetConsoleTextAttribute(kolor, 15);
		cin >> wybor;
		if (stan_uz == 1) { //Zalogowany uzytkownik
			switch (toupper(wybor)) {
				SetConsoleTextAttribute(kolor, 15);

				//===================UWAGA! Funckie nie przyjmują zmiennych!===================//

			case 'L':
				cout << "Jesteś już zalogowanym użytkownikiem" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				stan = false;
				break;
			case 'R':
				cout << "Jesteś zarejestrowanym użytkownikiem" << endl;
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				stan = false;
				break;
			case 'Z':
                Klient.Zmiana_hasla();
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
                system("cls");
                Dane_kontaktowe.wyswietl_kontakt();
                system("pause");
                stan = false;
				break;
			default:
				system("cls");
				SetConsoleTextAttribute(kolor, 10);
				cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
				SetConsoleTextAttribute(kolor, 8);
				system("pause");
				system("cls");
				stan = false;
				break;
			}


		}
		else if (stan_uz == 0) { //Uzytkownik nie jest zalogowany
			switch (wybor) {
			case 'L':
                system("cls");
                Klient.Logowanie();
                system("pause");
                stan = false;
                break;
			case 'R':
                system("cls");
                Klient.Rejestracja(listaloginow);
                system("pause");
                stan = false;
                break;
			case 'Z':
                cout << "Odmowa dostępu. Usługa dostępna wyłącznie dla zalogowanych użytkowników" << endl;
                stan = false;
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
                system("cls");
                Dane_kontaktowe.wyswietl_kontakt();
				break;
			default:
				break;
			}
		}
	} while (stan == false);
}

int main() {
	setlocale(LC_ALL, "polish");
	kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	menu(stan_uz);

}
