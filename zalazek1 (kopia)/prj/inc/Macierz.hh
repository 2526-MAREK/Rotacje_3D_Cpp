#ifndef MACIERZ_HH
#define MACIERZ_HH


#include <iostream>
#include <math.h>
#include "Wektor.hh"
#include "Wektor3D.hh"

/*!
 * \file
 * \brief Definicja szablonu klasy Macierz
 *
 * Zawiera definicję szablonu klasy Macierz. 
 * 
 */

/*!
 * \brief Klasa modeluje pojęcie macierzy 2x2, posiada informacje o zawartośći macierzy
 */
template<unsigned int Templ_Size>
class Macierz {
private:  
  double Tab[Templ_Size][Templ_Size]; //Macierz będzie zawierać sinusy i cosinusy danych kątów
public:
  Macierz(); //konstruktor domyślny
  Macierz(const std::initializer_list<double> &rListaWsp);
  double operator () (unsigned int Wie,unsigned int Kol) const { assert((Wie < Templ_Size)||(Kol < Templ_Size)); return Tab[Wie][Kol]; }
  double& operator () (unsigned int Wie,unsigned int Kol) { assert((Wie < Templ_Size)||(Kol < Templ_Size)); return Tab[Wie][Kol]; }
  //inline char OznaczenieOsi() { return OznaczenieOsi;}
  /*!
  * \brief Mnoży macierz przez wektor
  */
  Wektor<Templ_Size> operator *(const Wektor<Templ_Size> &Wktr) const;
  Macierz<Templ_Size>& operator *(const Macierz<Templ_Size> &MacRot); 
  //Macierz operator *(const Macierz &MacRot1) const;
  ~Macierz(); //destruktor
};

/*Konstruktor Domyślny*/
template <unsigned int Templ_Size>
Macierz<Templ_Size>::Macierz()
{
    /*Inicjalizuje tablice i dane zerami*/
    for(double* ElemTab: Tab)
      *ElemTab = 0;
}

/*konstruktor klasy Macierz*/
template <unsigned int Templ_Size>
Macierz<Templ_Size>::Macierz(const std::initializer_list<double> &rListaWsp) : Macierz() 
{
  assert(rListaWsp.size() <= Templ_Size*Templ_Size);

  double Tab_tymczas[Templ_Size*Templ_Size];
  int Ind = -1;
  for(double Wsp_i : rListaWsp)
    Tab_tymczas[++Ind] = Wsp_i;

  Ind = -1;    
  for(int unsigned Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(int unsigned Ind2=0;Ind2<Templ_Size;++Ind2)
      Tab[Ind1][Ind2] = Tab_tymczas[++Ind];
  }
}


/*!
  *  Funkcja przeciązająca operator '*'(mnozenia), która 
  * korzysta z macierzy rotacji i obiektu Wektor. 
  *  Obiekty te służą do wykorzystania wzoru na obrót 
  * danego punktu o zadany kąt wokół środka układu 
  * wspólrzednych. 
  * 
  * \param[in] Wektor - Referncja na obiekt klasy Wektor2D zawierący
  * informacje o współrzędnych wierzchołka prostokąta
  *
  * Tab[][] - Tablica dwuwymiarowa , która jest 
  * Macierzą rotacji zawierająca odpowiednie 
  * sinsuy i cosinsu kąta obrotu prostokąta, niezbędna
  * do wykorzystania wzoru na obrót danego punktu wokół
  * środka ukłądu współrzednych.
  * 
  * \pre Obiekt Wektor musi mieć wcześniej zainicjalizowane dane 
  * o współrzednych punktu wierzchołka prostokąta.
  * 
  * \pre Tablica Tab[][] musi mieć dane o sinusach i cosinsuach 
  * odpowiedniego kąta obrotu.
  *
  * \post Prawidłowo obliczone i zwrócone przez wartość Współrzedne
  *  obróconego już punktu wierzchołka prostokąta. 
  *
  *  \return Funkcja zwraca przez wartość zainicjowany obiekt przez
  *  konstruktor klasy Wektor2D.
  */
template <unsigned int Templ_Size>
Wektor<Templ_Size> Macierz<Templ_Size>::operator *(const Wektor<Templ_Size> &Wktr) const
{
  Wektor<Templ_Size> Wek;
  for(unsigned int Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(unsigned int Ind2 = 0;Ind2<Templ_Size;++Ind2){
      Wek[Ind1] = Wek[Ind1] + Wktr[Ind2]*Tab[Ind1][Ind2];
    }
  }
  return Wek;
}

template <unsigned int Templ_Size>
Macierz<Templ_Size>& Macierz<Templ_Size>::operator *(const Macierz<Templ_Size> &MacRot) 
{
  Macierz<Templ_Size> MacRotTym;
  for(unsigned int Ind1 = 0;Ind1<Templ_Size;++Ind1){
    for(unsigned int Ind2 = 0;Ind2<Templ_Size;++Ind2){
      for(unsigned int Ind3 =0; Ind3<Templ_Size;++Ind3)
        MacRotTym.Tab[Ind1][Ind2] += MacRot.Tab[Ind1][Ind3]*Tab[Ind3][Ind2];
    }
  }
  *this = MacRotTym;
  return *this;
}

template <unsigned int Templ_Size>
std::ostream &operator<<(std::ostream &StrmWy, const Macierz<Templ_Size> &MacRot)
{
  StrmWy<<"Macierz Rotacji prezentuje się następująco: "<<std::endl;
  for(unsigned int Ind1= 0; Ind1<Templ_Size;++Ind1)
  {
    StrmWy<<std::endl; 
    for(unsigned int Ind2= 0; Ind2<Templ_Size;++Ind2)
    {
      StrmWy.width(10);
      StrmWy<< MacRot(Ind1, Ind2)<<" ";
    }
  }
  StrmWy<<std::endl<<std::endl;
  return StrmWy;
}

/*Destruktor*/
template <unsigned int Templ_Size>
Macierz<Templ_Size>::~Macierz(){}

#endif
