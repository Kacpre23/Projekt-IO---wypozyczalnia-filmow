#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int stan_uz = 0;

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
    int Rejestracja(Klient* nowy) //funkcja rejestrujaca
    {
        if (nowy == NULL)
        {
            nast = new Klient;
            cout << "Login: " << endl;
            cin >> login;
            cout << "Haslo: " << endl;
            cin >> haslo;
            cout << "Imie: " << endl;
            cin >> imie;
            cout << "Nazwisko: " << endl;
            cin >> nazwisko;
            cout << "Adres zamieszkania" << endl;
            cout << "Ulica: " << endl;
            cin >> ulica;
            cout << "Kod pocztowy: " << endl;
            cin >> kodpocztowy;
            cout << "Miasto: " << endl;
            cin >> miasto;
            cout << "Kraj: " << endl;
            cin >> kraj;
            Weryfikacja_danych(login);
        }
        else
        {
            nowy = nast;
        }
    }


    int Logowanie(string l, string h) //funkcja logujaca
    {
        do 
        {
            cout << "Login: " << endl;
            cin >> l;
            cout << "Haslo: " << endl;
            cin >> h;
            if (l == login && h == haslo)
            {
                cout << "Zalogowano" << endl;
                stan_uz = 1;
            }
            else
            {
                cout << "Blad logowania" << endl;
            }
        } while (stan_uz==1);
        
    }

    int Zmiana_hasla() //funkcja do zmiany hasla
    {
        string oldhaslo, newhaslo, newhaslo1;
        cout << "Stare haslo: " << endl;
        cin >> oldhaslo;
        if (oldhaslo == haslo)
        {
            cout << "Nowe haslo: " << endl;
            cin >> newhaslo;
            cout << "Powtorz nowe haslo: " << endl;
            cin >> newhaslo1;
            if (newhaslo == newhaslo1)
            {
                cout << "Haslo zostalo zmienione" << endl;
                haslo = newhaslo;
            }
            else
            {
                cout << "Hasla nie sa sobie rowne" << endl;
            }
        }
        else
        {
            cout << "Stare haslo nieprawidlowe" << endl;
        }
    }

    void Weryfikacja_danych(string login) //funkcja sprawdzajaca czy dane z rejestracji nie powtarzaja sie z innymi uzytkownikami
    {
        /*if (login == listalogin)
        {
            cout << "Wpisany login juz istnieje, prosze wybrac inny" << endl;
        }*/
    }
};



int main()
{
    
}
