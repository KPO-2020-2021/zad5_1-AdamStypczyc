#pragma once
#include "Macierz.hh"
#include "Wektor3D.hh"
#include <fstream>
#include <vector>
/*!
 * \brief Klasa Graniastoslup.
 * Deklaracja klasy prostopadłościan. Zawiera ona elementy i metody potrzebne do wykonywania różnych operacji na prostopadłościanie.
 * \param wspol deklaracja prostopadłościanu jako 8 wektorów 3D. Wspol jest skrótem od współrzędna
 */
class Graniastoslup
{
protected:
    std::vector<Wektor3D> wspol;
    Wektor3D *wymiar;
    Wektor3D srodek;
    std::string nazwa_pliku;

public:
    ~Graniastoslup();
    Wektor3D &operator[](int i);
    const Wektor3D operator[](int i) const;

    void ustaw_srodek(Wektor3D sro);
    void ustaw_nazwa(std::string nazwa);
    Wektor3D pokaz_srodek() const;
    std::string pokaz_nazwa() const;

    void translacja(Wektor3D translacja);
    void rotacja(Macierz3x3 obrot);

    void zapis();
};
/*!
 * \brief Destruktor klasy Graniastoslup.
 */
Graniastoslup::~Graniastoslup()
{
    /*delete*/free (wymiar);
}
/*!
 * \brief Przeciążenie operatora [] set.
 * Umożliwia zmianę wartości poszczególnej wszpółrzędnej prostopadłościanu.
 * \return Zwraca wektor3D odpowiadający interesującej nas współrzędnej.
 */
Wektor3D &Graniastoslup::operator[](int i)
{
    return wspol[i];
}
/*!
 * \brief Przeciążenie operatora [] get.
 * Umożliwia podgląd wartości poszczególnej wszpółrzędnej prostopadłościanu.
 * \return Zwraca wektor3D odpowiadający interesującej nas współrzędnej.
 */
const Wektor3D Graniastoslup::operator[](int i) const
{
    return wspol[i];
}
void Graniastoslup::ustaw_srodek(Wektor3D sro)
{
    this->srodek = sro;
}
void Graniastoslup::ustaw_nazwa(std::string nazwa)
{
    this->nazwa_pliku = nazwa;
}
Wektor3D Graniastoslup::pokaz_srodek() const
{
    return this->srodek;
}
std::string Graniastoslup::pokaz_nazwa() const
{
    return this->nazwa_pliku;
}

void Graniastoslup::translacja(Wektor3D translacja)
{
    for (int i = 0; i < (int)wspol.size(); ++i)
    {
        wspol[i] = wspol[i] + translacja;
    }
    srodek = srodek + translacja;
}

void Graniastoslup::rotacja(Macierz3x3 obrot)
{
    for (int i = 0; i < (int)wspol.size(); ++i)
    {
        wspol[i] = (obrot * wspol[i]);
    }
    srodek = obrot * srodek;
}

void Graniastoslup::zapis()
{
    std::fstream StrmPlikowy;

    Wektor3D translacja_srodka = {0, 0, (*wymiar)[2] / 2};

    StrmPlikowy.open(nazwa_pliku, std::ios::out);

    for (int i = 0; i < (int)wspol.size(); i += 2)
    {
        StrmPlikowy << srodek + translacja_srodka << std::endl;
        for (int j = 0; j < 2; ++j)
        {
            StrmPlikowy << wspol[j + i] << std::endl;
        }
        StrmPlikowy << srodek - translacja_srodka << std::endl
                    << std::endl;
    }

    StrmPlikowy << srodek + translacja_srodka << std::endl;
    for (int i = 0; i < 2; ++i)
    {
        StrmPlikowy << wspol[i] << std::endl;
    }
    StrmPlikowy << srodek - translacja_srodka << std::endl
                << std::endl;
                
    StrmPlikowy.close();
}
