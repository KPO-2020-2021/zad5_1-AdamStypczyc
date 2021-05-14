#ifndef MACIERZ_HH
#define MACIERZ_HH

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "wektor.hh"
#include "Wektor3D.hh"
/*!
* \brief Szablon macierzy.
* Szablon ten jest szablonem klasy macierz. Zawiera on elementy potrzebne do utworzenia macierzy oraz wykonywania na niej różnych operacji.
* Zawiera on tablicę o rozmiarach odopowiadających naszej macierzy oraz kąty potrzebne do obrotów 2D i 3D (kąty X, Y, Z).
* \param value tablica przechowująca wartości macierzy
* \param kat_stopnie kąt odpowiadający stopniom przy obrotach 2D
* \param kat_radian kąt odpowiadający stopniom w radianach przy obrotach 2D
* \param kat_stopnieX kąt odpowiadający stopniom przy obrotach 3D w obrotach wokół osi OX
* \param kat_radianX kąt odpowiadający stopniom w radianach przy obrotach 3D w obrotach wokół osi OX
* \param kat_stopnieY kąt odpowiadający stopniom przy obrotach 3D w obrotach wokół osi OY
* \param kat_radianY kat_radianX kąt odpowiadający stopniom w radianach przy obrotach 3D w obrotach wokół osi OY
* \param kat_stopnieZ kąt odpowiadający stopniom przy obrotach 3D w obrotach wokół osi OZ
* \param kat_radianZ kat_radianX kąt odpowiadający stopniom w radianach przy obrotach 3D w obrotach wokół osi OZ
*/

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
class Macierz
{

private:
    Templ_Typ value[Templ_Rozmiar][Templ_Rozmiar]; // Wartosci macierzy
    double kat_stopnie;
    double kat_radian;
    double kat_stopnieX;
    double kat_radianX;
    double kat_stopnieY;
    double kat_radianY;
    double kat_stopnieZ;
    double kat_radianZ;

public:
    Macierz(Templ_Typ tmp[Templ_Rozmiar][Templ_Rozmiar]); 

    Macierz(); 

    Macierz operator+(Macierz tmp);
    Macierz operator-(Macierz tmp);
    Macierz operator*(Macierz tmp);

    Templ_Typ &operator()(unsigned int row, unsigned int column);

    const Templ_Typ &operator()(unsigned int row, unsigned int column) const;
    void StopienNaRadian();
    void StopienNaRadianX();
    void StopienNaRadianY();
    void StopienNaRadianZ();

    void Oblicz_Macierz_Obrotu();
    void Oblicz_Macierz_ObrotuX();
    void Oblicz_Macierz_ObrotuY();
    void Oblicz_Macierz_ObrotuZ();
    void Oblicz_Macierz4x4(double katX, double katY, double katZ, Wektor3D V);

    void przypisz_stopnie(double stopnie);
    void przypisz_stopnieX(double stopnie);
    void przypisz_stopnieY(double stopnie);
    void przypisz_stopnieZ(double stopnie);

    bool operator==(const Macierz tmp) const;
};

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Konstruktor parametryczny klasy macierz.
 * Konstruktor ten nadaje wartości macierzy poprzez tablicę odpowiadającą jej wymiarom.
 * \param tmp tablica poprzez którą będziemy nadawać wartości macierzy 
 */
Macierz<Templ_Typ, Templ_Rozmiar>::Macierz(Templ_Typ tmp[Templ_Rozmiar][Templ_Rozmiar])
{
    for (unsigned int index = 0; index < Templ_Rozmiar; ++index)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            value[index][j] = tmp[index][j];
        }
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Konstruktor bezparametryczny klasy macierz.
 * Konstruktor wypełnia macierz zerami.
 */
Macierz<Templ_Typ, Templ_Rozmiar>::Macierz()
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            value[i][j] = 0;
        }
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora dodawania.
 * Przeciążenie operatora dodawania, aby umożliwić dodawanie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z dodawanych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej dodawania.
 * \return Wynik dodawania w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator+(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            result(i, j) = this->value[i][j] + tmp(i, j);
        }
    }
    return result;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora odejmowania.
 * Przeciążenie operatora odejmowania, aby umożliwić odejmowanie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z odejmowanych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej odejmowania.
 * \return Wynik odejmowania w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator-(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            result(i, j) = this->value[i][j] - tmp(i, j);
        }
    }
    return result;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora mnożenia Macierz*Macierz.
 * Przeciążenie operatora mnożenia, aby umożliwić mnożenie dwóch macierzy.
 * \param tmp macierz odpowiadająca jednej z mnożonych macierzy.
 * \param result macierz pomocnicza odpowiadająca macierzy wynikowej mnożenia.
 * \return Wynik mnożenia w postaci macierzy result.
 */
