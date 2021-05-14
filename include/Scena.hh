#pragma once

#include "lacze_do_gnuplota.hh"
#include "dron.hh"

class Scena
{
    dron Drony[2];
    PzG::LaczeDoGNUPlota Lacze;

public:
    // dron wybierz_aktywnego_drona() const;
};
// dron Scena::wybierz_aktywnego_drona() const
// {
//     double nr=0;
//     std::cout << "Którym dronem chcesz poruszać?" << std::endl << "Wpisz 1 lub 2" << std::endl;
//     while (nr != 1 && nr != 2)
//     {
//         std::cin >> nr;
//         if (nr == 1)
//         {
//             return Drony[0];
//         }
//         else if (nr == 2)
//         {
//             return Drony[1];
//         }
//         else
//         {
//             std::cout << "Zły numer!!!\nPodaj wartość jeszcze raz!!!" << std::endl;
//         }
//     }
// }