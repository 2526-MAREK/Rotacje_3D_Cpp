#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include "Macierz.hh"
#include "Macierz3x3.hh"

#define ILOSC_WIERZCHOLKOW 8
#define ILOSC_BOKOW 4
#define EPSILON 0.000000000001

/*!
 * \file 
 * \brief Definicja klasy Prostopadloscian
 *
 *  Plik zawiera definicję klasy Prostopadloscian, która modeluje Prostopadlośćian w 3 wymiarach.
 */

/*!
 * \brief Klasa modeluje pojęcie Prostopadłościanu w 3 wymiarach
 * 
 * Klasa modeluje pojęcie Prostopadłościanu w 3 wymiarach. Zawiera informacje o współrzednych 
 * wierzchołków prostopadłościanu i długości boków odpowiednio: Najkróßszych, Długiego i Poprzecznego
 * 
 */
class Prostopadloscian {
private:
/*!
 * \brief Tablica trójwymiarowych Wierzchołków Prostopadłościanu
 * 
 * Pole klasy zawiera dane na temat wierzchołków Prostopadłościanu w tablicy statycznej o rozmiarze w zależności od ilości wierzchołków
 * Nasz prostopadłościan posiada 8 wierzchołków w trój-wymiarze. Tablica jest typu Wektor3D który pozwala na przechowanie 
 * Jednego wierzchołka w trój-wymiarze( współrzedne x,y,z)
 * 
 */
  Wektor3D Wierzcholek[ILOSC_WIERZCHOLKOW];
  /*!
 * \brief Tablica DlugosciBokowKrotkich Prostopadłościanu
 * 
 * Pole klasy zawiera dane w tablicy statycznej na temat DługościBokowKrotkich Prostopadłościanu
 * 
 */
  double DlugoscBokuKrotkiego[ILOSC_BOKOW];
  /*!
 * \brief Tablica DlugosciBokowKrotkich Prostopadłościanu
 * 
 * Pole klasy zawiera dane w tablicy statycznej na temat DługościBokowDlugich Prostopadłościanu
 * 
 */
  double DlugoscBokuDluzszego[ILOSC_BOKOW];
  /*!
 * \brief Tablica DlugosciBokowKrotkich Prostopadłościanu
 * 
 * Pole klasy zawiera dane w tablicy statycznej na temat DługościBokowPoprzecznych Prostopadłościanu
 * 
 */
  double DlugoscBokuPoprzecznego[ILOSC_BOKOW];
public:
/*!
  * \brief Konstruktor Domyślny klasy Prostopadloscian 
  */
  Prostopadloscian(); 
  /*!
  * \brief Konstruktor Parametryczny klasy Prostopadloscian 
  */
  Prostopadloscian(const std::initializer_list<Wektor3D> &rListaWsp);
  /*!
  * \brief Obrot Prostopadloscianu o zadana Macierz (Metoda Jednoargumentowa)
  */
  int ObrotProstopadloscianu(const Macierz3x3 &MacRot);    
  /*!
  * \brief Obrot Prostopadloscianu o zadane dwie Macierze (Metroda Dwuargumentowa)
  */
  int ObrotProstopadloscianu(const Macierz3x3 &MacRot1,const Macierz3x3 &MacRot2);   
  /*!
  * \brief Oblicza długość boków Prostopadloscianu 
  */
  void ObliczDlugoscBokow();
  /*!
  * \brief Sprawdza długość przeciwległych(czy są równe) boków Prostopadloscianu 
  */
  void SprawdzDlugoscBokow();
  /*!
  * \brief Wyświetla Długość Bokow Prosopadloscianu
  */
  void WyswietlDlugosciBokow(const double *DlogoscBoku);
  /*!
  * \brief Przesuwa Prostopadloscian o zadany wektor
  */
  void PrzesunProstopadloscian(const Wektor3D &Wktr);
  /*!
  * \brief Pozwala na wyświetlenie Wierzchołków prostopadłościanu
  */
  friend std::ostream& operator <<(std::ostream & StrmWy,const Prostopadloscian & Pr);
  /*!
  * \brief Destruktor klasy Prostopadłościan
  */
  ~Prostopadloscian(); 
};



#endif
