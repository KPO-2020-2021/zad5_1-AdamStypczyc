#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "Prostopadloscian.hh"
#include "Graniastoslup6.hh"
#include "dron.hh"
#include "Scena.hh"
#include "../include/lacze_do_gnuplota.hh"
/*!
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 * 
 * EDIT: dodane kreowanie wektorow i Macierz3x3y plus obsluga lacza do gnuplota
 */
/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */

/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool ZapisWspolrzednychDoPlikuProstopadloscianu(const char *sNazwaPliku, Prostopadloscian Pr)
{
    std::ofstream StrmPlikowy;

    StrmPlikowy.open(sNazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }

    StrmPlikowy << Pr;
    StrmPlikowy.close();
    return !StrmPlikowy.fail();
}
bool ZapisWspolrzednychDoPlikuGraniasto6(const char *sNazwaPliku, Graniastoslup6 Rot)
{
    std::ofstream StrmPlikowy;

    StrmPlikowy.open(sNazwaPliku);
    if (!StrmPlikowy.is_open())
    {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    }

    StrmPlikowy << Rot;
    StrmPlikowy.close();
    return !StrmPlikowy.fail();
}

void pokaz_menu(char &wybor)
{
    std::cout << "Opcje: " << std::endl;
    std::cout << "o - obrot prostopadloscianu o zadaną sekwencję ruchów" << std::endl;
    std::cout << "p - przesuniecie prostopadloscianu o zadany wektor" << std::endl;
    std::cout << "r - wyświetlenie macierzy rotacji" << std::endl;
    std::cout << "s - skalowanie prostopadloscianu o zadany wektor" << std::endl;
    std::cout << "t - powtorzenie poprzedniego obrotu" << std::endl;
    std::cout << "w - wyswietlenie wspolrzednych wierzcholkow" << std::endl;
    std::cout << "m - wyswietl menu" << std::endl;
    std::cout << "d - sprawdź długość boków" << std::endl;
    std::cout << "k - koniec dzialania programu" << std::endl;
    std::cout << "Twoj wybor? (m - menu) > ";
    std::cin >> wybor;
    std::cout << "------------------------------------" << std::endl;
}
int menu()
{
    PzG::LaczeDoGNUPlota Lacze;

    Prostopadloscian korpus;
    Graniastoslup6 rotory[4];
    dron Dron;
    Wektor3D lewy_przedni_dolny_korpus = {0, 0, 0}, srodek = {0, 0, 0}, translacja = {50, 50, 0};
    for (int i = 0; i < 4; ++i)
    {
        rotory[i] = Graniastoslup6(srodek, 2, 3);
    }
    korpus = Prostopadloscian(lewy_przedni_dolny_korpus, 8, 4, 2);
    Dron = dron(korpus, rotory, translacja);

    Lacze.DodajNazwePliku("bryly_wzorcowe/plaszczyzna.dat");
    Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
    Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
    Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
    Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
    Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.Inicjalizuj(); // Tutaj startuje gnuplot.
    std::cout << "Kliknij enter" << std::endl;
    std::cin.ignore(1024, '\n');
    return 1;
}
