#include "../tests/doctest/doctest.h"
#include "lacze_do_gnuplota.hh"
#include "Prostopadloscian.hh"
#include "Macierz4x4.hh"
#include "Graniastoslup6.hh"
#include "obsluga.hh"

// TEST_CASE("rysowanie sześciokąta 1")
// {
//     Graniastoslup6 Pr;
//     Wektor3D poczatek ={{0,0,0}};
//     Pr = Graniastoslup6(poczatek, 60, 40);
//     PzG::LaczeDoGNUPlota Lacze;
//     if (!ZapisWspolrzednychDoPliku2("../datasets/gra6.dat", Pr))
//     Lacze.Rysuj();
// }