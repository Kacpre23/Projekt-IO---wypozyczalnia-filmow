#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm> 
#include <fstream>
//Biblioteki do kolorów:
#include <windows.h>
#include <iostream>
#include <cstdlib>
//===============================================
#include <conio.h> //polskie znaki -jeszcze nie działają
#include <cctype> //Biblioteka do zmiany wielkości liter

using namespace std;

int stan_uz = 0; //zmienna stan_uz określa czy użytkownik jest zalogowany, czy nie. Odblokowuje to nowe opcje w menu. Domyślnie ustawione na 0 - niezalogowany
int admin = 1; //Uprawnienia administratora
HANDLE kolor; //zmienna przetrzymuj1ca nasze kolorki (tak dzia3a w windowsie)


void wyszukanie();


class Film {
    string Kategoria;
    string Nazwa_Filmu;
    string Rezyser;
    string rok;
    string stan_rezerwacji2;
    friend void wyszukanie();

public:
    Film() {}

    Film(string k, string n, string r, string e, string t) {
        Kategoria = k;
        Nazwa_Filmu = n;
        Rezyser = r;
        rok = e;
        stan_rezerwacji2 = t;
    }

    int sprawdzenie_dostepnosci() 
    {
        return 0;
    }

    int wypozyczenie()
    {
        return 0;
    }

    int zwrot()
    {
        return 0;
    }

    void Dodaj() {
        SetConsoleTextAttribute(kolor, 15);
        string dane;
        cin.sync();
        getline(cin, dane);

        cout << "\nProsze podac tytul filmu: ";
        cin.sync();
        getline(cin, Nazwa_Filmu);

        cout << "\nProsze podac rok produkcji: ";
        cin.sync();
        getline(cin, rok);

        cout << "\nProsze podac Imie i nazwisko rezysera: ";
        cin.sync();
        getline(cin, Rezyser);

        cout << "\nProsze podac kategorie filmu: ";
        cin.sync();
        getline(cin, Kategoria);

        stan_rezerwacji2 = "Dostepny";
        SetConsoleTextAttribute(kolor, 10);
        system("cls");
        cout << "\nFilm zostal poprawnie dodany\n\n";
        SetConsoleTextAttribute(kolor, 8);
        system("pause");
        system("cls");
    }

    void wypisz() {
        SetConsoleTextAttribute(kolor, 15);
        cout << "\nTytul filmu:    \t" << Nazwa_Filmu << endl;
        cout << "Rok produkcji:    \t" << rok << endl;
        cout << "Kategoria filmu:  \t" << Kategoria << endl;
        cout << "Rezyser filmu:    \t" << Rezyser << endl;
        cout << "Stan rezerwacji:  \t" << stan_rezerwacji2 << endl;
        SetConsoleTextAttribute(kolor, 8);
        system("pause");
        system("cls");
    }

    string toString() {
        return (Nazwa_Filmu + " " + rok + "\n" + Rezyser + "\n" + Kategoria + "\n" + stan_rezerwacji2);
    }

    void setStan_rezerwacji(string a) {
        stan_rezerwacji2 = a;
    }

    string getTytul() {
        return	Nazwa_Filmu;
    }

    string getStan_rezerwacji() {
        return stan_rezerwacji2;
    }

    string getKategoria() {
        return Kategoria;
    }
};


class Baza_danych {
    int liczba_filmow = 0;
    vector <Film> baza_danych;
    friend void wyszukanie();

public:
    Baza_danych() {};

    void Dodaj_do_bazy(Film* film) {
        baza_danych.push_back(**&film);
        liczba_filmow++;
        return;
    }

    void Wypisz() {
        SetConsoleTextAttribute(kolor, 15);
        cout << "Ilosc filmow w bazie to: " << liczba_filmow << endl;
        for (int i = 0; i < liczba_filmow; i++) {
            baza_danych[i].wypisz();
            cout << endl;
        }
        cout << endl;
        SetConsoleTextAttribute(kolor, 8);
        system("pause");
    }


