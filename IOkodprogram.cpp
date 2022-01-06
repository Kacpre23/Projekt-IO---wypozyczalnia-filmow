#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

int stan_uz = 0;
HANDLE kolor;

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
    int Rejestracja(node*& listaloginow) //funkcja rejestrujaca
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
        if (Weryfikacja_danych(listaloginow ,login) == 0)
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

    int Weryfikacja_danych(node*& listaloginow, string login) //funkcja sprawdzajaca czy dane z rejestracji nie powtarzaja sie z innymi uzytkownikami
    {
        SetConsoleTextAttribute(kolor, 15);
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



int main()
{
    kolor = GetStdHandle(STD_OUTPUT_HANDLE);
    Klient k1;
    node* listaloginow = NULL;
    k1.Rejestracja(listaloginow);
    Klient k2, k3;
    k2.Rejestracja(listaloginow);
    k3.Rejestracja(listaloginow);
    k2.Logowanie();
    k3.Logowanie();
}
