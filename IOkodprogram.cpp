#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

int stan_uz = 0;
HANDLE kolor;

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
    Klient() {};
    int Rejestracja() //funkcja rejestrujaca
    {
        SetConsoleTextAttribute(kolor, 15);
        nast = new Klient;
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
        if (Weryfikacja_danych(login) == 1)
        {
            cout << "Zarejestrowano" << endl;
        }
        else
        {
            delete nast;
            cout << "Blad rejestracji, wpisany login juz istnieje" << endl;
            // tu powrot do menu
        }
        return 0;
    }


    int Logowanie() //funkcja logujaca
    {
        string l, h;
        do 
        {
            SetConsoleTextAttribute(kolor, 15);
            cout << endl << "Login: ";
            cin >> l;
            cout << endl << "Haslo: ";
            cin >> h;
            if (l == login && h == haslo)
            {
                cout << endl << "Zalogowano" << endl;
                stan_uz = 1;
            }
            else
            {
                string x;
                cout << endl << "Blad logowania, czy chcesz sprobowac jeszcze raz?" << endl;
                cout << "Wpisz T/N" << endl;
                cin >> x;
                if (x == "T"||x=="t")
                {
                    Logowanie();
                }
                if (x == "N" || x == "n")
                {
                    cout << "Anulowano logowanie" << endl;
                    // tu przejscie do menu
                }
            }
        } while (stan_uz==0);
        return stan_uz;
        
    }

    int Zmiana_hasla() //funkcja do zmiany hasla
    {
        SetConsoleTextAttribute(kolor, 15);
        string oldhaslo, newhaslo, newhaslo1;
        cout << "Stare haslo: " << endl;
        cin >> oldhaslo;
        if (oldhaslo == haslo)
        {
            cout << endl << "Nowe haslo: ";
            cin >> newhaslo;
            cout << endl << "Powtorz nowe haslo: ";
            cin >> newhaslo1;
            if (newhaslo == newhaslo1)
            {
                cout << endl << "Haslo zostalo zmienione" << endl;
                haslo = newhaslo;
            }
            else
            {
                cout << endl << "Hasla nie sa sobie rowne" << endl;
            }
        }
        else
        {
            cout << "Stare haslo nieprawidlowe" << endl;
        }
        return 0;
    }

    int Weryfikacja_danych(string login) //funkcja sprawdzajaca czy dane z rejestracji nie powtarzaja sie z innymi uzytkownikami
    {
        /*if (login == listalogin)
        {
            cout << "Wpisany login juz istnieje, prosze wybrac inny" << endl;
            // powrot do menu
        }
        return x; // tu zwraca czy prawidlowo zweryfikowano rejestracje
        */
        return 1;
    }
};



int main()
{
    kolor = GetStdHandle(STD_OUTPUT_HANDLE);
    Klient k1;
    k1.Rejestracja();
    k1.Logowanie();
    k1.Zmiana_hasla();
}
