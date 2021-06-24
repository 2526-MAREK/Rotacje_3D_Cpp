#include <iostream>
#include <iomanip>
#include <fstream>
#include "lacze_do_gnuplota.hh"
#include "Scena.hh"
#include "FunkcjeOgolne.hh"

using namespace std;

/*
 * Tu definiujemy pozostale funkcje.
 * Lepiej jednak stworzyc dodatkowy modul
 * i tam je umiescic. Ten przyklad pokazuje
 * jedynie absolutne minimum.
 */


#define DL_BOKU   50

/*!
 * Zapis wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] StrmWy - strumien wyjsciowy, do ktorego maja zostac zapisane
 *                     kolejne wspolrzedne.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 *                          mozliwosc zmiany wspolrzednych i prostokata
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void ZapisWspolrzednychDoStrumienia( std::ostream&  StrmWy, Prostopadloscian& Wierzcholki)
{
   StrmWy << Wierzcholki;
}

/*!
 *Zapis wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] sNazwaPliku - nazwa pliku, do którego zostana zapisane
 *                          wspolrzędne punktów.
 * \param[in] Przesuniecie - ten parameter jest tylko po to, aby pokazać
 a
 *                          i zmiane jego polorzenia na okienku graficznym
 *                         rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool ZapisWspolrzednychDoPliku( const char  *sNazwaPliku, Prostopadloscian &Pr)
{
std::ofstream  StrmPlikowy;

  StrmPlikowy.open(sNazwaPliku);
  if (!StrmPlikowy.is_open())  {
    std::cerr << ":(  Operacja otwarcia do zapisu \"" << sNazwaPliku << "\"" << std::endl
	 << ":(  nie powiodla sie." << std::endl;
    return false;
  }

  ZapisWspolrzednychDoStrumienia(StrmPlikowy,Pr);

  StrmPlikowy.close();
  return !StrmPlikowy.fail();
}


int ZapiszDoPlikuINarysujProstokat(Prostopadloscian &Pr, PzG::LaczeDoGNUPlota &Lacze)
{
  if (!ZapisWspolrzednychDoPliku("prostopadloscian.dat",Pr)) return 1;

  Lacze.Rysuj(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku

  return 0;
}

void WczytajDaneDoPrzesunieciaProstopadloscianu(Prostopadloscian &Pr, Wektor3D &Wktr)
{
    std::cout<<"Wprowadz wspolrzedne wektora translacji "
    "w postaci dwoch liczb tzn. wspolrzednej x, wspol"
    "rzednej y,oraz wspolrzednej z."<<std::endl;
    while(!(std::cin>>Wktr))
    {
        KomunikatOBledzie();
        CzyszczenieStrumieniaWejsciowego(std::cin);
    }
    Pr.PrzesunProstopadloscian(Wktr);
}

int main()
{
  Wektor3D Wktr;              
  Prostopadloscian  Pr= {Wktr={0, 0 ,0}, Wktr={60, 0, 0}, Wktr={0, 50, 0},Wktr={60, 50,0}, 
  Wktr={0, 50, 40}, Wktr={60,50,40},Wktr={0,0,40},Wktr={60,0,40}}; 
  Macierz3x3 MacRot;
  int IloscStruktur = POCZATKOWA_ILOSC_STRUKTUR;
  int *wskIloscStruktur = &IloscStruktur;
  Scena Sc[ILOSC_STRUKTUR];
 // Scena * wsk_Scena = NULL;//new Scena[*wskIloscStruktur];
  PzG::LaczeDoGNUPlota  Lacze;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  Lacze.DodajNazwePliku("prostopadloscian.dat",PzG::RR_Ciagly,2);
   //
   //  Ustawienie trybu rysowania 3D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy x,y,z.
   //
  Lacze.ZmienTrybRys(PzG::TR_3D);

   // Ustawienie zakresow poszczegolnych osi
  Lacze.UstawZakresY(-155,155);
  Lacze.UstawZakresX(-155,155);
  Lacze.UstawZakresZ(-155,155);

  Pr.SprawdzDlugoscBokow();

  ZapiszDoPlikuINarysujProstokat(Pr, Lacze);

  Menu(Pr,Wktr,MacRot,Lacze,Sc, wskIloscStruktur);

}

/*Funkcja "czyści" strumień wejściowy*/
void CzyszczenieStrumieniaWejsciowego(std::istream &StrmWe)
{
    char ch;

    StrmWe.clear(); //czyścimy stan strumienia z błędnych bitów aby obiekt StrmWe klasy istream mógł prawidłowo "wyczyśćic" strumien wejściowy
    while( (ch = StrmWe.get()) != '\n'){
        continue; //mogłoby się obyć bez continue 
  }
}