    void Dostepnosc(string tytul) {
        int pom = -1;
        for (int i = 0; i < liczba_filmow; i++) {
            if (!tytul.compare(baza_danych[i].getTytul())) { //funckja porównująca stringi
                pom = i;
            }
        }
        if (pom == -1) {
            SetConsoleTextAttribute(kolor, 15);
            cout << "Film obecnie niedostępny. Brak mozliwosci wypozyczenia." << endl;
            SetConsoleTextAttribute(kolor, 8);
            system("pause");
            system("cls");
        }
        else {
            SetConsoleTextAttribute(kolor, 15);
            cout << "Film znajduje sie w wypozyczalni: " << endl;
            baza_danych[pom].wypisz();
            string sr = "Dostepne";
            bool stan = true;
            if (!sr.compare(baza_danych[pom].getStan_rezerwacji())) cout << "Niestety nie mozna go w tej chwili zarezerwowac" << endl;
            if (sr.compare(baza_danych[pom].getStan_rezerwacji())) {
                do {
                    cout << "\nCzy chcesz zarezerwowac film?:\n\n[T] Tak; \t[N] Nie;" << endl;
                    SetConsoleTextAttribute(kolor, 8);
                    cout << "\n\nTwoj wybor: ";
                    SetConsoleTextAttribute(kolor, 15);
                    char wybor;
                    stan = true;
                    cin.sync();
                    cin >> wybor;
                    switch (toupper(wybor)) {
                    case 'T':
                        baza_danych[pom].setStan_rezerwacji("Zarezerwowano");
                        cout << "\nPoprawnie zarezerwowano film \n";
                        baza_danych[pom].wypisz();
                        break;
                    case 'N':
                        break;
                    default:
                        system("cls");
                        SetConsoleTextAttribute(kolor, 10);
                        cout << "Wybrano niepoprawna opcje, prosze sprobowac ponownie\n\n";
                        SetConsoleTextAttribute(kolor, 8);
                        system("pause");
                        system("cls");
                        stan = false;
                        break;
                    }
                } while (stan == false);
            }
            SetConsoleTextAttribute(kolor, 8);
            system("pause");
            system("cls");
        }
    }

    void Wypozycz() {
        SetConsoleTextAttribute(kolor, 8);
        cout << "Podaj tytul filmu ktory chcesz wypozyczyc: ";
        string tytul;
        cin.sync();
        cin >> tytul;
        int i = 0;
        int pom = -1;
        for (int i = 0; i < liczba_filmow; i++) {
            if (!tytul.compare(baza_danych[i].getTytul())) {
                pom = i;
            }
        }
        if (pom == -1) {
            SetConsoleTextAttribute(kolor, 15);
            cout << "Brak filmu w bazie" << endl;
        }
        else {
            baza_danych.erase(baza_danych.begin() + pom); //do vectora
            SetConsoleTextAttribute(kolor, 10);
            cout << "\nFilm zostal poprawnie wypozyczony" << endl;
            SetConsoleTextAttribute(kolor, 8);
            liczba_filmow--;
            system("pause");
            system("cls");
        }
    }

    void Wyszuk_Kategoria()
    {
        odczytajDane();
        vector <string> listaKategorii; // Ma wypisywac dostepne kategorie
        string dane;
        bool duplikat;
        SetConsoleTextAttribute(kolor, 15);

        int n = baza_danych.end() - baza_danych.begin();
        for (int i = 0; i < n; i++)
        {
            duplikat = false;
            dane = baza_danych[i].getKategoria();
            int m = listaKategorii.end() - listaKategorii.begin();
            for (int j = 0; j < m; j++)
            {
                if (listaKategorii[j] == dane)
                {
                    duplikat = true;
                    break;
                }
            }
            if (duplikat == false)
            {
                listaKategorii.push_back(dane);
            }
        }

        n = listaKategorii.end() - listaKategorii.begin();
        cout << "Dostepnych jest " << n << " kategorii:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << " " << listaKategorii[i] << endl;
        }

