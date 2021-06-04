#pragma once
#include <unistd.h> //dla usleep
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "lacze_do_gnuplota.hh"

class dron
{
    std::vector<Wektor3D> sciezka;
    PzG::LaczeDoGNUPlota &Lacze;
    Prostopadloscian korpus_orginal;
    Prostopadloscian korpus;
    Graniastoslup6 rotor_orginal[4];
    Graniastoslup6 rotor[4];
    Macierz3x3 obr;
    Wektor3D droga;
    double kat;
    int index;

public:
    dron(int ind, PzG::LaczeDoGNUPlota &Lacze1, Wektor3D polozenie);

    void ruch_pionowy(double pion);
    void przesuniecie(double droga);

    void obrot(double kat_obrotu);
    void obrot_rotorow();

    void zapisz();
    void akcja(char wybor);
    void przypisz_droge(double droga);

    Wektor3D pokaz_srodek() const;
};
dron::dron(int ind, PzG::LaczeDoGNUPlota &Lacze1, Wektor3D polozenie) : Lacze(Lacze1)
{
    kat = 0;
    this->index = ind;
    korpus_orginal.ustaw_nazwa("../datasets/korpus" + std::to_string(index) + ".dat");
    for (int i = 0; i < 4; ++i)
    {
        rotor_orginal[i].ustaw_nazwa("../datasets/rotor" + std::to_string(index) + std::to_string(i) + ".dat");
    }
    Lacze.DodajNazwePliku(korpus_orginal.pokaz_nazwa().c_str(), PzG::RR_Ciagly, 2);
    for (int i = 0; i < 4; ++i)
    {
        Lacze.DodajNazwePliku(rotor_orginal[i].pokaz_nazwa().c_str(), PzG::RR_Ciagly, 2);
    }
    korpus = korpus_orginal;

    korpus.translacja(polozenie);
    for (int i = 0; i < 4; ++i)
    {
        rotor[i] = rotor_orginal[i];
    }
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].translacja(korpus_orginal[2 * i] + polozenie);
    }
    this->droga = this->droga + polozenie;
}

void dron::ruch_pionowy(double pion)
{
    Wektor3D tmp;
    tmp[2] = pion;
    this->droga = this->droga + tmp;
    korpus.rotacja(this->obr);
    korpus.translacja(this->droga);
}
void dron::przesuniecie(double droga)
{
    Wektor3D tmp;
    tmp[0] = droga * cos(kat * M_PI / 180);
    tmp[1] = droga * sin(kat * M_PI / 180);
    this->droga = this->droga + tmp;
    korpus.rotacja(this->obr);
    korpus.translacja(this->droga);
}

void dron::obrot(double kat_obrotu)
{
    this->kat = this->kat + kat_obrotu;
    double radian;
    radian = StopienNaRadianZ(this->kat);
    // double tab[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    // Macierz3x3 tmp = Macierz3x3(tab);
    Macierz3x3 tmp1;
    Oblicz_Macierz_ObrotuZ(radian, tmp1);
    obr = /*tmp */ tmp1;
    korpus.rotacja(obr);
    korpus.translacja(this->droga);
}
void dron::obrot_rotorow()
{
    static int kat = 0;
    kat += 3;
    if (kat == 360)
    {
        kat = 0;
    }
    double tab[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    Macierz3x3 tmp = Macierz3x3(tab);
    Macierz3x3 tmp1;
    double radian;
    radian = StopienNaRadianZ(kat);
    Oblicz_Macierz_ObrotuZ(radian, tmp1);
    tmp = tmp * tmp1;
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].rotacja(tmp);
    }
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].translacja(korpus[2 * i]);
    }
}