int Menu(Prostopadloscian &Pr, Wektor3D &Wktr, Macierz3x3 &MacRot, PzG::LaczeDoGNUPlota &Lacze,Scena *Sc, int *wskIloscStruktur)
{
  char wybor;
  int koniec;

  WyswietlMenu();

  while(std::cin>>wybor){
    std::cout<<std::endl;
    switch(wybor)
    {
      case 'o':
      {
        koniec = WczytajDaneDoObrotuProstopadloscianu(MacRot, Pr, Sc, wskIloscStruktur);
        if(koniec!=-1)
        Pr.SprawdzDlugoscBokow();
        ZapiszDoPlikuINarysujProstokat(Pr, Lacze);
        break;
      }
      case 't':
      {
        for(int IlPow =0;IlPow<Sc[0].PowtorzeniaOperacjiObrotu;++IlPow){
          for(int i=0;i<*wskIloscStruktur-1;++i){
            (Sc[0].Bryla).ObrotProstopadloscianu((Sc[i].MacierzRotacji));
          }
        }
        Pr = Sc[0].Bryla;  
        ZapiszDoPlikuINarysujProstokat(Pr, Lacze);
        Pr.SprawdzDlugoscBokow();
        break;
      }
      case 'r':
      {
        std::cout<<MacRot;
        break;
      }
      case 'p':
      {
        WczytajDaneDoPrzesunieciaProstopadloscianu(Pr, Wktr);
	      ZapiszDoPlikuINarysujProstokat(Pr, Lacze);
        break;
      }
      case 'w':
      {
        std::cout << Pr<<std::endl;
        break;     
      }
      case 's':
      {
        Pr.SprawdzDlugoscBokow();
      }
      case 'm':
      {
        koniec = Menu(Pr, Wktr, MacRot, Lacze, Sc,wskIloscStruktur);
        break;  
      } 
      case 'k':
      {
        exit(0);
        break;  
      }
      default:
      {
        std::cout<<"Proszę wybrać odpowiednia litere: "<<std::endl<<std::endl;
      koniec = Menu(Pr, Wktr, MacRot, Lacze, Sc, wskIloscStruktur);
      }
    }
    WyswietlMenu();
  }
  CzyszczenieStrumieniaWejsciowego(cin);
  koniec = Menu(Pr, Wktr, MacRot, Lacze, Sc, wskIloscStruktur);
  return 0;
}

void WyswietlMenu()
{
  std::cout<<"o - obrot bryly o zadana sekwencje katow"<<std::endl;
  std::cout<<"t - powtorzenie poprzedniego obrotu"<<std::endl;
  std::cout<<"r - wyswietlenie macierzy rotacji"<<std::endl;
  std::cout<<"p - przesuniecie prostokata o zadany wektor"<<std::endl;
  std::cout<<"w - wyswietlenie wspolrzednych wierzcholkow"<<std::endl;
  std::cout<<"s - sprawdzenie dlugosci przeciwleglych bokow"<<std::endl;
  std::cout<<"m - wyswietl menu"<<std::endl;
  std::cout<<"k - koniec dzialania programu"<<std::endl<<std::endl;

  std::cout<<"Twoj wybor? (m-menu) > ";
}

void WczytajKatWStopniachIZamienNaRadiany(double* KatObrotu, int IndeksDanej)
{
    double KatWStopniach;
    while(!(std::cin>>KatWStopniach)){//Nie udało się wczytać 
        CzyszczenieStrumieniaWejsciowego(std::cin);
        KomunikatOBledzie();
    }
    KatObrotu[IndeksDanej] = ZamianaStopniNaRadiany(KatWStopniach);
}

void WczytanieKataObrotuIOznaczeniaOsi(std::string &OznaczeniaOsiObrotu, double* KatObrotu,int* wsk_IndeksDanej, char OznaczenieOsiObrotu)
{
  ++(*wsk_IndeksDanej);
  WczytajKatWStopniachIZamienNaRadiany(KatObrotu, *wsk_IndeksDanej);
  OznaczeniaOsiObrotu[*wsk_IndeksDanej] = OznaczenieOsiObrotu;
}

