#pragma once
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cmath>
#include <ctime>
#include <assert.h>
#include <memory>
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

class dron : public Graniastoslup6, public Prostopadloscian
{
private:
    Prostopadloscian KorpusDrona;
    Graniastoslup6 RotorDrona[4];
    Macierz3x3 ObrotDr;
    Macierz3x3 ObrotRo[2];
    int index;
    double kat_orientacji;
    double suma_kat_orientacji;
    Wektor3D srodek;
    Wektor3D sciezka[4];

public:
    dron();
    dron(Wektor3D przesuniecie_korpusu_wzglXY);
    void przypisz_kat_orientacji(double kat);
    void stworz_korpus();
    void stworz_rotory();
    void zwroc_pkty_sciezki(Wektor3D &a, Wektor3D &b, Wektor3D &c, Wektor3D &d);
    Wektor3D pokaz_srodek() { return srodek; }
    void wybierz_drona(int numer) { index = numer; }
    int ktory_dron() { return index; }

    int Inicjalizacja(int Ind, PzG::LaczeDoGNUPlota &Lacze);
    int Translacja(PzG::LaczeDoGNUPlota &Lacze, double droga);
    int Rotacja(PzG::LaczeDoGNUPlota &Lacze);

    void ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    void ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    void ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
    void ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);

    bool ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    bool ZapisWspolrzednychDoPlikuProstopadloscianu(const char *NazwaPliku, Wektor3D &Przesuniecie, Prostopadloscian &Korpus);
    bool ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Macierz3x3 &M, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
    bool ZapisWspolrzednychDoPlikuRotora(const char *NazwaPliku, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor);
    bool ZapisWspolrzednychDoPlikuSciezka(const char *NazwaPliku);
};

dron::dron()
{
    this->kat_orientacji = 0;
    this->suma_kat_orientacji = 0;
    srodek = {0, 0, 0};
}

