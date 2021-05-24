#pragma once
#include <list>
#include "dron.hh"

class Scena
{
private:
    std::shared_ptr<dron> aktualny_dron;
    std::list<std::shared_ptr<dron>> drony;

public:
    Scena();
    ~Scena();
    void ZapisWspolrzednychDoStrumieniaSiatka(std::ostream &Strm);
    bool ZapisWspolrzednychDoPlikuSiatka(const char *NazwaPliku);
    int Inicjalizacja(PzG::LaczeDoGNUPlota &Lacze);
    int menu(PzG::LaczeDoGNUPlota &Lacze);
};
void Scena::ZapisWspolrzednychDoStrumieniaSiatka(std::ostream &Strm)
{
    Wektor3D siatka[16][16];
    siatka[0][0] = {0, 0, 0};
    for (int i = 0; i < 16; ++i)
    {
        if (i > 0)
        {
            siatka[i][0] = siatka[i - 1][0];
            siatka[i][0][1] += 50;
        }
        for (int j = 1; j < 16; ++j)
        {
            siatka[i][j] = siatka[i][j - 1];
            siatka[i][j][0] += 50;
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            Strm << siatka[i][j] << std::endl;
        }
        Strm << std::endl;
    }
    Strm << std::endl;
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; ++j)
        {
            Strm << siatka[j][i] << std::endl;
        }
        Strm << std::endl;
    }
    Strm << std::endl;
}
bool Scena::ZapisWspolrzednychDoPlikuSiatka(const char *NazwaPliku)
{
    std::ofstream StrmPlikowy;
    StrmPlikowy.open(NazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << NazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }
    ZapisWspolrzednychDoStrumieniaSiatka(StrmPlikowy);

    StrmPlikowy.close();
    return !StrmPlikowy.fail();
}

Scena::Scena()
{
    Wektor3D wek1 = {0, 0, 0};
    std::shared_ptr<dron> Dron0 = std::make_shared<dron>(wek1);
    drony.push_back(Dron0);

    wek1 = {200, 600, 0};
    std::shared_ptr<dron> Dron1 = std::make_shared<dron>(wek1);
    drony.push_back(Dron1);

    wek1 = {500, 200, 0};
    std::shared_ptr<dron> Dron2 = std::make_shared<dron>(wek1);
    drony.push_back(Dron2);

    aktualny_dron = Dron0;
}

Scena::~Scena()
{
    drony.clear();
    aktualny_dron.~shared_ptr();
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "             Ilość stworzonych wektorów: " << Wektor3D::ilosc_stworzonych << std::endl;
    std::cout << "  Ilość aktualnie istniejących wektorów: " << Wektor3D::ilosc_tymczasowych << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
}
void pokaz_menu(char &wybor)
{
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Opcje: " << std::endl;
    std::cout << "o - obrot prostopadloscianu o zadaną sekwencję ruchów" << std::endl;
    std::cout << "t - translacja" << std::endl;
    std::cout << "w - wybor drona" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl;
    std::cout << "r - zrób koło" << std::endl;
    std::cout << "k - koniec dzialania programu" << std::endl;
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> wybor;
    std::cout << "------------------------------------" << std::endl;
}
int Scena::Inicjalizacja(PzG::LaczeDoGNUPlota &Lacze)
{
    //dron dron[3];
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.

    Lacze.UstawZakresX(0, 750);
    Lacze.UstawZakresY(0, 750);
    Lacze.UstawZakresZ(0, 750);
    Lacze.UstawRotacjeXZ(60, 30);
    Lacze.UstawSkaleXZ(1, 1);
    //////////////////
    if (!ZapisWspolrzednychDoPlikuSiatka(SIATKA))
        return 1;
    Lacze.DodajNazwePliku(SIATKA);
    // for (int i = 0; i < 3; ++i)
    // {
    //     dron[i].Inicjalizacja(i,Lacze);
    // }
    /////////////

    Lacze.Rysuj();
    return 0;
}
int Scena::menu(PzG::LaczeDoGNUPlota &Lacze)
{
    Inicjalizacja(Lacze);
    char wybor;
    double kat_obrotu;
    double droga;
    double kat_translacji;
    int wybor_drona;
    while (1)
    {
        pokaz_menu(wybor);
        switch (wybor)
        {
        case 'o':
            std::cout << "  Podaj kąt o jaki ma się obrócić dron: " << std::endl;
            while (1)
            {
                std::cin >> kat_obrotu;
                if (std::cin.good())
                {
                    aktualny_dron->przypisz_kat_orientacji(kat_obrotu);
                    std::cout << "  Przypisano kąt orientacji!!!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "  Podana liczba nie była liczbą :0\n  Podaj kąt obrotu jeszcze raz!" << std::endl;
                }
            }
            for (int i = 0; i < fabs(kat_obrotu); ++i)
            {
                aktualny_dron->Rotacja(Lacze);
                std::cout << "dupa" << std::endl;
            }

            break;

        case 't':
            std::cout << "Podaj kąt pod jakim ma polecieć dron" << std::endl;
            while (1)
            {
                std::cin >> kat_translacji;
                if (std::cin.good())
                {
                    aktualny_dron->przypisz_kat_orientacji(kat_translacji);
                    std::cout << "  Przypisano kąt orientacji!!!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "  Podana liczba nie była liczbą :0\n  Podaj kąt orientacji jeszcze raz!" << std::endl;
                }
            }
            for (int i = 0; i < fabs(kat_translacji); ++i)
            {
                aktualny_dron->Rotacja(Lacze);
            }
            std::cout << "Podaj długość drogi jaką ma przebyc dron" << std::endl;
            while (1)
            {
                std::cin >> droga;
                if (std::cin.good())
                {
                    std::cout << "  Przypisano długość drogi!!!" << std::endl;
                    break;
                }
                else
                {
                    std::cout << "  Podana liczba nie była liczbą :0\n  Długość drogi jeszcze raz!" << std::endl;
                }
            }
            for (int i = 0; i < fabs(kat_translacji); ++i)
            {
                aktualny_dron->Translacja(Lacze, droga);
            }
            break;

        case 'w':
            std::cout << "  Aktualnie wybranym dronem jest: ";
            std::cout << "Dron nr " << aktualny_dron->ktory_dron() + 1 << std::endl;
            std::cout << "Jego współrzędne to : " << aktualny_dron->pokaz_srodek() << std::endl;

            for (std::shared_ptr<dron> i : drony)
            {
                std::cout << " Dron: " << i->ktory_dron() + 1 << std::endl;
                std::cout << " Jego współrzędne to: " << i->pokaz_srodek() << std::endl;
            }
            std::cout << "Podaj numer drona, którym chcesz sterować" << std::endl;
            std::cout << "Twój wybór:  ";
            while (1)
            {
                std::cin >> wybor_drona;
                if (std::cin.good())
                {
                    if (wybor_drona > 0 && wybor_drona < 4)
                    {
                        for (std::shared_ptr<dron> i : drony)
                        {
                            if (i->ktory_dron() == (wybor_drona - 1))
                            {
                                aktualny_dron = i;
                            }
                        }
                        std::cout << "Wybrano drona nr: " << aktualny_dron->ktory_dron() + 1 << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Wybierz drona wpisując 1, 2 lub 3" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Podana liczba nie była liczbą :0\n Podaj liczbę jeszcze raz." << std::endl;
                }
            }

            break;

        case 'm':
            pokaz_menu(wybor);
            break;

            // case 'r':
            //     /* code */
            //     break;

        case 'k':
            std::cout << "Do zobaczenia!!!" << std::endl;
            return 0;
            break;

        default:
            break;
        }
    }
}