int WczytajIloscPowtorzenOperacjiObrotu()
{
    int IloscPowtorzen;
    std::cout<<"Ile razy operacja obrotu ma byc powtorzona?"<<std::endl;
    while(!(std::cin>>IloscPowtorzen)) //Nie udało się wczytać 
    {
        CzyszczenieStrumieniaWejsciowego(std::cin);
        KomunikatOBledzie();
    }
    std::cout<<std::endl;

    if(IloscPowtorzen<=0){ //Ilość powtórzeń <=0
        std::cerr<<"Niestety, aby wykonac ta operacje ilosc powtorzen musi byc wieksza od zera"<<std::endl;
        return -1;
    }
    return IloscPowtorzen;
}

void UruchomObrotProstopadloscianuIZapamietajMacRot(Macierz3x3 &MacRot, Macierz3x3 &MacRotTym, Prostopadloscian &Pr, Scena *Sc, int i, int * wskIloscStruktur, int i2)
{
  Pr.ObrotProstopadloscianu(MacRot, MacRotTym);
  if(i2==0) ++(*wskIloscStruktur);
  if(i2==0) Sc[i].MacierzRotacji = MacRot; //Zapisuje tylko raz( gdy jest pierwsza ilosc powotrzen, aby zaoszczedzic pamiec)  
}

void WybierzNastOznaczenie(std::string& OznaczeniaOsiObrotu,double* KatObrotu,Macierz3x3& MacRot,Prostopadloscian& Pr,Scena* Sc,int* wskIloscStruktur,int *wsk_i, int i2 )
{
  Macierz3x3 MacRotTym; // Tworzę Macierz tymczasowa, gdy potrzebna
  if((OznaczeniaOsiObrotu[++(*wsk_i)])=='x'){
    MacRotTym = {1, 0, 0, 0, cos(ALFA), -sin(ALFA),0, sin(ALFA), cos(ALFA)};
    UruchomObrotProstopadloscianuIZapamietajMacRot(MacRot,MacRotTym,Pr,Sc, *wsk_i, wskIloscStruktur, i2);
  }
  else //jeśli następna zapisana dana nie jest x to zmniejsz licznik
    --(*wsk_i);
  if((OznaczeniaOsiObrotu[++(*wsk_i)])=='y'){
    MacRotTym = {cos(ALFA), 0, sin(ALFA), 0, 1, 0, -sin(ALFA), 0, cos(ALFA)};
    UruchomObrotProstopadloscianuIZapamietajMacRot(MacRot,MacRotTym,Pr,Sc, *wsk_i, wskIloscStruktur, i2);    
  }
    else //jeśli następna zapisana dana nie jest y to zmniejsz licznik
    --(*wsk_i);
  if((OznaczeniaOsiObrotu[++(*wsk_i)])=='z'){
    MacRotTym = {cos(ALFA), -sin(ALFA),0, sin(ALFA), cos(ALFA), 0, 0, 0,1};
    UruchomObrotProstopadloscianuIZapamietajMacRot(MacRot,MacRotTym,Pr,Sc, *wsk_i, wskIloscStruktur, i2);
  }
}

