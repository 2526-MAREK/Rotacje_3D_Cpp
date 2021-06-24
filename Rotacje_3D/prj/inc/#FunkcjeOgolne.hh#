#ifndef FUNKCJEOGOLNE_HH
#define FUNKCJEOGOLNE_HH

#include <iostream>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include"Scena.hh"

#define ALFA KatObrotu[(*wsk_i)]
#define ILOSC_KATOW_OBROTOW 100

class Prostopadloscian;
struct Scena;

inline void KomunikatOBledzie() {  std::cerr<<"Blad formatu wprowadzanej liczby, program tutaj"
" oczekuje tylko liczb calkowitych, mozesz powtorzyc wprowadzanie:"<<std::endl;}
void CzyszczenieStrumieniaWejsciowego(std::istream &StrmWe);
int Menu(Prostopadloscian &Pr, Wektor3D &Wktr, Macierz3x3 &MacRot, PzG::LaczeDoGNUPlota &Lacze,Scena *Sc, int *wskIloscStruktur);
int ZapiszDoPlikuINarysujProstokat(Prostopadloscian &Pr, PzG::LaczeDoGNUPlota &Lacze);
void WyswietlMenu();
bool ZapisWspolrzednychDoPliku( const char  *sNazwaPliku, Prostopadloscian &Pr);
void ZapisWspolrzednychDoStrumienia( std::ostream&     StrmWy, Prostopadloscian& Wierzcholki);
void WczytajKatWStopniachIZamienNaRadiany(double* KatObrotu, int IndeksDanej);
void UruchomObrotProstopadloscianuIZapamietajMacRot(Macierz3x3 &MacRot, Macierz3x3 &MacRotTym, Prostopadloscian &Pr, Scena *Sc, int i, int *wskIloscStruktur, int i2);
void WczytajDaneDoPrzesunieciaProstopadloscianu(Prostopadloscian &Pr, Wektor3D &Wktr, int *wskIloscStruktur);
inline double ZamianaStopniNaRadiany(double KatWStopniach){double KatWRadianach = (2*M_PI*KatWStopniach)/360; return KatWRadianach;}
int WczytajDaneDoObrotuProstopadloscianu(Macierz3x3 &MacRot, Prostopadloscian &Pr, Scena *Sc, int *wskIloscStruktur);
void WywolanieObrotuWedlugOdpowiednichOznaczen(Macierz3x3 &MacRot, Prostopadloscian &Pr, Scena *Sc,int *wskIloscStruktur,std::string &OznaczeniaOsiObrotu,double* KatObrotu, int IndeksDanej, int IloscPowtorzen);
int WczytajIloscPowtorzenOperacjiObrotu();
void WczytanieKataObrotuIOznaczeniaOsi(std::string &OznaczeniaOsiObrotu, double* KatObrotu,int* wsk_IndeksDanej, char OznaczenieOsi);
void WybierzNastOznaczenie(std::string& OznaczeniaOsiObrotu,double* KatObrotu,Macierz3x3& MacRot,Prostopadloscian& Pr,Scena* Sc,int* wskIloscStruktur,int *wsk_i, int i2 );

std::ostream& operator <<(std::ostream & StrmWy,const Prostopadloscian & Pr);
#endif