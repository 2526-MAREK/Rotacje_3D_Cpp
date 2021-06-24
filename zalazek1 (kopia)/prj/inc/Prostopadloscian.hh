#ifndef PROSTOKAT_HH
#define PROSTOKAT_HH

#include <iostream>
#include "Macierz.hh"
#include "Macierz3x3.hh"

#define ILOSC_WIERZCHOLKOW 8
#define ILOSC_BOKOW 4
#define EPSILON 0.000000000001

/*
 *  Klasa modeluje pojęcie prostokąta, zawiera informacje o współrzednych wierzchołków prostokąta i długości krótkiego i długiego boku prostokąta
 */
class Prostopadloscian {
private:
  Wektor3D Wierzcholek[ILOSC_WIERZCHOLKOW];
  double DlugoscBokuKrotkiego[ILOSC_BOKOW];
  double DlugoscBokuDluzszego[ILOSC_BOKOW];
  double DlugoscBokuPoprzecznego[ILOSC_BOKOW];
public:
  Prostopadloscian(); //Konstruktor domyślny
  Prostopadloscian(const std::initializer_list<Wektor3D> &rListaWsp);
  int ObrotProstopadloscianu(Macierz3x3 &MacRot);    
  int ObrotProstopadloscianu(Macierz3x3 &MacRot1, Macierz3x3 &MacRot2);    
  void PrzesunProstokat(Wektor3D &Wktr);
  void ObliczDlugoscBokow();
  void SprawdzDlugoscBokow();
  void WyswietlDlugosciBokow(const double *DlogoscBoku);
  /*!
  * \brief Przesuwa Prostopadloscian o zadany wektor
  */
  void PrzesunProstopadloscian(const Wektor3D &Wktr);
  friend std::ostream& operator <<(std::ostream & StrmWy,const Prostopadloscian & Pr);
  ~Prostopadloscian(); //destruktor
};



#endif
