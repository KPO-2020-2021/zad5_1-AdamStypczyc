#pragma once
#include <memory>
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"

class Obiekt_Sceny
{
public:
    std::vector<Wektor3D> siatka;
    Wektor3D operator[](unsigned int Index)
    {
        assert(Index < 64);
        return siatka[Index];
    }
    const Wektor3D operator[](unsigned int Index) const
    {
        assert(Index < 64);
        return siatka[Index];
    }
    void stworz_siatke();
    static int ilosc_obiektow;
    Obiekt_Sceny();
    ~Obiekt_Sceny();
};
int Obiekt_Sceny::ilosc_obiektow = 0;
Obiekt_Sceny::Obiekt_Sceny()
{
    ilosc_obiektow++;
}
Obiekt_Sceny::~Obiekt_Sceny()
{
    ilosc_obiektow--;
}
void Obiekt_Sceny::stworz_siatke()
{
    Wektor3D poczatek = {0, 0, 0};
    for (int i = 0; i < 8; ++i)
    {
        siatka.push_back(poczatek);
        for (int j = 0; j < 7; ++j)
        {
            poczatek[0] = poczatek[0] + 50;
            siatka.push_back(poczatek);
        }
        poczatek[0] = 0;
        poczatek[1] = poczatek[1] + 50;
    }
}
std::ostream operator<<(std::ostream &Strm, Obiekt_Sceny podloze)
{
    for (int i = 0; i < 64; ++i)
    {
        if (i > 0)
        {
            if (i % 8 == 0)
            {
                Strm << std::endl;
            }
        }
        Strm << podloze[i];
    }
    for (int i = 0; i < 8; ++i)
    {
        Strm << podloze[i] << podloze[i + 8] << podloze[i + 16] << podloze[i + 24] << podloze[i + 32] << podloze[i + 40] << podloze[i + 48] << podloze[i + 56] << std::endl;
    }
}