        string kategoria;
        cout << "Prosze podac nazwe kategori: " << endl;
        SetConsoleTextAttribute(kolor, 8);
        cout << "Kategoria: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        cin >> kategoria;

        n = baza_danych.end() - baza_danych.begin();
        int m = 0;
        for (int i = 0; i < n; i++)
        {
            if (kategoria == baza_danych[i].getKategoria())
            {
                cout << " | " << baza_danych[i].getTytul() << " |" << endl;
                m++;
            }
        }
        if (m == 0)
            cout << "Brak filmow z tej kategorii" << endl;
        cout << endl;
    }

    // Funkcja przeznaczona do odczytu z pliku informacji o filmach
    void odczytajDane()
    {
        fstream plik;
        plik.open("Filmy.txt", ios::in);

        if (!plik.good())
        {
            SetConsoleTextAttribute(kolor, 8);
            cout << "Error: Problem z zaladowaniem danych filmow" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            string dane;
            // Forma zapisu (oddzielone spacjami):
            // [tytul][rok]
            // [rezyser]
            // [kategoria]
            // [stan rezerwacji]
            string tyt; // Tytul
            string kat; // Kategoria
            string rez; // Rezyser
            string rk;  // Rok
            string rz;   // Rezerwacja

            while (!plik.eof())
            {
                getline(plik, dane);
                rk = dane.substr(dane.size() - 4);
                dane.erase(dane.size() - 5);
                tyt = dane;

                getline(plik, dane);
                rez = dane;

                getline(plik, dane);
                kat = dane;

                getline(plik, dane);
                rz = dane;

                Film tmp(kat, tyt, rez, rk, rz);
                baza_danych.push_back(*&tmp);
                liczba_filmow++;
            }
        }
        plik.close();
    }

    // Funkcja przeznaczona do zapisu aktualnego stanu bazy filmow
    void zapiszDane()
    {
        fstream plik;
        plik.open("Filmy.txt", ios::out);
        int n = baza_danych.end() - baza_danych.begin();

        cout << "Zapisywanie: " << n << " filmow..." << endl;

        if (!plik.good())
        {
            SetConsoleTextAttribute(kolor, 8);
            cout << "Error: Problem z zaladowaniem danych filmow" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            string dane;
            // Forma zapisu (oddzielone spacjami):
            // [tytul][rok]
            // [rezyser]
            // [kategoria]
            // [stan rezerwacji]
            string tyt; // Tytul
            string kat; // Kategoria
            string rez; // Rezyser
            string rk;  // Rok
            string rz;   // Rezerwacja

            for (int i = 0; i < n; i++)
            {
                if (i >= 1)
                    plik << endl;
                plik << baza_danych[i].toString();
            }
            cout << "Zapisano" << endl;
        }

        plik.close();
    }
};


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