void WywolanieObrotuWedlugOdpowiednichOznaczen(Macierz3x3 &MacRot, Prostopadloscian &Pr, Scena *Sc,int *wskIloscStruktur,std::string &OznaczeniaOsiObrotu,double* KatObrotu, int IndeksDanej, int IloscPowtorzen)
{
  for(int i2 = 0;i2<IloscPowtorzen;++i2){
  int i=-1;
    while(i<=IndeksDanej)
    {
      ++i;
      int *wsk_i =&i;
      switch(OznaczeniaOsiObrotu[i])
      {
        case 'x':
        {
          MacRot={1, 0, 0, 0, cos(ALFA), -sin(ALFA),0, sin(ALFA), cos(ALFA)};
          if(i2==0)
           ++(*wskIloscStruktur); 
          if(i2==0) 
            Sc[i].MacierzRotacji = MacRot; //Zapisuje tylko raz( gdy jest pierwsza ilosc powotrzen, aby zaoszczedzic pamiec)
          if((IndeksDanej>0)&&!(i==IndeksDanej)) //jeśli jest wiecej niz jedno oznaczenie osi i aktualne oznaczenie nie jest ostatnie 
          {
            WybierzNastOznaczenie(OznaczeniaOsiObrotu, KatObrotu,MacRot, Pr, Sc, wskIloscStruktur,wsk_i,i2 );
            break;
          }
         else{
          Pr.ObrotProstopadloscianu(MacRot);
          std::cout<<"Uruchomiono jednoargumentowy obrotProstopadloscianuX"<<std::endl;
          break;
         }
        }
        case 'y':
        {
          MacRot=  {cos(ALFA), 0, sin(ALFA), 0, 1, 0, -sin(ALFA), 0, cos(ALFA)};
          if(i2==0) 
            ++(*wskIloscStruktur); 
          if(i2==0) 
            Sc[i].MacierzRotacji = MacRot; //Zapisuje tylko raz( gdy jest pierwsza ilosc powotrzen, aby zaoszczedzic pamiec)
          if((IndeksDanej>0)&&!(i==IndeksDanej))
          {
            WybierzNastOznaczenie(OznaczeniaOsiObrotu, KatObrotu,MacRot, Pr, Sc, wskIloscStruktur,wsk_i,i2 );
            break;
          }
         else{
          Pr.ObrotProstopadloscianu(MacRot);
          std::cout<<"Uruchomiono jednoargumentowy obrotProstopadloscianuY"<<std::endl;
          break;
         }
        }
        case 'z':
        {
          MacRot= {cos(ALFA), -sin(ALFA),0, sin(ALFA), cos(ALFA), 0, 0, 0,1};
          if(i2==0) 
            ++(*wskIloscStruktur); 
          if(i2==0) 
            Sc[i].MacierzRotacji = MacRot; //Zapisuje tylko raz( gdy jest pierwsza ilosc powotrzen, aby zaoszczedzic pamiec)
          if((IndeksDanej>0)&&!(i==IndeksDanej))
          {
            WybierzNastOznaczenie(OznaczeniaOsiObrotu, KatObrotu,MacRot, Pr, Sc, wskIloscStruktur,wsk_i,i2 );
            break; 
          }
         else{
          Pr.ObrotProstopadloscianu(MacRot);
          break;
         }
        }
      }
     }
  }
}

int WczytajDaneDoObrotuProstopadloscianu(Macierz3x3 &MacRot, Prostopadloscian &Pr, Scena *Sc, int *wskIloscStruktur)
{
    std::string OznaczeniaOsiObrotu;
    double KatObrotu[ILOSC_KATOW_OBROTOW];
    int IndeksDanej = -1;
    int *wsk_IndeksDanej = &IndeksDanej;
    char OznaczenieOsiObrotu;

    std::cout<<"Podaj sekwencje oznaczen osi oraz katy obrotu w stopniach"<<std::endl;
    while((std::cin>>OznaczenieOsiObrotu)&&(OznaczenieOsiObrotu != '.')){
        switch(OznaczenieOsiObrotu)
        { case 'x':{ WczytanieKataObrotuIOznaczeniaOsi(OznaczeniaOsiObrotu,KatObrotu, wsk_IndeksDanej, 'x');  break; }
            case 'y':{ WczytanieKataObrotuIOznaczeniaOsi(OznaczeniaOsiObrotu,KatObrotu, wsk_IndeksDanej, 'y'); break; }
            case 'z':{ WczytanieKataObrotuIOznaczeniaOsi(OznaczeniaOsiObrotu,KatObrotu, wsk_IndeksDanej, 'z'); break; }
            default:{
              std::cout<<":( Bledne oznaczenie osi. Dopuszczalne znaki to: x y z ."<<std::endl;
              std::cout<<":( Sproboj jeszcze raz. "<<std::endl;
              CzyszczenieStrumieniaWejsciowego(cin);
              break;
            }    
        }
    }
    int IloscPowtorzen = WczytajIloscPowtorzenOperacjiObrotu();
    
    *wskIloscStruktur = POCZATKOWA_ILOSC_STRUKTUR;
    ++(*wskIloscStruktur);
    Sc[0].PowtorzeniaOperacjiObrotu = IloscPowtorzen;
  
    WywolanieObrotuWedlugOdpowiednichOznaczen(MacRot, Pr, Sc,wskIloscStruktur,OznaczeniaOsiObrotu,KatObrotu, IndeksDanej, IloscPowtorzen);
    
    Sc[0].Bryla = Pr; // Inicjalizuje tylko pierwsza bryłę ponieważ na niej póżniej będą znowu powtarzane operacje obrotu 
    return 0;
}



