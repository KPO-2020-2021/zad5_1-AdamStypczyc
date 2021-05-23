#pragma once
#include <memory>
#include "Wektor3D.hh"
#include "lacze_do_gnuplota.hh"

class Obiekt_Sceny
{
public:
    static int ilosc_obiektow;
    Obiekt_Sceny();
    ~Obiekt_Sceny();

    virtual int Inicjalizuj(int ind, PzG::LaczeDoGNUPlota &Lacze) = 0;  
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
