#pragma once
#include <iomanip>
#include "Graniastoslup.hh"
/*!
 * \brief Klasa Prostopadloscian.
 * Deklaracja klasy prostopadłościan. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na prostopadłościanie.
 * \param wspol deklaracja prostopadłościanu jako 8 wektorów 3D. Wspol jest skrótem od współrzędna.
 */
class Prostopadloscian: public Graniastoslup
{

public:
    Prostopadloscian();                                                            
    Prostopadloscian(Wektor3D poczatek, double h = 0, double w = 0, double d = 0);                        
    void dlugosc();                                                                //sprawdzanie długości boków po obrocie
    void wyswietl_wspolrzedne();

};

/*!
 * \brief Konstruktor parametryczny klasy Prostopadloscian.
 * Tworzy prostopadłościan i przypisuje wartości (x,y,z) do współrzędnych.
 * \param poczatek punkt od którego maja wychodzić wszystkie inne punkty (punkt 0)
 * \param h wartość odpowiadająca wysokości prostopadłościanu
 * \param w wartość odpowiadająca szerokości prostopadłościanu
 * \param d wartość odpowiadająca głębokości prostopadłościanu
 */
Prostopadloscian::Prostopadloscian(Wektor3D poczatek, double h, double w, double d)
{
    for (int i = 0; i < SZER; i++)
    {
        wspol[i] = poczatek;
    }
    wspol[1][0] += w; //
    wspol[2][0] += w; //      7___________ 6
    wspol[2][2] += d; //      /|         /|
    wspol[3][2] += d; //   4 /__________/5|
    wspol[4][1] += h; //    |  |        | |
    wspol[5][0] += w; //    |  |        | |
    wspol[5][1] += h; //    |  |        | |
    wspol[6][0] += w; //    |  |________| |
    wspol[6][1] += h; //    | /3        | /2
    wspol[6][2] += d; //    |/__________|/
    wspol[7][1] += h; //    0           1
    wspol[7][2] += d; //
}

/*!
 * \brief Metoda sprawdzająca długości boków.
 * Metoda sprawdzająca czy odpowiednie boki nowopowstałego prostopadłościanu są sobie równe. Wektory są obliczane ze wzorów matematycnych, tak samo ich długości.
 * Porównywanie długości jest zrobione trochę nadgorliwie, ale to nie szkodzi. Wektory 0 - 3 to dolna podstawa, 4 - 7 to podstawa górna, a 8 - 11 to boki. Na koniec metoda wyświetla 
 * odpowiedni komunikat.
 * \param WekX wektor o numerze X, dzięki któremu poprzez oblicznie jego długości liczone są długości boków prostopadłościanu
 * \param BokX bok prostopadłoscianu o numerze X
 */