void dron::zapisz()
{
    korpus.zapis();
    for (int i = 0; i < 4; ++i)
    {
        rotor[i].zapis();
    }
}
void dron::akcja(char wybor)
{
    double droga;
    double kat;

    zapisz();
    switch (wybor)
    {
    case 'o':
        std::cout << "Podaj kąt o jaki ma się obrócić dron" << std::endl;
        while (1)
        {
            std::cin >> kat;
            if (std::cin.good())
            {
                std::cout << "Przypisano kąt :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano kąta :(" << std::endl;
                std::cout << "Podaj kąt jeszcze raz :(" << std::endl;
            }
        }
        if (kat < 0)
        {
            for (int i = 0; i > kat; --i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(-1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
        }
        else
        {
            for (int i = 0; i < kat; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
        }
        break;
    case 't':
        std::cout << "Podaj długość drogi" << std::endl;
        while (1)
        {
            std::cin >> droga;
            if (std::cin.good())
            {
                std::cout << "Przypisano długość drogi :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano długości drogi :(" << std::endl;
                std::cout << "Podaj długość drogi jeszcze raz :(" << std::endl;
            }
        }
        std::cout << "Podaj kąt o jaki ma się obrócić dron" << std::endl;
        while (1)
        {
            std::cin >> kat;
            if (std::cin.good())
            {
                std::cout << "Przypisano kąt :)" << std::endl;
                break;
            }
            else
            {
                std::cout << "Nieprzypisano kąta :(" << std::endl;
                std::cout << "Podaj kąt jeszcze raz :(" << std::endl;
            }
        }
        if (kat < 0)
        {
            for (int i = 0; i > kat; --i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(-1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
        }
        else
        {
            for (int i = 0; i < kat; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
        }
        przypisz_droge(droga);
        Lacze.DodajNazwePliku("../datasets/sciezka.dat", PzG::RR_Ciagly, 2);
        std::cout << "Wznoszenie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        std::cout << "Lot..." << std::endl;
        for (int i = 0; i < droga; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        std::cout << "Lądowanie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(-1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        break;
    case 'r':
        std::cout << "Wznoszenie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        std::cout << "Lot..." << std::endl;
        for (int i = 0; i < 50; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        for (int i = 0; i < 120; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            obrot(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        for (int j = 0; j < 5; ++j)
        {
            for (int i = 0; i < 50; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                przesuniecie(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
            for (int i = 0; i < 60; ++i)
            {
                korpus = korpus_orginal;
                for (int i = 0; i < 4; ++i)
                {
                    rotor[i] = rotor_orginal[i];
                }
                obrot(1);
                obrot_rotorow();
                zapisz();
                Lacze.Rysuj();
                usleep(25000);
            }
        }
        for (int i = 0; i < 50; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        for (int i = 0; i < 120; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            obrot(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        for (int i = 0; i < 50; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            przesuniecie(1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        std::cout << "Lądowanie..." << std::endl;
        for (int i = 0; i < 400; ++i)
        {
            korpus = korpus_orginal;
            for (int i = 0; i < 4; ++i)
            {
                rotor[i] = rotor_orginal[i];
            }
            ruch_pionowy(-1);
            obrot_rotorow();
            zapisz();
            Lacze.Rysuj();
            usleep(25000);
        }
        break;
    default:
        break;
    }
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
    std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}
void dron::przypisz_droge(double droga)
{
    Wektor3D next = korpus.pokaz_srodek();
    next[2] = 0;
    sciezka.push_back(next);
    next[2] = 400;
    sciezka.push_back(next);
    next[0] = next[0] + droga * cos(kat * M_PI / 180);
    next[1] = next[1] + droga * sin(kat * M_PI / 180);
    sciezka.push_back(next);
    next[2] = 0;
    sciezka.push_back(next);

    std::fstream StrmPlikowy;

    StrmPlikowy.open("../datasets/sciezka.dat", std::ios::out);
    for (int i = 0; i < (int)sciezka.size(); ++i)
    {
        StrmPlikowy << sciezka[i] << std::endl;
    }
    StrmPlikowy.close();
}
Wektor3D dron::pokaz_srodek() const
{
    return korpus.pokaz_srodek();
}
