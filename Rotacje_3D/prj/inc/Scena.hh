#ifndef SCENA_HH
#define SCENA_HH
#include "Prostopadloscian.hh"

#define POCZATKOWA_ILOSC_STRUKTUR 0
#define ILOSC_STRUKTUR 1000

/*!
 * \file
 * \brief Plik zawiera defnicje struktury Scena 
 *
 * Plik zawiera defnicje struktury Scena, która modeluje pojęcie sceny 
 * 
 *
 */

/*!
 * \brief Definicja Struktury Scena 
 *
 * Struktura Scena modeluje pojecie Sceny i przechwouje Bryłe(typu Prostopadloscian), MAcierzRotacji(typu Macierz3X3) i Ilość powtórzen Operacji Obrotu.
 * Służy do zapamietania ostatniego obrotu Prostopadłościanu.
 *
 */
struct Scena
{
   int PowtorzeniaOperacjiObrotu;
   Prostopadloscian Bryla;
   Macierz3x3 MacierzRotacji;
};

#endif