#pragma once
#include "Graniastoslup.hh"
/*!
 * \brief Klasa Graniastoslup6.
 * Deklaracja klasy prostopadłościan. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na prostopadłościanie.
 * \param wspol deklaracja prostopadłościanu jako 8 wektorów 3D. Wspol jest skrótem od współrzędna.
 */
class Graniastoslup6 : public Graniastoslup
{
public:
    Wektor3D srodek[2];
    double promien;
    Graniastoslup6();
    Graniastoslup6(Wektor3D poczatek, double h, double r);
    void dlugosc(); //sprawdzanie długości boków po obrocie
    void wyswietl_wspolrzedne();
    Graniastoslup6 operator+=(const Wektor3D translacja);
};

/*!
 * \brief Konstruktor parametryczny klasy Graniastoslup6.
 * Tworzy prostopadłościan i przypisuje wartości (x,y,z) do współrzędnych.
 * \param poczatek punkt od którego maja wychodzić wszystkie inne punkty (punkt 0)
 * \param h wartość odpowiadająca wysokości prostopadłościanu
 * \param w wartość odpowiadająca szerokości prostopadłościanu
 * \param d wartość odpowiadająca głębokości prostopadłościanu
 */
Graniastoslup6::Graniastoslup6(Wektor3D poczatek, double h, double r)
{
    promien = r;
    double kat_radian = 60 * M_PI / 180;
    srodek[0] = poczatek; //dolny środek
    srodek[1] = poczatek; //górny środek
    srodek[1][2] += h;

    for (int i = 0; i < 6; ++i)
    {
        wspol[i] = srodek[0];
    }
    for (int i = 6; i < 12; ++i)
    {
        wspol[i] = srodek[1];
    }
    wspol[0][0] += r;
    wspol[6][0] += r;
    for (int i = 1; i < 6; ++i)
    {
        wspol[i] = wspol[i - 1];
        double _x, _y;
        _x = wspol[i][0];
        _y = wspol[i][1];
        wspol[i][0] = _x * cos(kat_radian) - _y * sin(kat_radian);
        wspol[i][1] = _x * sin(kat_radian) + _y * cos(kat_radian);
    }
    for (int i = 7; i < 12; ++i)
    {
        wspol[i] = wspol[i - 1];
        double _x, _y;
        _x = wspol[i][0];
        _y = wspol[i][1];
        wspol[i][0] = _x * cos(kat_radian) - _y * sin(kat_radian);
        wspol[i][1] = _x * sin(kat_radian) + _y * cos(kat_radian);
    }
}

std::ostream &operator<<(std::ostream &Strm, const Graniastoslup6 &Pr);
std::istream &operator>>(std::istream &Strm, const Graniastoslup6 &Pr);

/*!
 * \brief Przeciążenie strumieniowe out dla prostopadłościanu.
 * Umożliwia bezpośrednie wyświetlenie/zapis do pliku współrzędnych prostopadłościanu.
 * \param Pr prostopadłościan odpowiadający wyświetlanemu prostopadłościanowi
 * \param Strm strumień wyjściowy
 * \return Zwraca strumień wyjściowy.
 */
std::ostream &operator<<(std::ostream &Strm, const Graniastoslup6 &Pr)
{
    Wektor3D srodek[2];
    srodek[0] = Pr[0];
    srodek[1] = Pr[6];
    srodek[0][0] -= Pr.promien;
    srodek[1][0] -= Pr.promien;
    for (int i = 0; i < 6; ++i)
    {
        Strm << srodek[0] << std::endl;
        for (int j = 0; j < 6; ++j)
        {
            Strm << Pr[i] << std::endl;
            Strm << Pr[i + 6] << std::endl;
        }
        Strm << srodek[1] << std::endl
             << std::endl;
    }
    Strm << srodek[0] << std::endl;
    Strm << Pr[0] << std::endl;
    Strm << Pr[6] << std::endl;
    Strm << srodek[1] << std::endl
         << std::endl;
    return Strm;
}
Graniastoslup6 Graniastoslup6::operator+=(const Wektor3D translacja)
{
    for (int i = 0; i < 2; ++i)
    {
        srodek[i] = srodek[i] + translacja;
    }
    for (int i = 0; i < 12; ++i)
    {
        wspol[i] = wspol[i] + translacja;
    }
    return *this;
}
// /*!
//  * \brief Przeciążenie strumieniowe in dla prostopadłościanu.
//  * Umożliwia bezpośrednie wczytsanie współrzędnych prostopadłościanu.
//  * \param Pr prostopadłościan odpowiadający wczytywanemu prostopadłościanowi
//  * \param Strm strumień wejściowy
//  * \return Zwraca strumień wejściowy.
//  */
// std::istream &operator>>(std::istream &Strm, const Graniastoslup6 &Pr)
// {
//     for (int i = 0; i < SZER; ++i)
//     {
//         Strm >> Pr[i];
//     }
//     std::cout << std::endl;
//     return Strm;
// }
