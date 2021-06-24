#ifndef SCENA_HH
#define SCENA_HH
#include "Prostopadloscian.hh"

#define POCZATKOWA_ILOSC_STRUKTUR 0
#define ILOSC_STRUKTUR 1000

struct Scena
{
   int PowtorzeniaOperacjiObrotu;
   Prostopadloscian Bryla;
   Macierz3x3 MacierzRotacji;
};

#endif