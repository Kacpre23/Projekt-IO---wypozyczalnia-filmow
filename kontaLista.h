#include <iostream>
#include <string.h>

using namespace std;

struct Konto_seg    // Segment listy kont
{
    /* Dane */
    string imie;
    string nazwisko;
    string login;
    string haslo;
    string adres;
    /* Wskaznik do nastepnego */
    Konto_seg * nast;
};

void wypiszKonta(Konto_seg* &pocz);

void dodajKonta(Konto_seg* &pocz, string im, string naz, string log, string has, string adr);

void wczytajKonta(Konto_seg* &pocz);