Macierz<Templ_Typ, Templ_Rozmiar> Macierz<Templ_Typ, Templ_Rozmiar>::operator*(Macierz<Templ_Typ, Templ_Rozmiar> tmp)
{
    Macierz result = Macierz();
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            for (unsigned int k = 0; k < Templ_Rozmiar; ++k)
            {
                result(i, j) += this->value[i][k] * tmp(k, j);
            }
        }
    }
    return result;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora () set.
 * Umożliwia zmienienie wartości konkretnego elementu macierzy.
 * \param row odpowiednik numeru wiersza.
 * \param column odpowiednik numeru kolumny
 * \return Zwraca wartość elementu, który nas interesuje.
 */
Templ_Typ &Macierz<Templ_Typ, Templ_Rozmiar>::operator()(unsigned int row, unsigned int column)
{
    if (row >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0);
    }

    if (column >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0);
    }
    return value[row][column];
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora () get.
 * Umożliwia podgląd wartości konkretnego elementu macierzy.
 * \param row odpowiednik numeru wiersza.
 * \param column odpowiednik numeru kolumny
 * \return Zwraca wartość elementu, który nas interesuje.
 */
const Templ_Typ &Macierz<Templ_Typ, Templ_Rozmiar>::operator()(unsigned int row, unsigned int column) const
{
    if (row >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    if (column >= Templ_Rozmiar)
    {
        std::cout << "Error: Macierz jest poza zasiegiem";
        exit(0); // lepiej byłoby rzucić wyjątkiem stdexcept
    }

    return value[row][column];
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Zamaina stopni na radian 2D.
 * Metoda zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 2D.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::StopienNaRadian()
{
    kat_radian = kat_stopnie * M_PI / 180;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Zamaina stopni na radian 3D wokół OX.
 * Metoda zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OX.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::StopienNaRadianX()
{
    kat_radianX = kat_stopnieX * M_PI / 180;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Zamaina stopni na radian 3D wokół OY.
 * Metoda zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OY.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::StopienNaRadianY()
{
    kat_radianY = kat_stopnieY * M_PI / 180;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Zamaina stopni na radian 3D wokół OZ.
 * Metoda zamieniająca wartość stopni na stopnie w radianach, aby umożliwić obrót 3D wokół osi OZ.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::StopienNaRadianZ()
{
    kat_radianZ = kat_stopnieZ * M_PI / 180;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda obliczająca macierz obrotu 2D.
 * Metoda umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 2D.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::Oblicz_Macierz_Obrotu()
{
    if (Templ_Rozmiar == 2)
    {
        value[0][0] = cos(kat_radian);
        value[0][1] = -sin(kat_radian);
        value[1][0] = sin(kat_radian);
        value[1][1] = cos(kat_radian);
    }
    else
    {
        std::cerr << "Błąd!!!" << std::endl;
    }
}
template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda obliczająca macierz obrotu 3D OX.
 * Metoda umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OX.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::Oblicz_Macierz_ObrotuX()
{
    if (Templ_Rozmiar == 3)
    {
        value[0][0] = 1;
        value[0][1] = 0;
        value[0][2] = 0;
        value[1][0] = 0;
        value[1][1] = cos(kat_radianX);
        value[1][2] = -sin(kat_radianX);
        value[2][0] = 0;
        value[2][1] = sin(kat_radianX);
        value[2][2] = cos(kat_radianX);
    }
    else
    {
        std::cerr << "Błąd!!!" << std::endl;
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda obliczająca macierz obrotu 3D OY.
 * Metoda umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OY.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::Oblicz_Macierz_ObrotuY()
{
    if (Templ_Rozmiar == 3)
    {
        value[0][0] = cos(kat_radianY);
        value[0][1] = 0;
        value[0][2] = sin(kat_radianY);
        value[1][0] = 0;
        value[1][1] = 1;
        value[1][2] = 0;
        value[2][0] = -sin(kat_radianY);
        value[2][1] = 0;
        value[2][2] = cos(kat_radianY);
    }
    else
    {
        std::cerr << "Błąd!!!" << std::endl;
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda obliczająca macierz obrotu 3D OZ.
 * Metoda umożliwiająca obliczenie macierzy obrotu umożliwiającej obrót 3D wokół osi OZ.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::Oblicz_Macierz_ObrotuZ()
{
    if (Templ_Rozmiar == 3)
    {
        value[0][0] = cos(kat_radianZ);
        value[0][1] = -sin(kat_radianZ);
        value[0][2] = 0;
        value[1][0] = sin(kat_radianZ);
        value[1][1] = cos(kat_radianZ);
        value[1][2] = 0;
        value[2][0] = 0;
        value[2][1] = 0;
        value[2][2] = 1;
    }
    else
    {
        std::cerr << "Błąd!!!" << std::endl;
    }
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda przypisująca stopnie 2D.
 * Metoda przypisuje stopnie podane przez użytkownika do stopni macierzy, aby umożliwić obrót 2D.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::przypisz_stopnie(double stopnie)
{
    kat_stopnie = stopnie;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda przypisująca stopnie 3D OX.
 * Metoda przypisuje stopnie podane przez użytkownika do stopni macierzy, aby umożliwić obrót 3D wokół osi OX.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::przypisz_stopnieX(double stopnie)
{
    kat_stopnieX = stopnie;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda przypisująca stopnie 3D OY.
 * Metoda przypisuje stopnie podane przez użytkownika do stopni macierzy, aby umożliwić obrót 3D wokół osi OY.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::przypisz_stopnieY(double stopnie)
{
    kat_stopnieY = stopnie;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Metoda przypisująca stopnie 3D OZ.
 * Metoda przypisuje stopnie podane przez użytkownika do stopni macierzy, aby umożliwić obrót 3D wokół osi OZ.
 */
void Macierz<Templ_Typ, Templ_Rozmiar>::przypisz_stopnieZ(double stopnie)
{
    kat_stopnieZ = stopnie;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora porównania dla macierzy.
 * Przeciążenie operatora porównania umożliwiające porównywanie dwóch macierzy, potrzebne przede wszystkim do testów.
 * \param tmp macierz odpowiadająca jednej z porównywanych macierzy
 * \param liczenie ilość "punktów" odpowiadających ilości zgadzających się elementów macierzy, powinna odpowiadać ilości elementów macierzy
 * \return Zwraca true albo false w zależności czy ilośc punktów odpowiada elementom macierzy. 
 */
bool Macierz<Templ_Typ, Templ_Rozmiar>::operator==(const Macierz<Templ_Typ, Templ_Rozmiar> tmp) const
{
    int liczenie = 0;
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            if (std::abs(value[i][j] - tmp(i, j)) <= MIN_DIFF)
            {
                ++liczenie;
            }
        }
    }
    if (liczenie == pow(Templ_Rozmiar, 2))
    {
        return true;
    }
    return false;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora strumieniowego in dla macierzy.
 * Umożliwia bezpośredie wczytanie macierzy.
 * \param in strumień wejściowy 
 * \param mat macierz odpowiadająca wczytywanej macierzy
 * \return Zwraca strumień wejściowy in. 
 */
std::istream &operator>>(std::istream &in, Macierz<Templ_Typ, Templ_Rozmiar> &mat)
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            in >> mat(i, j);
        }
    }
    return in;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
/*!
 * \brief Przeciążenie operatora strumieniowego out dla macierzy.
 * Umożliwia bezpośredie wyświetlenie macierzy.
 * \param out strumień wyjściowy 
 * \param mat macierz odpowiadająca wyświetlaniej macierzy
 * \return Zwraca strumień wyjściowy out. 
 */
std::ostream &operator<<(std::ostream &out, Macierz<Templ_Typ, Templ_Rozmiar> const &mat)
{
    for (unsigned int i = 0; i < Templ_Rozmiar; ++i)
    {
        for (unsigned int j = 0; j < Templ_Rozmiar; ++j)
        {
            out << "| " << mat(i, j) << " | ";
        }
        std::cout << std::endl;
    }
    return out;
}

template <typename Templ_Typ, unsigned int Templ_Rozmiar>
void Macierz<Templ_Typ, Templ_Rozmiar>::Oblicz_Macierz4x4(double katX, double katY, double katZ, Wektor3D V)
{
    double radianX, radianY, radianZ;
    radianX = katX * M_PI / 180;
    radianY = katY * M_PI / 180;
    radianZ = katZ * M_PI / 180;
    value[0][0] = cos(radianX) * cos(radianY);
    value[0][1] = cos(radianX) * sin(radianY) * sin(radianZ) - sin(radianX) * cos(radianZ);
    value[0][2] = cos(radianX) * sin(radianY) * cos(radianZ) + sin(radianX) * sin(radianZ);
    value[0][3] = V[0];
    value[1][0] = sin(radianX) * cos(radianY);
    value[1][1] = sin(radianX) * sin(radianY) * sin(radianZ) + cos(radianX) * cos(radianZ);
    value[1][2] = sin(radianX) * sin(radianY) * cos(radianZ) - cos(radianX) * sin(radianZ);
    value[1][3] = V[1];
    value[2][0] = -sin(radianY);
    value[2][1] = cos(radianY) * sin(radianZ);
    value[2][2] = cos(radianY) * cos(radianZ);
    value[2][3] = V[2];
    value[3][0] = 0;
    value[3][1] = 0;
    value[3][2] = 0;
    value[3][3] = 1;
}
#endif