node* listaloginow = NULL;



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

    Dane_kontaktowe() {}
    Dane_kontaktowe(string i, string n, string ml, string nr, string u, string k, string m, string c)
    {
        imie = i;
        nazwisko = n;
        mail = ml;
        numer_tel = nr;
        ulica = u;
        kodpocztowy = k;
        miasto = m;
        kraj = c;
    }
    void odczytajDane() 
    {
        fstream plik;
        string dane;
        plik.open("DaneKontaktowe.txt", std::ios::in);
        if (!plik.good())
        {
            SetConsoleTextAttribute(kolor, 8);
            cout << "Error: Problem z zaladowaniem danych kontaktowych" << endl;
            system("pause");
            system("cls");
        }

        getline(plik, dane);
        imie = dane;

        getline(plik, dane);
        nazwisko = dane;

        getline(plik, dane);
        mail = dane;

        getline(plik, dane);
        numer_tel = dane;

        getline(plik, dane);
        ulica = dane;

        getline(plik, dane);
        kodpocztowy = dane;

        getline(plik, dane);
        miasto = dane;

        getline(plik, dane);
        kraj = dane;

        plik.close();
    }
    void wyswietl_kontakt()
    {
        odczytajDane();
        SetConsoleTextAttribute(kolor, 15);
        cout << "Cena wypozyczenia kazdego filmu wynosi 10zl" << endl;
        cout << "Imie: " << imie << endl << "Nazwisko: " << nazwisko << endl;
        cout << "Mail: " << mail << endl << "Nr telefonu: " << numer_tel << endl;
        cout << "Ulica: " << ulica << endl << "Miasto: " << miasto << endl;
        cout << "Kod pocztowy: " << kodpocztowy << endl << "Kraj: " << kraj << endl;
        system("pause");
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
    Klient() {};

    Klient(string i, string n, string l, string h, string u, string k, string m, string c)
    {
        imie = i;
        nazwisko = n;
        login = l;
        haslo = h;
        ulica = u;
        kodpocztowy = k;
        miasto = m;
        kraj = c;

    };

    friend void menu(int stan_uz);

    int Rejestracja() //funkcja rejestrujaca
    {
        Klient* p = nast;
        Klient* wsk = new Klient;
        string dane;
        cin.sync();
        getline(cin, dane); 

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Login: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->imie = dane;
       
        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Haslo: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->nazwisko = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Imie: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->login = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Nazwisko: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->haslo = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Adres zamieszkania: \n";
        cout << endl << "Ulica: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->ulica = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Kod pocztowy: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->kodpocztowy = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Miasto: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->miasto = dane;

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Kraj: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, dane);
        wsk->kraj = dane;

        wsk->nast = NULL;
        if (p)
        {
            while (p->nast)
                p = p->nast;
            p->nast = wsk;
        }
        else
        {
            // Weryfikacja
            // nast = wsk; lub delete wsk;

            if (Weryfikacja_konta(listaloginow, wsk->login))
            {
                delete wsk;
                return 0;
            }
            else    // W przypadku powodzenia weryfikacji funkcja
            {       // z automatu takze loguje nwego uzytkownika
                nast = wsk;
                AddToList(listaloginow, wsk->login);

                imie = p->imie;
                nazwisko = p->nazwisko;
                login = p->login;
                haslo = p->haslo;
                ulica = p->ulica;
                kodpocztowy = p->kodpocztowy;
                miasto = p->miasto;
                kraj = p->kraj;

                system("cls");
                cout << "Zarejestrowano pomyslnie" << endl;
                cout << "Witaj " << login << endl;
                system("pause");
                zapiszDane();
                system("cls");

                return 0;
            }
        }
    }

    int Zalogowano(int stan)
    {
        return 1;
    }

    int Logowanie()         // Funkcja logujaca uzytkownika
    {                       // Wykozystuje pola przed lisa
        string l, h;        // kont do przechowywania danych
        Klient* p = nast;  // zalogowanego
        string x;
        cin.sync();
        getline(cin, x); // To musi tutaj byc aby wszystko dzialalo

        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Login: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, l);
        cin.sync();
        SetConsoleTextAttribute(kolor, 8);
        cout << endl << "Haslo: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        getline(cin, h);

        while (p)
        {
            if (p->login == l)
            {
                if (p->haslo == h)
                {
                    imie = p->imie;
                    nazwisko = p->nazwisko;
                    login = p->login;
                    haslo = p->haslo;
                    ulica = p->ulica;
                    kodpocztowy = p->kodpocztowy;
                    miasto = p->miasto;
                    kraj = p->kraj;

                    system("cls");

                    cout << "Zalogowano pomyslnie" << endl;
                    cout << "Witaj " << login << endl;
                    return Zalogowano(stan_uz);
                }
            }
            p = p->nast;
        }
        blad();
        system("pause");
        system("cls");
        return 0;
    }

    int Zmiana_hasla() //funkcja do zmiany hasla
    {
        odczytajDane();
        SetConsoleTextAttribute(kolor, 15);
        string oldhaslo, newhaslo, newhaslo1, dane;
        Klient* p = nast;

        cin.sync();
        getline(cin, dane);

        SetConsoleTextAttribute(kolor, 15);
        cout << "Stare haslo: ";
        SetConsoleTextAttribute(kolor, 8);
        cin.sync();
        getline(cin, oldhaslo);

        if (oldhaslo == haslo)
        {
            SetConsoleTextAttribute(kolor, 15);
            cout << endl << "Nowe haslo: ";
            SetConsoleTextAttribute(kolor, 8);
            cin.sync();
            getline(cin, newhaslo);

            SetConsoleTextAttribute(kolor, 15);
            cout << endl << "Powtorz nowe haslo: ";
            SetConsoleTextAttribute(kolor, 8);
            cin.sync();
            getline(cin, newhaslo1);

            if (newhaslo == newhaslo1)
            {
                SetConsoleTextAttribute(kolor, 10);
                haslo = newhaslo;

                if (p)
                {
                    while (p)    // Zmina hasla w bazie
                    {           // uzytkownikow
                        if (p->login == login)
                        {
                            p->haslo = haslo;
                            break;
                        }
                        p = p->nast;
                    }
                }
                else
                {
                    SetConsoleTextAttribute(kolor, 8);
                    cout << "Error: Brak danych o kontach" << endl;
                    SetConsoleTextAttribute(kolor, 10);
                    system("pause");
                    system("cls");
                }
                SetConsoleTextAttribute(kolor, 8);
                cout << endl << "Haslo zostalo zmienione" << endl;
                zapiszDane();
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

    void odczytajDane() // Uwaga! Ten mechanizm uzywa pierwszego obiektu w liscie
    {                   // tylko do przechowywania adresu "pierwszego" konta
        fstream plik;
        plik.open("Konta.txt", std::ios::in);

        if (!plik.good())
        {
            SetConsoleTextAttribute(kolor, 8);
            cout << "Error: Problem z zaladowaniem danych klientow" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            //cout << "Laduje dane kont..." << endl;  // do debugowania
            while (!plik.eof())
            {
                Klient* p = nast;
                Klient* wsk = new Klient;

                string dane;
                // Forma zapisu (oddzielone spacjami):
                // wiersz 1: [imie]
                // wiersz 2: [nazwisko]
                // wiersz 3: [login]
                // wiersz 4: [haslo]
                // wiersz 5: [ulica]
                // wiersz 6: [kod pocztowy]
                // wiersz 7: [miasto]
                // wiersz 8: [kraj]

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->imie = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->nazwisko = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->login = dane;
                AddToList(listaloginow, dane);

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->haslo = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->ulica = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->kodpocztowy = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->miasto = dane;

                cin.sync();
                getline(plik, dane);
                //cout << dane << endl;   // do debugowania
                wsk->kraj = dane;

                wsk->nast = NULL;
                if (p)
                {
                    while (p->nast)
                        p = p->nast;
                    p->nast = wsk;
                }
                else
                {
                    nast = wsk;
                }
            }
        }
        plik.close();
    }

    void zapiszDane()
    {
        Klient* p = nast;
        int i = 1;
        fstream plik;
        plik.open("Konta.txt", std::ios::out);
        string dane;

        if (!plik.good())
        {
            SetConsoleTextAttribute(kolor, 8);
            cout << "Error: Problem z zapisem danych klientow" << endl;
            system("pause");
            system("cls");
        }
        else
        {
            SetConsoleTextAttribute(kolor, 10);
            cout << "Zapisuje dane klientow..." << endl;
            while (p)
            {
                if (i >= 2)
                    plik << endl;
                plik << p->imie << endl;
                plik << p->nazwisko << endl;
                plik << p->login << endl;
                plik << p->haslo << endl;
                plik << p->ulica << endl;
                plik << p->kodpocztowy << endl;
                plik << p->miasto << endl;
                plik << p->kraj;

                p = p->nast;
                i++;
            }
            SetConsoleTextAttribute(kolor, 10);
            cout << "Zapisano" << endl;
            system("pause");
            system("cls");
        }
        plik.close();
    }

    void blad() {
        SetConsoleTextAttribute(kolor, 8);
        cout << "Error: Login lub haslo sa niepoprawne" << endl;
    }
};


Baza_danych Baza_filmow;
Film film;
Klient Klient;
Dane_kontaktowe DaneKontaktowe;


void wyszukanie()
{
    char wybor;
    bool stan = true;
    string tytul;
    do {
        system("cls");
        stan = true;
        SetConsoleTextAttribute(kolor, 15); //domyślny kolor
        cout << "Prosze wybrac odpowiednia opcje za pomoca litery podanej w nawiasie kwadratowym:\n" << endl;
        cout << " [K] Wyszukiwanie filmu za pomoca kategorii;\n" << " [T] Wyszukiwanie filmu po tytule;\n" << " [Z] Zarezerwuj film" << endl;
        if (admin == 1) {
            SetConsoleTextAttribute(kolor, 10);
            cout << " [D] Dodaj film do bazy danych;\n" << " [W] Wypozycz film;\n" << " [S] Stan filmow" << endl;
        }
        SetConsoleTextAttribute(kolor, 15);
        cout << " [P] Powrot" << endl;
        SetConsoleTextAttribute(kolor, 10);
        if (admin == 1) cout << endl << " [*] - opcje admina" << endl;

        SetConsoleTextAttribute(kolor, 8);
        cout << "\n\nTwoj wybor: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        cin >> wybor;
         string tytul;
        switch (toupper(wybor)) {

            // Wyszukanie za pomoca kategorii
        case 'K':
            system("cls");
            Baza_filmow.Wyszuk_Kategoria();
            stan = false;
            break;

            // Wyszukiwanie filmu po tytule
        case 'T':
            system("cls");
            SetConsoleTextAttribute(kolor, 8);
            cout << "\nProsze wpisac tytul filmu: ";
            SetConsoleTextAttribute(kolor, 15);
            cin.sync();
            getline(cin, tytul);
            Baza_filmow.Dostepnosc(tytul);
            stan = false;
            break;

            // Rezerwacja filmu
        case 'Z':
            SetConsoleTextAttribute(kolor, 8);
            cout << "\nProsze wpisac tytul filmu: ";
            SetConsoleTextAttribute(kolor, 15);
            cin.sync();
            getline(cin, tytul);
            Baza_filmow.Dostepnosc(tytul);
            stan = false;
            break;

            // Dla admina: Dodawanie filmu
        case 'D':
            if (admin == 1)    // Aby nikt nie uruchomil opcji
            {               // admina przez przypadek
                system("cls");
                film.Dodaj();
                Baza_filmow.Dodaj_do_bazy(&film);
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(kolor, 10);
                cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
                SetConsoleTextAttribute(kolor, 8);
                system("pause");
                system("cls");
            }
            stan = false;
            break;

            // Dla admina: Wypozyczane filmu
        case'W':
            if (admin == 1)    // Aby nikt nie uruchomil opcji
            {               // admina przez przypadek
                Baza_filmow.Wypozycz();
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(kolor, 10);
                cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
                SetConsoleTextAttribute(kolor, 8);
                system("pause");
                system("cls");
            }
            stan = false;
            break;

            // Dla admina: Stan filmow
        case'S':
            if (admin == 1)    // Aby nikt nie uruchomil opcji
            {               // admina przez przypadek
                Baza_filmow.Wypisz();
            }
            else
            {
                system("cls");
                SetConsoleTextAttribute(kolor, 10);
                cout << "Wybrono niepoprawna opcje, prosze sprobowac ponownie\n\n";
                SetConsoleTextAttribute(kolor, 8);
                system("pause");
                system("cls");
            }
            stan = false;
            break;

            // Powrot do menu glownego
        case'P':
            system("cls");
            stan = true;
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
    } while (stan == false);
    stan = false;
}


void menu(int stan_uz) {
    bool stan = true; //wykorzystywane do petli for
    do {
        stan = true;
        SetConsoleTextAttribute(kolor, 15); //domyslny kolor
        cout << "Prosze wybrac odpowiednia opcje za pomoca litery podanej w nawiasie kwadratowym: " << endl;
        cout << "\n[L]  Logowanie;\n[R]  Rejestracja;\n[Z]  Zmiana hasla;\n[W]  Wyszukaj film;" << endl;
        cout << "[D]  Dane kontaktowe;\n[X]  Wyjscie;" << endl;
        char wybor;

        SetConsoleTextAttribute(kolor, 8);
        cout << "\n\nTwoj wybor: ";
        SetConsoleTextAttribute(kolor, 15);
        cin.sync();
        cin >> wybor;

        if (stan_uz == 1)   // Gdy klient jest zalogowany
        {
            switch (toupper(wybor)) {
                SetConsoleTextAttribute(kolor, 15);

                //===================UWAGA! Funckie nie przyjmuj1 zmiennych!===================//

            // Logowanie
            case 'L':
                system("cls");
                cout << "Jestes juz zalogowanym uzytkownikiem" << endl;
                SetConsoleTextAttribute(kolor, 8);
                stan = false;
                break;

                // Rejestracja
            case 'R':
                system("cls");
                cout << "Jestes zarejestrowanym uzytkownikiem" << endl;
                SetConsoleTextAttribute(kolor, 8);
                stan = false;
                break;

                // Zmiana hasla
            case 'Z':
                system("cls");
                Klient.Zmiana_hasla();
                stan = false;
                break;

                // Wyszukaj film
            case 'W':
                system("cls");
                wyszukanie();
                stan = false;
                break;


                // Dane kontaktowe
            case 'D':
                system("cls");
                DaneKontaktowe.wyswietl_kontakt();
                stan = false;
                break;

                // Wyjscie
            case 'X':
                cout << "Czy napewno chcesz wyjsc? (t/n)" << endl;
                char d;
                while (true)
                {
                    cin >> d;
                    if (d == 't')
                    {
                        cout << "Do widzenia!" << endl;
                        break;
                    }
                    else if (d == 'n')
                    {
                        stan = false;
                        break;
                    }
                    else
                    {
                        cout << "Niepoprawna opcja" << endl;
                    }
                }
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
        else if (stan_uz == 0)  // Gdy nikt sie jeszcze nie zalogowal
        {
            switch (toupper(wybor)) {

                // Logowanie
            case 'L':
                system("cls");
                Klient.Logowanie();
                stan = false;
                break;

                // Rejestracja
            case 'R':
                system("cls");
                Klient.Rejestracja();
                stan = false;
                break;

                // Zmiana hasla
            case 'Z':
                system("cls");
                SetConsoleTextAttribute(kolor, 8);
                cout << "Odmowa dostepu. Usluga dostepna wylacznie dla zalogowanych uzytkownikow" << endl;
                stan = false;
                break;

                // Wyszukaj film
            case 'W':
                system("cls");
                wyszukanie();
                stan = false;
                break;

                // Dane kontaktowe
            case 'D':
                system("cls");
                DaneKontaktowe.wyswietl_kontakt();
                stan = false;
                break;

                // Wyjscie
            case 'X':
                SetConsoleTextAttribute(kolor, 8);
                cout << "Czy napewno chcesz wyjsc? (t/n)" << endl;
                SetConsoleTextAttribute(kolor, 15);
                char d;
                while (true)
                {
                    cin >> d;
                    if (d == 't')
                    {
                        SetConsoleTextAttribute(kolor, 8);
                        cout << "Do widzenia!" << endl;
                        break;
                    }
                    else if (d == 'n')
                    {
                        stan = false;
                        system("cls");
                        break;
                    }
                    else
                    {
                        SetConsoleTextAttribute(kolor, 10);
                        cout << "Niepoprawna opcja" << endl;
                    }
                }
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
    } while (stan == false);
}


int main()
{
    SetConsoleTextAttribute(kolor, 8);
    setlocale(LC_ALL, "polish");
    kolor = GetStdHandle(STD_OUTPUT_HANDLE);
    Baza_filmow.odczytajDane();

    menu(stan_uz);


    Baza_filmow.zapiszDane();
    Klient.zapiszDane();

    return 0;
}
