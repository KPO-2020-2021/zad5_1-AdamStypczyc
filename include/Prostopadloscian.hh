#pragma once
#include "Graniastoslup.hh"
/*!
 * \brief Klasa Prostopadloscian.
 * Deklaracja klasy prostopadłościan. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na prostopadłościanie.
 * \param wspol deklaracja prostopadłościanu jako 8 wektorów 3D. Wspol jest skrótem od współrzędna.
 */
class Prostopadloscian : public Graniastoslup
{

public:
    ~Prostopadloscian();
    Prostopadloscian(Wektor3D sro = Wektor3D(), double h = 30, double w = 50, double d = 50, std::string nazwa = "../datasets/prostopadloscian.dat");
};
Prostopadloscian::~Prostopadloscian()
{
    /*delete*/free (wymiar);
}
Prostopadloscian::Prostopadloscian(Wektor3D sro, double h, double w, double d, std::string nazwa)
{
    wymiar = new Wektor3D({w, d, h});
    this->nazwa_pliku = nazwa;
    this->srodek = sro;
    Wektor3D tmp;
    /*!   0________2
     *   /|        /|
     * 6/_|______4/ |
     * |  |      |  |
     * |  |   .ś |  |
     * |  |      |  |
     * |  |1_____|_3|
     * | /       | /
     * |/________|/
     * 7         5
     * 
     */
    tmp = {srodek[0]-(w/2), srodek[1]+(d/2), srodek[2]+(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]-(w/2), srodek[1]+(d/2), srodek[2]-(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]+(w/2), srodek[1]+(d/2), srodek[2]+(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]+(w/2), srodek[1]+(d/2), srodek[2]-(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]+(w/2), srodek[1]-(d/2), srodek[2]+(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]+(w/2), srodek[1]-(d/2), srodek[2]-(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]-(w/2), srodek[1]-(d/2), srodek[2]+(h/2)};
    wspol.push_back(tmp);

    tmp = {srodek[0]-(w/2), srodek[1]-(d/2), srodek[2]-(h/2)};
    wspol.push_back(tmp);
}

