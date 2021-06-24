#ifndef WEKTOR_HH
#define WEKTOR_HH

#include <iostream>
#include<iomanip>
#include <fstream>
#include <cassert>
#define MANIPULATORY_WYSWIETLAJACE std::setw(16) << std::fixed << std::setprecision(10) 

/*!
 * \file
 * \brief Definicja szablonu klasy Wektor 
 *  
 *  Zawiera definicje szablonu klasy Wektor
 *
 */

/*!
* \brief Klasa modeluje pojęcie wektora.
 * Posiada informacje o wspólrzędnych wektora i metody przeciążające operator ineksujący '[]'
* i umożliwijąc dostęp do współrzednych wektora
*/
enum wspolrzedne {X, Y, Z}; //Typ wyliczeniowy dla współrzedych wektora x, y , Z 

template<unsigned int Templ_Size>
class Wektor {
private:
  double Wsp[Templ_Size]; //Wspólrzędne wektora x i y
public:
  Wektor(); //konstruktor domyślny
  Wektor(const std::initializer_list<double> &rListaWsp);
  double operator [] (unsigned int lnd) const { assert(lnd < Templ_Size); return Wsp[lnd]; }
  double &operator [] (unsigned int lnd)  { assert(lnd < Templ_Size); return Wsp[lnd]; } 
  /*!
  * \brief Metoda pozwala dodawać Wektory 
  */
  Wektor operator+(const Wektor & Wierz) const;
  /*! 
  * \brief Metoda pozwala odejmować Wektory
  */
  Wektor operator-(const Wektor & Wierz) const;
  ~Wektor(); //destruktor
};

/*Konstruktor domyślny*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor()
{
  for(double& Wspolrzedne: Wsp)
    Wspolrzedne = 0;  //Inicjalizacja całej tablicy zerami 
}


/*konstruktor klasy Wektor2D*/
/*template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor(double x,double y) 
{
  Wsp[X] = x;
  Wsp[Y] = y;
}*/

/*konstruktor klasy Wektor2D*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::Wektor(const std::initializer_list<double> &rListaWsp) : Wektor() 
{
  assert(rListaWsp.size() <= Templ_Size);
  int Ind = -1;
  for(double Wsp_i : rListaWsp)
    Wsp[++Ind] = Wsp_i;
}

/*!
  * \brief Przeciąża operator '<<' dla szablonu klasy Wektor i pozwala wyświetlić jego składowe 
  * 
  * Funkcja przeciążająca operator '<<' dla klasy Wektor2D. Wczytuje do strumienia
  * wyjściowego odpowiednie współrzedne wierzchołków i ustawia odpowiednie
  *  flagi( manipulatory: setw, fixed, setprecision) na strumień wyjściowy dla 
  * prawidłowości wczytywania do strumienia wyjściowego.
  *
  *  \param[in] StrmWy - Referncja na klase ostream 
  *  \param [in] Wktr - Referencja na obiekt klasy Wektor2D, który zawiera informacje o
  *  Współrzednych Punktów wierzchołków prostokąta
  *
  * \pre Obiekt Wktr musi mieć juz wcześniej zainicjowane współrzedne wierzchołków
  * prostokąta początkowego To przeciążenie tylko je wczytuje, a nie inicjalizuje.
  *
  * \post Prawidłowo wczytane Współrzędne wierzchołków prostokąta do strumienia wyjściowego
  *
  * \return Referncja na Obiekt (StrmWy) klasy ostream
  */
template <unsigned int Templ_Size>
std::ostream &operator<<(std::ostream &StrmWy, const Wektor<Templ_Size> &Wktr)
{
  for(unsigned int i=0;i<Templ_Size;++i)
    StrmWy << MANIPULATORY_WYSWIETLAJACE << Wktr[i];
  StrmWy<< std::endl;        
  return StrmWy;
}

 /*!
  *  Funkcje przeciążają operatory '+' i '-' dla klasy Wektor2D,
  * wywołując konstruktor klasy Wektor2D który przypisuje do 
  * obiektu odpowiednio składowe odjęte/dodane
  * (opisałem dwa przeciązenia w jednym opisie ponieważ 
  * nie różniłyby się one niczym).
  *
  * \param[in] Wierz - Stała Referencja na obiekt klasy Wektor2D zawierający
  * dane na temat wektora(współrzedne wektora)
  * 
  * \pre Obiekt wywołujący przeciążenie i obiekt przekazany przez
  *  referncje (Wierz) musi mieć dane na temat dodawanych/odejmowanych
  *  wektrów, a mianowicie wspólrzedne wektora.
  *  
  * \post Wypełniony obiekt odpowiednimi wartościami po wykonaniu
  * operacji dodawania/odejmowania.
  *
  * \return Funkcja przeciązająca zwraca obiekt, do którego zostały
  * przypisane wykonane operacje dodawania/odejmowania
  * na współrzednych wektora.
  */
template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator-(const Wektor<Templ_Size> & Wierz) const
{
  Wektor<Templ_Size> Wktr;
  for(int unsigned i=0;i<Templ_Size;++i)
    Wktr.Wsp[i] = Wsp[i]-Wierz[i];
  return Wktr;
}

/*!
* Opis przeciążenia operatora '+' jest nad funkcją przeciążaj
*jącą operator '-'
*/
template <unsigned int Templ_Size>
Wektor<Templ_Size> Wektor<Templ_Size>::operator+(const Wektor<Templ_Size> & Wierz) const
{
  Wektor<Templ_Size> Wktr;
  for(int unsigned i=0;i<Templ_Size;++i)
    Wktr.Wsp[i] = Wsp[i]+Wierz[i];
  return Wktr;
}

//Wektor<Templ_Size> WektorMiedzyDwomaPunktami()

/*!
  * \brief Przeciążenie operatora '>>' dla szablony klasy Wektor pozwalające zapisywać dane do składowych szablonu klasy
  *  Przeciązenie operatora '>>' pozwalające zapisać współrzedne
  * wektora z strumienia wejściowego do obiektu przekazanego 
  * przez referencje.
  * 
  * \param[in] StrmWe - Referncja na obiekt klasy istream
  * \param[in] Wktr - Referncja na obiekt klasy Wektor2D
  *
  * \pre Wcześniej zainicjalizowany przez konstruktor domyślny 
  * obiekt klasy Wketro2D
  *
  * \post Prawidłowo zapisane dane o współrzednych wektora
  *  do obiektu klasy Wektor2D
  *
  * \return Funkcja zwraca obiekt klasy istream.
  */
template <unsigned int Templ_Size>
std::istream& operator>>(std::istream &StrmWe, Wektor<Templ_Size> &Wktr)
{
  for(int unsigned i=0;i<Templ_Size;++i)
    StrmWe>>Wktr[i];
  return StrmWe;
}


/*Destruktor*/
template <unsigned int Templ_Size>
Wektor<Templ_Size>::~Wektor(){}

#endif
