#include <iostream>
#include <fstream>
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
        // cout << ">" << p->haslo << endl; // Do debugowania
        cout << " " << p->imie << " " << p->nazwisko << endl;
        cout << " " << p->adres << endl;
        cout << endl;
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
int wczytajKonta(Konto_seg* &pocz)
{
    fstream plik;
    plik.open( "Konta.txt", std::ios::in );

    if(!plik.good())
    {
        cout << "Error: Problem z zaladowaniem danych klientow" << endl;
        return -1;
    }
    //cout << "Zawartosc pliku:" << endl; // Do debugowania

    string dane;
    // Forma zapisu (oddzielone spacjami):
    // [haslo][login][adres][nazwisko][imie]
    string im;
    string naz;
    string log;
    string has;
    string adr;

    while( !plik.eof() )
    {
        getline( plik, dane );
        int n = dane.size();
        int i;

        //cout << "[" << dane << "]" << endl;   // Do debugowania

// Imie
        for(i=n;dane[i]!=32;i--){}
        //cout << dane.substr(i+1) << endl;   // Do debugowania
        im = dane.substr(i+1);
        dane.erase(i);
// Nazwisko
        for(;dane[i]!=32;i--){}
        //cout << dane.substr(i+1) << endl;   // Do debugowania
        naz = dane.substr(i+1);
        dane.erase(i);
// Adres
        for(int s=0;s<4;i--)
        {
            if(dane[i]==32)
                s++;
        } i++;
        //cout << dane.substr(i+1) << endl;   // Do debugowania
        adr = dane.substr(i+1);
        dane.erase(i);
// Login
        for(;dane[i]!=32;i--){}
        //cout << dane.substr(i+1) << endl;   // Do debugowania
        log = dane.substr(i+1);
        dane.erase(i);
// Haslo
        has = dane;

        // Do debugowania
        //cout << "Pobrano: " << im << ", " << naz << ", " << adr << ", " << log << ", " << has << endl;
        //cout << endl;
        dodajKonta(pocz, im, naz, log, has, adr);
    }
    plik.close();
    return 0;
}
