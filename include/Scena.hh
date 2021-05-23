#pragma once

#include "lacze_do_gnuplota.hh"
#include "dron.hh"
#include <list>

class Scena
{
    std::shared_ptr<dron> aktualny_dron;
    std::list<std::shared_ptr<Obiekt_Sceny>> obiekty;
    std::list<std::shared_ptr<dron>> drony;

public:
    Scena();
    ~Scena();
    int Inicjalizacja(PzG::LaczeDoGNUPlota &Lacze);
    int Menu(PzG::LaczeDoGNUPlota &Lacze);
    void pokaz_menu(char &wybor);
};

Scena::Scena()
{
    Wektor3D wektor = {0, 0, 0};
    std::shared_ptr<dron> dron0 = std::make_shared<dron>(wektor);
    drony.push_back(dron0);

    wektor = {200, 200, 0};
    std::shared_ptr<dron> dron1 = std::make_shared<dron>(wektor);
    drony.push_back(dron1);

    wektor = {400, 400, 0};
    std::shared_ptr<dron> dron2 = std::make_shared<dron>(wektor);
    drony.push_back(dron2);

    wektor = {0, 0, 0};
    std::shared_ptr<Obiekt_Sceny> siatka = std::make_shared<Obiekt_Sceny>(wektor);
    obiekty.push_back(siatka);
}

Scena::~Scena()
{
    obiekty.clear();
    drony.clear();
    aktualny_dron.~shared_ptr();

    std::cout << "  Ilość stworzonych wektorów w trakcie działania programu: " << Wektor3D::ilosc_stworzonych << std::endl;
    std::cout << "  Ilość aktualnie istniejących wektorów:                   " << Wektor3D::ilosc_tymczasowych << std::endl;
    std::cout << "  Ilość aktualnie istniejących obiektów:                   " << Obiekt_Sceny::ilosc_obiektow << std::endl;
}

int Scena::Inicjalizacja(PzG::LaczeDoGNUPlota &Lacze)
{
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj();

    Lacze.UstawZakresX(0, 700);
    Lacze.UstawZakresY(0, 700);
    Lacze.UstawZakresZ(0, 700);

    Lacze.UstawRotacjeXZ(64, 65);

    return 0;
}
void Scena::pokaz_menu(char &wybor)
{
    std::cout << "Opcje: " << std::endl;
    std::cout << "o - obrot drona" << std::endl;
    std::cout << "p - przesuniecie drona o zadany wektor w zadanym kierunku" << std::endl;
    std::cout << "w - wybór aktywnego drona" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl;
    std::cout << "k - koniec dzialania programu" << std::endl;
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> wybor;
    std::cout << "------------------------------------" << std::endl;
}
int Scena::Menu(PzG::LaczeDoGNUPlota &Lacze)
{
    int index = 0;
    Inicjalizacja(Lacze);

    for (std::shared_ptr<Obiekt_Sceny> i : obiekty)
    {
        i->Inicjalizuj(index, Lacze);
        index++;
    }

    char wybor;

    while (1)
    {
        pokaz_menu(wybor);
        switch (wybor)
        {
        case 'o':
            double kat;
            std::cout << "Podaj kąt obrotu: " << std::endl;
            while (1)
            {
                std::cin >> kat;
                if (std::cin.good())
                {
                    aktualny_dron->przypisz_kat_orientacji(kat);
                    break;
                }
                else
                {
                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                }
            }

            aktualny_dron->Rotacja(Lacze);
            break;

        case 'p':
            double kat2, droga;
            std::cout << "Podaj kąt obrotu: " << std::endl;
            while (1)
            {
                std::cin >> kat2;
                if (std::cin.good())
                {
                    aktualny_dron->przypisz_kat_orientacji(kat2);
                    break;
                }
                else
                {
                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                }
            }

            std::cout << "Podaj długość drogi: " << std::endl;
            while (1)
            {
                std::cin >> droga;
                if (std::cin.good())
                {
                    break;
                }
                else
                {
                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                }
            }

            aktualny_dron->Translacja(Lacze, droga, 490);
            break;

        case 'w':
            int nr;
            std::cout << "Aktualnie wybranym dronem jest dron nr: " << aktualny_dron->ktory_dron() << std::endl;
            std::cout << "Jego współrzędne to:" << aktualny_dron->pokaz_srodek() << std::endl;
            for (std::shared_ptr<dron> i : drony)
            {
                std::cout << "Dron: " << i->ktory_dron() << std::endl;
                std::cout << "Współrzędne :" << i->pokaz_srodek() << std::endl;
            }
            std::cout << "Podaj numer drona którego chcesz wybrać" << std::endl;
            std::cout << "Jeśli nie chcesz zmieniać drona wpisz 99" << std::endl;
            std::cout << "Twój wybór: ";

            while (1)
            {
                std::cin >> nr;
                if (std::cin.good())
                {
                    if (nr == 1 || nr == 2 || nr == 3)
                    {
                        for (std::shared_ptr<dron> i : drony)
                        {
                            if (i->ktory_dron() == (nr - 1))
                            {
                                aktualny_dron = i;
                            }
                        }
                        break;
                    }
                    else if (nr == 0)
                    {
                    }
                    else
                    {
                        std::cout << "Wybierz odpowiedni numer drona" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1024, '\n');
                    }
                }
                else
                {
                    std::cout << "Podana liczba nie była liczbą :0\nPodaj wartość jeszcze raz" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1024, '\n');
                }
            }
            break;

        case 'm':
            pokaz_menu(wybor);
            break;

        case 'k':
            std::cout << "Do zobaczenia!!!" << std::endl;
            return 0;
            break;

        default:
            break;
        }
    }
    return 0;
}