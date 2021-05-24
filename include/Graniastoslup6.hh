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
    double promien;
    Graniastoslup6();
    Graniastoslup6(Wektor3D poczatek, double h, double r);
};
Graniastoslup6::Graniastoslup6()
{

}
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
    Wektor3D tymczasowy;
    double kat_radian = 60 * M_PI / 180;
    for (int i = 1; i < 7; ++i)
    {
        //górna podstawa
        tymczasowy[0] = poczatek[0] + r * cos(i * kat_radian);
        tymczasowy[1] = poczatek[1] + r * sin(i * kat_radian);
        tymczasowy[2] = poczatek[2] + h;
        wspol.push_back(tymczasowy);
        //dolna podstawa
        tymczasowy[0] = poczatek[0] + r * cos(i * kat_radian);
        tymczasowy[1] = poczatek[1] + r * sin(i * kat_radian);
        tymczasowy[2] = poczatek[2];
        wspol.push_back(tymczasowy);
    }

    tymczasowy[0] = poczatek[0];
    tymczasowy[1] = poczatek[1];
    tymczasowy[2] = poczatek[2] + h;
    wspol.push_back(tymczasowy);

    tymczasowy[0] = poczatek[0];
    tymczasowy[1] = poczatek[1];
    tymczasowy[2] = poczatek[2];
    wspol.push_back(tymczasowy);
}

std::ostream &operator<<(std::ostream &Strm, const Graniastoslup6 &Gr);

/*!
 * \brief Przeciążenie strumieniowe out dla prostopadłościanu.
 * Umożliwia bezpośrednie wyświetlenie/zapis do pliku współrzędnych prostopadłościanu.
 * \param Pr prostopadłościan odpowiadający wyświetlanemu prostopadłościanowi
 * \param Strm strumień wyjściowy
 * \return Zwraca strumień wyjściowy.
 */
std::ostream &operator<<(std::ostream &Strm, const Graniastoslup6 &Gr)
{
    for (int i = 0; i < (int)Gr.wspol.size() - 2; i += 2)
    {
        Strm << Gr[12] << Gr[i] << Gr[i + 1] << Gr[13];
        Strm << std::endl;
    }
    Strm << Gr[12] << Gr[0] << Gr[1] << Gr[13];

    return Strm;
}
