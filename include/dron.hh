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

class dron: public Graniastoslup6
{
    Prostopadloscian KorpusDrona;
    Graniastoslup6 RotorDrona[4];
    Macierz3x3 MacObrot;
    Macierz3x3 MacObrot2[2];
    int index;
    std::vector<std::string> pliki;
public:
    dron();
    dron(Prostopadloscian korpus, Graniastoslup6 rotory[4], Wektor3D przesuniecie_korpusu_wzglXY);
    void przypisz_kat_orientacji(double kat);
    void przypisz_punkty_sciezki(double h = 0, double kat = 0, double dlugosc_sciezki = 0);
};
dron::dron(Prostopadloscian korpus, Graniastoslup6 rotory[4], Wektor3D przesuniecie_korpusu_wzglXY)
{
    for (int i = 0; i < 8; ++i)
    {
        korpus[i] = korpus[i] + przesuniecie_korpusu_wzglXY;
    }
    for (int i = 0; i < 4; ++i)
    {
        rotory[i] += korpus[i + 4];
    }
    Polozenie[0] = (korpus[0][0] - korpus[2][0]) / 2;
    Polozenie[1] = (korpus[0][1] - korpus[2][1]) / 2;
}

void dron::przypisz_kat_orientacji(double kat)
{
    kat_orientacji = kat;
}
void dron::przypisz_punkty_sciezki(double h, double kat, double dlugosc_sciezki)
{
    double _x, _y;
    double kat_radian = kat * M_PI / 180;
    for (int i = 0; i < 4; ++i)
    {
        sciezka[i] = Polozenie;
    }
    sciezka[1][2] += h;
    sciezka[2][2] += h;
    sciezka[2][0] += dlugosc_sciezki;
    _x = sciezka[2][0];
    _y = sciezka[2][1];
    sciezka[2][0] = _x * cos(kat_radian) - _y * sin(kat_radian);
    sciezka[2][1] = _x * sin(kat_radian) + _y * cos(kat_radian);
    sciezka[3] = sciezka[2];
    sciezka[3][2] -= h;
}
