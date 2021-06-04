#pragma once
#include <iomanip>
#include "dron.hh"
#define ZAKRES 700
#define POCZATEK \
    {            \
        0, 0, 0  \
    }
#define ROZMIAR 14
#define POLOZENIE_1  \
    {                \
        100, 100, 15 \
    }
#define POLOZENIE_2  \
    {                \
        400, 400, 15 \
    }
class Scena
{
    PzG::LaczeDoGNUPlota Lacze;
    dron *tab_dronow[2];
    Wektor3D siatka[ROZMIAR][ROZMIAR];

public:
    Scena();
    ~Scena();
    bool dzialanie();
    void stworz_siatka(std::string nazwa);
    PzG::LaczeDoGNUPlota pokaz_lacze();
};
PzG::LaczeDoGNUPlota Scena::pokaz_lacze()
{
    return this->Lacze;
}
void Scena::stworz_siatka(std::string nazwa)
{
    std::fstream StrmPlikowy;
    double odstep = (ZAKRES + 50) / ROZMIAR;
    siatka[0][0] = POCZATEK;
    for (int i = 0; i < ROZMIAR; ++i)
    {
        if (i > 0)
        {
            siatka[i][0] = siatka[i - 1][0];
            siatka[i][0][1] += odstep;
        }
        for (int j = 1; j < ROZMIAR; ++j)
        {
            siatka[i][j] = siatka[i][j - 1];
            siatka[i][j][0] += odstep;
        }
    }

    StrmPlikowy.open(nazwa, std::ios::out);
    for (int i = 0; i < ROZMIAR; ++i)
    {
        for (int j = 0; j < ROZMIAR; ++j)
        {
            StrmPlikowy << siatka[i][j] << std::endl;
        }
        StrmPlikowy << std::endl;
    }
    StrmPlikowy << std::endl;
    for (int i = 0; i < ROZMIAR; ++i)
    {
        for (int j = 0; j < ROZMIAR; ++j)
        {
            StrmPlikowy << siatka[j][i] << std::endl;
        }
        StrmPlikowy << std::endl;
    }
    StrmPlikowy << std::endl;
    StrmPlikowy.close();
}
Scena::Scena()
{
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(0, ZAKRES);
    Lacze.UstawZakresY(0, ZAKRES);
    Lacze.UstawZakresZ(0, ZAKRES);

    Lacze.UstawRotacjeXZ(60, 30);
    Lacze.UstawSkaleXZ(1, 1);

    stworz_siatka("../datasets/siatka.dat");
    Lacze.DodajNazwePliku("../datasets/siatka.dat", PzG::RR_Ciagly, 2);
    Wektor3D pozycja = POLOZENIE_1;
    tab_dronow[0] = new dron(0, Lacze, pozycja);
    tab_dronow[0]->zapisz();
    pozycja = POLOZENIE_2;
    tab_dronow[1] = new dron(1, Lacze, pozycja);
    tab_dronow[1]->zapisz();

    Lacze.Rysuj();
}
Scena::~Scena()
{
    free(tab_dronow[0]);
    free(tab_dronow[1]);
}
bool Scena::dzialanie()
{
    int index = 0;
    char wybor;
    std::cout << "Aktualny dron to dron nr: " << index << std::endl;
    while (1)
    {
        std::cout << "------------------------------------" << std::endl;
        std::cout << "Opcje: " << std::endl;
        std::cout << "o - obrot drona o zadany kat" << std::endl;
        std::cout << "t - translacja" << std::endl;
        std::cout << "w - wybor drona" << std::endl;
        std::cout << "m - wyswietl menu" << std::endl;
        std::cout << "r - wykonaj lot zwiadowczny" << std::endl;
        std::cout << "k - koniec dzialania programu" << std::endl;
        std::cout << "Twoj wybor? (m - menu) > ";
        std::cin >> wybor;
        std::cout << "------------------------------------" << std::endl;
        if (wybor == 'w')
        {
            std::cout << "Aktualny dron to dron nr: " << index << std::endl;
            std::cout << "Jego współrzędne to: " << tab_dronow[index]->pokaz_srodek() << std::endl;
            while (1)
            {
                std::cout << "Wpisz 0 lub 1 aby wybrać drona" << std::endl;
                std::cin >> index;
                if (std::cin.good())
                {
                    if (index == 0 || index == 1)
                    {
                        std::cout << "Udało się wybrać drona :)" << std::endl;
                        std::cout << "Aktualny dron to dron nr: " << index << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Nie udało się wybrać drona :(" << std::endl;
                        std::cout << "Wybierz jeszcze raz :(" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Nie udało się wybrać drona :(" << std::endl;
                    std::cout << "Wybierz jeszcze raz :(" << std::endl;
                }
            }
        }
        else if (wybor == 'k')
        {
            std::cout << "--------------------------------------------------------" << std::endl;
            std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
            std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
            std::cout << "--------------------------------------------------------" << std::endl;

            std::cout << "Do zobaczenia!!!" << std::endl;
            break;
        }
        else if (wybor == 'o' || wybor == 't' || wybor == 'r')
        {
            tab_dronow[index]->akcja(wybor);
        }
    }
    return false;
}