dron::dron(Wektor3D przesuniecie_korpusu_wzglXY)
{
    srodek[0] = 100 + przesuniecie_korpusu_wzglXY[0];
    srodek[1] = 100 + przesuniecie_korpusu_wzglXY[1];
    srodek[2] = 0 + przesuniecie_korpusu_wzglXY[2];
}
void dron::przypisz_kat_orientacji(double kat)
{
    this->kat_orientacji = kat;
    this->suma_kat_orientacji += kat_orientacji;
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
void dron::zwroc_pkty_sciezki(Wektor3D &a, Wektor3D &b, Wektor3D &c, Wektor3D &d)
{
    a = sciezka[0];
    b = sciezka[1];
    c = sciezka[2];
    d = sciezka[3];
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
void dron::ZapisWspolrzednychDoStrumieniaProstopadloscianu(std::ostream &Strm, Wektor3D &Przesuniecie, Prostopadloscian &Korpus)
{
    for (int i = 0; i < 8; ++i)
    {
        Korpus[i] = Korpus[i] + Przesuniecie;
    }
    Strm << Korpus << std::endl;
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
void dron::ZapisWspolrzednychDoStrumieniaRotora(std::ostream &Strm, Wektor3D &Przesuniecie, Graniastoslup6 &Rotor)
{
    for (int i = 0; i < 8; ++i)
    {
        Rotor[i] = Rotor[i] + Przesuniecie;
    }
    Strm << Rotor << std::endl;
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
bool dron::ZapisWspolrzednychDoPlikuSciezka(const char *NazwaPliku)
{
    Wektor3D szlak[4];
    zwroc_pkty_sciezki(szlak[0], szlak[1], szlak[2], szlak[3]);
    std::ofstream StrmPlikowy;
    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    StrmPlikowy << szlak[0] << std::endl
                << szlak[1] << std::endl
                << szlak[2] << std::endl
                << szlak[3] << std::endl
                << std::endl;

    StrmPlikowy.close();
    return !StrmPlikowy.fail();
}
int dron::Inicjalizacja(int Ind, PzG::LaczeDoGNUPlota &Lacze)
{
    stworz_korpus();
    wybierz_drona(Ind);

    if (index == 0)
    {
        Lacze.DodajNazwePliku(KORPUS00, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR00, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR10, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR20, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR30, PzG::RR_Ciagly, 2);
    }
    else if (index == 1)
    {
        Lacze.DodajNazwePliku(KORPUS01, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR01, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR11, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR21, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR31, PzG::RR_Ciagly, 2);
    }
    else if (index == 2)
    {
        Lacze.DodajNazwePliku(KORPUS02, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR02, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR12, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR22, PzG::RR_Ciagly, 2);
        Lacze.DodajNazwePliku(ROTOR32, PzG::RR_Ciagly, 2);
    }
    else
    {
        std::cerr << "Zły numer drona!!!" << std::endl;
    }
    Wektor3D wek = {0, 0, 0};
    int j = 4;
    for (int i = 0; i < 4; ++i)
    {
        RotorDrona[i] = Graniastoslup6(KorpusDrona[j], 10, 15);
        j += 1;
    }
    if (index == 0)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, wek, KorpusDrona))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, wek, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, wek, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, wek, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, wek, RotorDrona[3]))
            return 1;
    }
    else if (index == 1)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, wek, KorpusDrona))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, wek, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, wek, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, wek, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, wek, RotorDrona[3]))
            return 1;
    }
    else if (index == 2)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, wek, KorpusDrona))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, wek, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, wek, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, wek, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, wek, RotorDrona[3]))
            return 1;
    }
    Lacze.Rysuj();

    return 0;
}
int dron::Translacja(PzG::LaczeDoGNUPlota &Lacze, double droga)
{
    double x, y, z[2];
    // double obrot_caly_rad;
    double rad_tmp;

    Wektor3D wek1, wek2, wek3;
    Wektor3D TabWek[4];

    rad_tmp = StopienNaRadianZ(4);
    Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotRo[0]);
    rad_tmp = StopienNaRadianZ(-4);
    Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotRo[1]);

    //obrot_caly_rad = suma_kat_orientacji * M_PI / 180;
    x = droga * cos(rad_tmp);
    y = droga * sin(rad_tmp);
    z[0] = 490;
    z[1] = -490;

    for (int i = 0; i < 4; ++i)
    {
        //obliczanie środka ciężkości rotora
        TabWek[i][0] = RotorDrona[i][13][0];
        TabWek[i][1] = RotorDrona[i][13][1];
        TabWek[i][2] = RotorDrona[i][13][2] + 5;
    }
    if (kat_orientacji >= 0)
    {
        wek1 = {0, 0, z[0]};
        wek2 = {x, y, 0};
        wek3 = {0, 0, z[1]};
    }
    else if (kat_orientacji < 0)
    {
        wek1 = {0, 0, z[0]};
        wek2 = {x, -y, 0};
        wek3 = {0, 0, z[1]};
    }
    sciezka[0] = srodek;
    sciezka[1] = sciezka[0] + wek1;
    sciezka[2] = sciezka[1] + wek2;
    sciezka[3] = sciezka[2] + wek3;

    srodek = srodek + wek2;

    if (!ZapisWspolrzednychDoPlikuSciezka(SCIEZKA))
        return 1;
    Lacze.Rysuj();
    std::cout << "Wznoszenie ..." << std::endl;
    if (index == 0)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, wek1, KorpusDrona))
            return 1;
    }
    else if (index == 1)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, wek1, KorpusDrona))
            return 1;
    }
    else if (index == 2)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, wek1, KorpusDrona))
            return 1;
    }

    if (index == 0)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek1;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, wek1, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, wek1, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, wek1, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, wek1, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek1;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, wek1, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, wek1, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, wek1, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, wek1, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 2)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek1;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, wek1, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, wek1, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, wek1, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, wek1, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    usleep(30000);

    std::cout << "Lot..." << std::endl;
    if (index == 0)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, wek2, KorpusDrona))
            return 1;
    }
    else if (index == 1)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, wek2, KorpusDrona))
            return 1;
    }
    else if (index == 2)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, wek2, KorpusDrona))
            return 1;
    }

    if (index == 0)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek2;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, wek2, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, wek2, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, wek2, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, wek2, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek2;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, wek2, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, wek2, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, wek2, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, wek2, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 2)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek2;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, wek2, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, wek2, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, wek2, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, wek2, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    usleep(30000);

    std::cout << "Lądowanie..." << std::endl;
    if (index == 0)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, wek3, KorpusDrona))
            return 1;
    }
    else if (index == 1)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, wek3, KorpusDrona))
            return 1;
    }
    else if (index == 2)
    {
        if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, wek3, KorpusDrona))
            return 1;
    }

    if (index == 0)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek3;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, wek3, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, wek3, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, wek3, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, wek3, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 1)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek3;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, wek3, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, wek3, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, wek3, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, wek3, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    else if (index == 2)
    {
        for (int i = 0; i < 4; ++i)
        {
            TabWek[i] = TabWek[i] + wek3;
        }
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, wek3, RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, ObrotRo[0], TabWek[0], RotorDrona[0]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, wek3, RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, ObrotRo[1], TabWek[1], RotorDrona[1]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, wek3, RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, ObrotRo[0], TabWek[2], RotorDrona[2]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, wek3, RotorDrona[3]))
            return 1;
        if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, ObrotRo[1], TabWek[3], RotorDrona[3]))
            return 1;

        for (int i = 0; i < 4; ++i)
        {
            //obliczanie środka ciężkości rotora
            TabWek[i][0] = RotorDrona[i][13][0];
            TabWek[i][1] = RotorDrona[i][13][1];
            TabWek[i][2] = RotorDrona[i][13][2] + 5;
        }
    }
    Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    usleep(30000);
    return 0;
}
int dron::Rotacja(PzG::LaczeDoGNUPlota &Lacze)
{
    double rad_tmp;
    rad_tmp = StopienNaRadianZ(4);
    Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotRo[0]);
    rad_tmp = StopienNaRadianZ(-4);
    Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotRo[1]);
    
    Macierz3x3 M_Przod[2], M_Tyl[2];
    
    rad_tmp = StopienNaRadianZ(1);
    Oblicz_Macierz_ObrotuZ(rad_tmp, M_Przod[0]);
    rad_tmp = StopienNaRadianZ(7);
    Oblicz_Macierz_ObrotuZ(rad_tmp, M_Przod[1]);
    
    rad_tmp = StopienNaRadianZ(-1);
    Oblicz_Macierz_ObrotuZ(rad_tmp, M_Tyl[0]);
    rad_tmp = StopienNaRadianZ(-7);
    Oblicz_Macierz_ObrotuZ(rad_tmp, M_Tyl[1]);
    
    Wektor3D TabWek[4];

    for (int i = 0; i < 4; ++i)
    {
        /******************
         * 
         * SEGMENT
         */
        
        //obliczanie środka ciężkości rotora
        TabWek[i][0] = RotorDrona[i][13][0];
        TabWek[i][1] = RotorDrona[i][13][1];
        TabWek[i][2] = RotorDrona[i][13][2] + 5;
        
        
    }
    
    if (kat_orientacji >= 0)
    {
        rad_tmp = StopienNaRadianZ(1);
        Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotDr);

        if (index == 0)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, ObrotDr, srodek, KorpusDrona))
                return 1;
        }
        else if (index == 1)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, ObrotDr, srodek, KorpusDrona))
                return 1;
        }
        else if (index == 2)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, ObrotDr, srodek, KorpusDrona))
                return 1;
        }

        if (index == 0)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, M_Przod[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, M_Przod[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, M_Przod[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, M_Przod[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        else if (index == 1)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, M_Przod[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, M_Przod[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, M_Przod[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, M_Przod[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        else if (index == 2)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, M_Przod[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, M_Przod[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, M_Przod[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, M_Przod[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
        usleep(30000);
    }
    else
    {
        rad_tmp = StopienNaRadianZ(-1);
        Oblicz_Macierz_ObrotuZ(rad_tmp, ObrotDr);

        if (index == 0)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS00, ObrotDr, srodek, KorpusDrona))
                return 1;
        }
        else if (index == 1)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS01, ObrotDr, srodek, KorpusDrona))
                return 1;
        }
        else if (index == 2)
        {
            if (!ZapisWspolrzednychDoPlikuProstopadloscianu(KORPUS02, ObrotDr, srodek, KorpusDrona))
                return 1;
        }

        if (index == 0)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, M_Tyl[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR00, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, M_Tyl[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR10, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, M_Tyl[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR20, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, M_Tyl[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR30, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        else if (index == 1)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, M_Tyl[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR01, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, M_Tyl[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR11, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, M_Tyl[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR21, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, M_Tyl[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR31, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        else if (index == 2)
        {

            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, M_Tyl[0], TabWek[0], RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR02, ObrotDr, srodek, RotorDrona[0]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, M_Tyl[1], TabWek[1], RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR12, ObrotDr, srodek, RotorDrona[1]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, M_Tyl[0], TabWek[2], RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR22, ObrotDr, srodek, RotorDrona[2]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, M_Tyl[1], TabWek[3], RotorDrona[3]))
                return 1;
            if (!ZapisWspolrzednychDoPlikuRotora(ROTOR32, ObrotDr, srodek, RotorDrona[3]))
                return 1;

            for (int i = 0; i < 4; ++i)
            {
                //obliczanie środka ciężkości rotora
                TabWek[i][0] = RotorDrona[i][13][0];
                TabWek[i][1] = RotorDrona[i][13][1];
                TabWek[i][2] = RotorDrona[i][13][2] + 5;
            }
        }
        Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
        usleep(30000);
    }
    return 0;
}
