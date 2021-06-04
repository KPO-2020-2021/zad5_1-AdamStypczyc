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
    ~Graniastoslup6();
    Graniastoslup6(Wektor3D sro = Wektor3D(), double h = 15, double r = 20, std::string nazwa = "../datasets/graniastoslup6.dat");
};
Graniastoslup6::~Graniastoslup6()
{
   free(wymiar);
}
Graniastoslup6::Graniastoslup6(Wektor3D sro, double h, double r, std::string nazwa)
{
    double radian = 60 * M_PI / 180;
    wymiar = new Wektor3D({0, 0, h});
    this->nazwa_pliku = nazwa;
    this->srodek = sro;
    Wektor3D tmp;
    for (int i = 0; i < 6; ++i)
    {
        tmp = {r * cos(i * radian), r * sin(i * radian), srodek[2] + (h / 2)};
        wspol.push_back(tmp);
        tmp = {r * cos(i * radian), r * sin(i * radian), srodek[2] - (h / 2)};
        wspol.push_back(tmp);
    }
}