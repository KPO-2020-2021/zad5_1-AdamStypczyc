#pragma once
#include <iomanip>
#include <fstream>
#include <string>
#include "Graniastoslup6.hh"
#include "Prostopadloscian.hh"
#include "ObiektSceny.hh"
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <assert.h>
#include <memory>

class dron : public Graniastoslup6
{
    Prostopadloscian KorpusDrona;
    Graniastoslup6 RotorDrona[4];
    Macierz3x3 MacObrot;
    Macierz3x3 MacObrot2[2];
    int index;
    double kat_orientacji;
    double suma_kat_orientacji;
    std::vector<std::string> pliki;
    Wektor3D srodek;
    Wektor3D sciezka[3];

public:
    dron();
    dron(Wektor3D przesuniecie_korpusu_wzglXY);
    void przypisz_kat_orientacji(double kat);
    void przypisz_punkty_sciezki(double kat = 0, double dlugosc_sciezki = 0);
    void stworz_korpus();
    void stworz_rotory();
    Wektor3D pokaz_srodek() { return srodek; }
    void wybierz_drona(int numer) { index = numer; }
    int ktory_dron() { return index; }
    int Inicjalizacja(int Ind, PzG::LaczeDoGNUPlota &Lacze);
    int Rotacja(PzG::LaczeDoGNUPlota &Lacze);

    void ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    void ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    void ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
    void ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);

    bool ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    bool ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    bool ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
    bool ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
};
dron::dron(Wektor3D przesuniecie_korpusu_wzglXY)
{
    this->kat_orientacji = 0;
    this->suma_kat_orientacji = 0;

    srodek[0] = 100 + przesuniecie_korpusu_wzglXY[0];
    srodek[1] = 100 + przesuniecie_korpusu_wzglXY[1];
    srodek[2] = 0 + przesuniecie_korpusu_wzglXY[2];
}

void dron::przypisz_kat_orientacji(double kat)
{
    kat_orientacji = kat;
    suma_kat_orientacji = suma_kat_orientacji + kat_orientacji;
}
void dron::przypisz_punkty_sciezki(double kat, double dlugosc_sciezki)
{
    double _x, _y;
    double kat_radian = kat * M_PI / 180;
    for (int i = 0; i < 4; ++i)
    {
        sciezka[i] = srodek;
    }
    sciezka[1][2] = 490;
    sciezka[2][2] = 490;
    sciezka[2][0] += dlugosc_sciezki;
    _x = sciezka[2][0];
    _y = sciezka[2][1];
    sciezka[2][0] = _x * cos(kat_radian) - _y * sin(kat_radian);
    sciezka[2][1] = _x * sin(kat_radian) + _y * cos(kat_radian);
    sciezka[3] = sciezka[2];
    sciezka[3][2] = sciezka[3][2] - 490;
}
void dron::stworz_korpus()
{
    Wektor3D poczatek = {0, 0, 0};
    KorpusDrona = Prostopadloscian(poczatek, 70, 70, 70);
}
void dron::stworz_rotory()
{
    Wektor3D poczatek = {0, 0, 0};
    for (int i = 0; i < 4; ++i)
    {
        RotorDrona[i] = Graniastoslup6(poczatek, 20, 30);
    }
}
void dron::ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
    for (int i = 0; i < 8; ++i)
    {
        Korpus[i] = Korpus[i] - Przesuniecie;
    }
    for (int i = 0; i < 8; ++i)
    {
        Korpus[i] = M * Korpus[i];
    }
    for (int i = 0; i < 8; ++i)
    {
        Korpus[i] = Korpus[i] + Przesuniecie;
    }
    Strm << Korpus << std::endl;
}
void dron::ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
    for (int i = 0; i < 8; ++i)
    {
        Korpus[i] = Korpus[i] + Przesuniecie;
    }
    Strm << Korpus << std::endl;
}
void dron::ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
}
void dron::ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
}

bool dron::ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
}
bool dron::ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
    std::ofstream StrmPlikowy;

    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
             << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisWspolrzednychDoStrumieniaProstopadloscianu(StrmPlikowy, Przesuniecie, Korpus);

    StrmPlikowy.close();

    return !StrmPlikowy.fail();
}
bool dron::ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
}
bool dron::ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
}
