#include <iostream>
#include <string.h>

#include "kontaLista.h"

using namespace std;

/* Wypisywanie calej listy kont */
void wypiszKonta(Konto_seg* &pocz)
{
    Konto_seg * p = pocz;
    int i = 1;
    cout << "Lista struktur:" << endl;
    while(p)
    {
        cout << i << ".[" << p->login << "]" << endl;
        cout << " " << p->imie << endl;
        cout << " " << p->nazwisko << endl;
        cout << " " << p->adres << endl;
        p = p->nast;
        i++;
    }
    cout << endl;
}

/* Dodawanie konta na koniec listy */
void dodajKonta(Konto_seg* &pocz, string im, string naz, string log, string has, string adr)
{
    Konto_seg * p = pocz;
    Konto_seg * wsk = new Konto_seg;

    wsk->imie = im;
    wsk->nazwisko = naz;
    wsk->login = log;
    wsk->haslo = has;
    wsk->adres = adr;

    wsk->nast = NULL;
    if(p)
    {
        while(p->nast)
            p = p->nast;
        p->nast = wsk;
    }
    else
    {
        pocz = wsk;
    }
}

/* Tworzenie nowej listy kont przy pomocy pliku z danymi */
//void wczytajKonta(Konto_seg* &pocz);