void Prostopadloscian::dlugosc()
{
    double Wek0[3], Wek1[3], Wek2[3], Wek3[3], Wek4[3], Wek5[3], Wek6[3], Wek7[3], Wek8[3], Wek9[3], Wek10[3], Wek11[3]; 
    double Bok0, Bok1, Bok2, Bok3, Bok4, Bok5, Bok6, Bok7, Bok8, Bok9, Bok10, Bok11;                                     

    Wek0[0] = wspol[0][0] - wspol[1][0]; //x        
    Wek0[1] = wspol[0][1] - wspol[1][1]; //y        
    Wek0[2] = wspol[0][2] - wspol[1][2]; //z        

    Wek1[0] = wspol[1][0] - wspol[2][0]; //x        
    Wek1[1] = wspol[1][1] - wspol[2][1]; //y
    Wek1[2] = wspol[1][2] - wspol[2][2]; //z

    Wek2[0] = wspol[2][0] - wspol[3][0]; //x
    Wek2[1] = wspol[2][1] - wspol[3][1]; //y
    Wek2[2] = wspol[2][2] - wspol[3][2]; //z

    Wek3[0] = wspol[3][0] - wspol[0][0]; //x
    Wek3[1] = wspol[3][1] - wspol[0][1]; //y
    Wek3[2] = wspol[3][2] - wspol[0][2]; //z

    Wek4[0] = wspol[4][0] - wspol[5][0]; //x
    Wek4[1] = wspol[4][1] - wspol[5][1]; //y
    Wek4[2] = wspol[4][2] - wspol[5][2]; //z

    Wek5[0] = wspol[5][0] - wspol[6][0]; //x
    Wek5[1] = wspol[5][1] - wspol[6][1]; //y
    Wek5[2] = wspol[5][2] - wspol[6][2]; //z

    Wek6[0] = wspol[6][0] - wspol[7][0]; //x
    Wek6[1] = wspol[6][1] - wspol[7][1]; //y
    Wek6[2] = wspol[6][2] - wspol[7][2]; //z

    Wek7[0] = wspol[7][0] - wspol[4][0]; //x
    Wek7[1] = wspol[7][1] - wspol[4][1]; //y
    Wek7[2] = wspol[7][2] - wspol[4][2]; //z

    Wek8[0] = wspol[4][0] - wspol[0][0]; //x
    Wek8[1] = wspol[4][1] - wspol[0][1]; //y
    Wek8[2] = wspol[4][2] - wspol[0][2]; //z

    Wek9[0] = wspol[5][0] - wspol[1][0]; //x
    Wek9[1] = wspol[5][1] - wspol[1][1]; //y
    Wek9[2] = wspol[5][2] - wspol[1][2]; //z

    Wek10[0] = wspol[6][0] - wspol[2][0]; //x
    Wek10[1] = wspol[6][1] - wspol[2][1]; //y
    Wek10[2] = wspol[6][2] - wspol[2][2]; //z

    Wek11[0] = wspol[7][0] - wspol[3][0]; //x
    Wek11[1] = wspol[7][1] - wspol[3][1]; //y
    Wek11[2] = wspol[7][2] - wspol[3][2]; //z

    Bok0 = sqrt(pow(Wek0[0], 2) + pow(Wek0[1], 2) + pow(Wek0[2], 2)); 
    Bok1 = sqrt(pow(Wek1[0], 2) + pow(Wek1[1], 2) + pow(Wek1[2], 2));
    Bok2 = sqrt(pow(Wek2[0], 2) + pow(Wek2[1], 2) + pow(Wek2[2], 2));
    Bok3 = sqrt(pow(Wek3[0], 2) + pow(Wek3[1], 2) + pow(Wek3[2], 2));
    Bok4 = sqrt(pow(Wek4[0], 2) + pow(Wek4[1], 2) + pow(Wek4[2], 2));
    Bok5 = sqrt(pow(Wek5[0], 2) + pow(Wek5[1], 2) + pow(Wek5[2], 2));
    Bok6 = sqrt(pow(Wek6[0], 2) + pow(Wek6[1], 2) + pow(Wek6[2], 2));
    Bok7 = sqrt(pow(Wek7[0], 2) + pow(Wek7[1], 2) + pow(Wek7[2], 2));
    Bok8 = sqrt(pow(Wek8[0], 2) + pow(Wek8[1], 2) + pow(Wek8[2], 2));
    Bok9 = sqrt(pow(Wek9[0], 2) + pow(Wek9[1], 2) + pow(Wek9[2], 2));
    Bok10 = sqrt(pow(Wek10[0], 2) + pow(Wek10[1], 2) + pow(Wek10[2], 2));
    Bok11 = sqrt(pow(Wek11[0], 2) + pow(Wek11[1], 2) + pow(Wek11[2], 2));
    std::cout << std::endl;
    if (std::abs(Bok0 - Bok2) <= MIN_DIFF && std::abs(Bok0 - Bok4) <= MIN_DIFF && std::abs(Bok0 - Bok6) <= MIN_DIFF && std::abs(Bok2 - Bok4) <= MIN_DIFF && std::abs(Bok2 - Bok6) <= MIN_DIFF && std::abs(Bok4 - Bok6) <= MIN_DIFF) 
    {
        std::cout << ":) Naprzeciwległe boki odpowidające szerokości są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok0 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok2 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok4 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok6 << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << ":( Naprzeciwległe boki odpowidające szerokości nie są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok0 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok2 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok4 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok6 << std::endl
                  << std::endl;
    }
    if (std::abs(Bok8 - Bok9) <= MIN_DIFF && std::abs(Bok8 - Bok10) <= MIN_DIFF && std::abs(Bok8 - Bok11) <= MIN_DIFF && std::abs(Bok9 - Bok10) <= MIN_DIFF && std::abs(Bok9 - Bok11) <= MIN_DIFF && std::abs(Bok10 - Bok11) <= MIN_DIFF) 
    {
        std::cout << ":) Naprzeciwległe boki odpowidające wysokości są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok8 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok9 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok10 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok11 << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << ":( Naprzeciwległe boki odpowidające wysokości nie są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok8 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok9 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok10 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok11 << std::endl
                  << std::endl;
    }
    if (std::abs(Bok1 - Bok3) <= MIN_DIFF && std::abs(Bok1 - Bok5) <= MIN_DIFF && std::abs(Bok1 - Bok7) <= MIN_DIFF && std::abs(Bok3 - Bok5) <= MIN_DIFF && std::abs(Bok3 - Bok7) <= MIN_DIFF && std::abs(Bok5 - Bok7) <= MIN_DIFF) 
    {
        std::cout << ":) Naprzeciwległe boki odpowidające głębokości są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok1 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok3 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok5 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok7 << std::endl
                  << std::endl;
    }
    else
    {
        std::cout << ":( Naprzeciwległe boki odpowidające głębokości nie są sobie równe, a ich długości wynoszą: " << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok1 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok3 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok5 << std::endl;
        std::cout << std::fixed << std::setprecision(10) << Bok7 << std::endl
                  << std::endl;
    }
}


std::ostream &operator<<(std::ostream &Strm, const Prostopadloscian &Pr);
std::istream &operator>>(std::istream &Strm, const Prostopadloscian &Pr);

/*!
 * \brief Przeciążenie strumieniowe out dla prostopadłościanu.
 * Umożliwia bezpośrednie wyświetlenie/zapis do pliku współrzędnych prostopadłościanu.
 * \param Pr prostopadłościan odpowiadający wyświetlanemu prostopadłościanowi
 * \param Strm strumień wyjściowy
 * \return Zwraca strumień wyjściowy.
 */
std::ostream &operator<<(std::ostream &Strm, const Prostopadloscian &Pr)
{
    for (int i = 0; i < 4; i++)
    {
        Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[i] << std::endl;
    }
    Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[0] << std::endl
         << std::endl;
    for (int i = 4; i < 8; i++)
    {
        Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[i] << std::endl;
    }
    Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[4] << std::endl
         << std::endl;
    for (int i = 0; i < 4; i++)
    {
        Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[i] << std::endl;
        Strm << std::setw(20) << std::fixed << std::setprecision(10) << Pr[i + 4] << std::endl
             << std::endl;
    }
    return Strm;
}
/*!
 * \brief Przeciążenie strumieniowe in dla prostopadłościanu.
 * Umożliwia bezpośrednie wczytsanie współrzędnych prostopadłościanu.
 * \param Pr prostopadłościan odpowiadający wczytywanemu prostopadłościanowi
 * \param Strm strumień wejściowy
 * \return Zwraca strumień wejściowy.
 */
std::istream &operator>>(std::istream &Strm, const Prostopadloscian &Pr)
{
    for (int i = 0; i < SZER; ++i)
    {
        Strm >> Pr[i];
    }
    std::cout << std::endl;
    return Strm;
}
