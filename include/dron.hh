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
    Wektor3D srodek_ciezkosci;
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
    int Translacja(PzG::LaczeDoGNUPlota &Lacze, double kat_wzn, double droga);
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
    for (int i = 0; i < 8; ++i)
    {
        Rotor[i] = Rotor[i] - Przesuniecie;
    }
    for (int i = 0; i < 8; ++i)
    {
        Rotor[i] = M * Rotor[i];
    }
    for (int i = 0; i < 8; ++i)
    {
        Rotor[i] = Rotor[i] + Przesuniecie;
    }
    Strm << Rotor << std::endl;
}
void dron::ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
    for (int i = 0; i < 8; ++i)
    {
        Rotor[i] = Rotor[i] + Przesuniecie;
    }
    Strm << Rotor << std::endl;
}

bool dron::ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
    std::ofstream StrmPlikowy;
    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisWspolrzednychDoStrumieniaProstopadloscianu(StrmPlikowy, M, Przesuniecie, Korpus);

    StrmPlikowy.close();
    return !StrmPlikowy.fail();
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
    std::ofstream StrmPlikowy;

    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisWspolrzednychDoStrumieniaRotora(StrmPlikowy, M, Przesuniecie, Rotor);

    StrmPlikowy.close();

    return !StrmPlikowy.fail();
}
bool dron::ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
    std::ofstream StrmPlikowy;

    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisWspolrzednychDoStrumieniaRotora(StrmPlikowy, Przesuniecie, Rotor);

    StrmPlikowy.close();

    return !StrmPlikowy.fail();
}
int dron::Inicjalizacja(int Ind, PzG::LaczeDoGNUPlota &Lacze)
{
    wybierz_drona(Ind);
    pliki.push_back("datasets/prostopadloscian0" + std::to_string(index) + ".dat");
    pliki.push_back("datasets/graniastoslup0" + std::to_string(index) + ".dat");
    pliki.push_back("datasets/graniastoslup1" + std::to_string(index) + ".dat");
    pliki.push_back("datasets/graniastoslup2" + std::to_string(index) + ".dat");
    pliki.push_back("datasets/graniastoslup3" + std::to_string(index) + ".dat");

    for (int i = 0; i < (int)pliki.size(); ++i)
    {
        Lacze.DodajNazwePliku(&pliki[i][0], PzG::RR_Ciagly, 2);
    }

    Wektor3D wek = {0, 0, 0};
    int j = 0;
    for (int i = 0; i < 4; ++i)
    {
        RotorDrona[i] = Graniastoslup6(KorpusDrona[j], 10, 15);
        j = j + 2;
    }

    if (!ZapisWspolrzednychDoPlikuProstopadloscianu(&pliki[0][0], wek, KorpusDrona))
        return 1;

    for (int i = 1; i < 5; ++i)
    {
        if (ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], wek, RotorDrona[i - 1]))
            return 1;
    }
    Lacze.Rysuj();

    return 0;
}
int dron::Translacja(PzG::LaczeDoGNUPlota &Lacze, double kat_wzn, double droga)
{
    double x, y, z;
    double obrot_caly;
    double kat_wznoszenia;
    double rad_tmp;

    Wektor3D wek = {0, 0, 0};

    Wektor3D wek2;
    Wektor3D wektory[4];

    rad_tmp = StopienNaRadianZ(3);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot2[0]);
    rad_tmp = StopienNaRadianZ(-3);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot2[1]);

    kat_wznoszenia = kat_wzn * M_PI / 180;
    obrot_caly = suma_kat_orientacji * M_PI / 180;
    x = droga * sin(fabs(obrot_caly)) * cos(fabs(kat_wznoszenia));
    y = droga * cos(fabs(obrot_caly)) * cos(fabs(kat_wznoszenia));
    z = droga * sin(fabs(kat_wznoszenia));

    for (int i = 0; i < 4; ++i)
    {
        wektory[i][0] = RotorDrona[i][13][0]; // obliczanie srodka ciezkosci kazdego rotora Drona
        wektory[i][1] = RotorDrona[i][13][1];
        wektory[i][2] = RotorDrona[i][13][2] + 5;
    }

    if (kat_wznoszenia >= 0 && obrot_caly >= 0)
    {
        wek[0] = -x;
        wek[1] = y;
        wek[2] = z;
    }
    else if (kat_wznoszenia >= 0 && obrot_caly < 0)
    {
        wek[0] = x;
        wek[1] = y;
        wek[2] = z;
    }
    else if (kat_wznoszenia < 0 && obrot_caly >= 0)
    {
        wek[0] = -x;
        wek[1] = y;
        wek[2] = -z;
    }
    else if (kat_wznoszenia < 0 && obrot_caly < 0)
    {
        wek[0] = x;
        wek[1] = y;
        wek[2] = -z;
    }

    wek2[0] = wek[0] / 100;
    wek2[1] = wek[1] / 100;
    wek2[2] = wek[2] / 100;

    srodek_ciezkosci = srodek_ciezkosci + wek2;
    srodek = srodek + wek2;

    if (!ZapisWspolrzednychDoPlikuProstopadloscianu(&pliki[0][0], wek2, KorpusDrona))
        return 1;

    for (int i = 1; i < 5; ++i)
    {
        wektory[i - 1][0] = wektory[i - 1][0] + wek2[0];
        wektory[i - 1][1] = wektory[i - 1][1] + wek2[1];
        wektory[i - 1][2] = wektory[i - 1][2] + wek2[2];

        if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], wek2, RotorDrona[i - 1]))
            return 1;

        if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], MacObrot2[(i - 1) % 2], wek2, RotorDrona[i - 1]))
            return 1;

        wektory[i][0] = RotorDrona[i][13][0]; // obliczanie srodka ciezkosci kazdego rotora Drona
        wektory[i][1] = RotorDrona[i][13][1];
        wektory[i][2] = RotorDrona[i][13][2] + 5;
    }
    Lacze.Rysuj();
    usleep(27000);
    return 0;
}
int dron::Rotacja(PzG::LaczeDoGNUPlota &Lacze)
{
    double rad_tmp;

    rad_tmp = StopienNaRadianZ(3);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot2[0]);
    rad_tmp = StopienNaRadianZ(-3);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot2[1]);

    Macierz3x3 MacPrz[2];
    rad_tmp = StopienNaRadianZ(1);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacPrz[0]);
    rad_tmp = StopienNaRadianZ(6);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacPrz[1]);

    Macierz3x3 MacTyl[2];
    rad_tmp = StopienNaRadianZ(-1);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacTyl[0]);
    rad_tmp = StopienNaRadianZ(-6);
    Oblicz_Macierz_ObrotuZ(rad_tmp, MacTyl[1]);

    Wektor3D wektory[4];

    for (int i = 0; i < 4; ++i)
    {
        wektory[i][0] = RotorDrona[i][13][0]; // obliczanie srodka ciezkosci kazdego rotora Drona
        wektory[i][1] = RotorDrona[i][13][1];
        wektory[i][2] = RotorDrona[i][13][2] + 5;
    }

    if (kat_orientacji > 0)
    {
        rad_tmp = StopienNaRadianZ(1);
        Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot);

        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(&pliki[0][0], MacObrot, srodek, KorpusDrona))
            return 1; //obrót wokół własnej osi

        for (int i = 1; i < 5; ++i)
        {
            if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], MacPrz[(i - 1) % 2], wektory[i - 1], RotorDrona[i - 1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], MacObrot, srodek, RotorDrona[i - 1]))
                return 1;

            wektory[i][0] = RotorDrona[i][13][0]; // obliczanie srodka ciezkosci kazdego rotora Drona
            wektory[i][1] = RotorDrona[i][13][1];
            wektory[i][2] = RotorDrona[i][13][2] + 5;
        }
        Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
        usleep(30000);
    }
    else
    {
        rad_tmp = StopienNaRadianZ(-1);
        Oblicz_Macierz_ObrotuZ(rad_tmp, MacObrot);
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(&pliki[0][0], MacObrot, srodek, KorpusDrona))
            return 1; //obrót wokół własnej osi

        for (int i = 1; i < 5; ++i)
        {
            if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], MacTyl[(i - 1) % 2], wektory[i - 1], RotorDrona[i - 1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(&pliki[i][0], MacObrot, srodek, RotorDrona[i - 1]))
                return 1;

            wektory[i][0] = RotorDrona[i][13][0]; // obliczanie srodka ciezkosci kazdego rotora Drona
            wektory[i][1] = RotorDrona[i][13][1];
            wektory[i][2] = RotorDrona[i][13][2] + 5;
        }
        Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
        usleep(30000);
    }

    return 0;
}
