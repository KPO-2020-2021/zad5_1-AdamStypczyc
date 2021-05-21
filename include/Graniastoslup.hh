#pragma once
#include <iomanip>
#include "Macierz.hh"
#include "Wektor3D.hh"
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

public:
    Graniastoslup();
    ~Graniastoslup();
    Wektor3D &operator[](int i);
    const Wektor3D operator[](int i) const;
    Graniastoslup operator+(const Wektor3D translacja); //sprawdzanie długości boków po obrocie
    void wyswietl_wspolrzedne();
    Graniastoslup operator*(Macierz3x3 Macierz_obrotu); //mnożenie prostokąt razy macierz
    Graniastoslup &operator*(double skala);
};
/*!
 * \brief Konstruktor bezparametryczny klasy Graniastoslup.
 * Przypisuje wszystkim współrzędnym ten sam punkt (0,0,0)
 */
Graniastoslup::Graniastoslup()
{
    for (int i = 0; i < (int)wspol.size(); i++)
    {
        wspol[i] = Wektor3D();
    }
}
/*!
 * \brief Destruktor klasy Graniastoslup.
 */
Graniastoslup::~Graniastoslup()
{
    wspol.clear();
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
/*!
 * \brief Przeciążenie operatora dodawania.
 * Umożliwia dodanie Wektora3D do prostopadłościanu przesuwając go o zadany wektor.
 * \param translacja Wektor3D odpowiadający wktorowi o jaki chcemy przesunąć prostopadłościan
 * \return Zwraca stary prostopadłościan przesunięty o wektor.
 */
Graniastoslup Graniastoslup::operator+(const Wektor3D translacja)
{
    for (int i = 0; i < SIZE; i++)
    {
        wspol[i] = wspol[i] + translacja;
    }
    return *this;
}

/*!
 * \brief Przeciążenie operatora mnożenia Prostopadłościan*Macierz.
 * Umożliwia mnożenie psrostopadłościanu razy macierz3x3.
 * \param Macierz_obrotu macierz odpowiadająca macierzy obrotu
 * \param _x wartość do której przypiszemy wartość X jednej z współrzędnych prostopadłościanu, żeby nie zmienić przypadkowo wartości i nie operować na błędnej wartości
 * \param _y wartość do której przypiszemy wartość Y jednej z współrzędnych prostopadłościanu, żeby nie zmienić przypadkowo wartości i nie operować na błędnej wartości
 * \param _z wartość do której przypiszemy wartość Z jednej z współrzędnych prostopadłościanu, żeby nie zmienić przypadkowo wartości i nie operować na błędnej wartości
 * \return Zwraca stary prostopadłościan odpowiednio obrócony.
 */
Graniastoslup Graniastoslup::operator*(Macierz3x3 Macierz_obrotu)
{
    Graniastoslup wynik;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            wynik[i][j] += wspol[i][j] * Macierz_obrotu(i, j);
    }
    return wynik;
}
/*!
 * \brief Przeciążenie operatora mnożenia Prostopadłościan*double.
 * Umożliwia mnożenie Prostopadłościanu razy double. Daje to w efekcie jego przeskalowanie.
 * \param skala liczba mówiąca jak bardzo chcemy przesklować prostopadłościan.
 */
Graniastoslup &Graniastoslup::operator*(double skala)
{
    for (int i = 0; i < SIZE; ++i)
    {
        wspol[i] = wspol[i] * skala;
    }
    return *this;
}
/*!
 * \brief Metoda wyświetlająca współrzędne prostopadłościanu.
 */
void Graniastoslup::wyswietl_wspolrzedne()
{
    for (int i = 0; i < SIZE; ++i)
        std::cout << std::setw(20) << std::fixed << std::setprecision(10) << wspol[i] << std::endl;
}
