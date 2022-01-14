#include <iostream>
#include <string.h>

using namespace std;

struct Film_seg    // Segment listy kont
{
    /* Dane */
    string tytul; // Tytul
    string kategoria; // Kategoria
    string rezyser; // Rezyser
    string rok;  // Rok
    /* Wskaznik do nastepnego */
    Film_seg * nast;
};

void wypiszFilmy(Film_seg* &pocz);

void dodajFilmy(Film_seg* &pocz, string tyt, string kat, string rez, string rk);

int wczytajFilmy(Film_seg* &pocz);

void wyszukajFilm(Film_seg* &pocz, string log);

void wyszukajFilmKategoriami(Film_seg* &pocz, string log);

