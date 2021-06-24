#include <math.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include<algorithm>
#include "Prostopadloscian.hh"

/*Konstruktor Domyślny*/
Prostopadloscian::Prostopadloscian()
{
    for(Wektor3D& Wsp : Wierzcholek)
        Wsp = {0,0};
    for(double& Bok: DlugoscBokuDluzszego)
        Bok = 0;
    for(double&Bok : DlugoscBokuKrotkiego)
        Bok =0;
}   

/*konstruktor klasy Prostokat*/
Prostopadloscian::Prostopadloscian(const std::initializer_list<Wektor3D> &rListaWsp) : Prostopadloscian() 
{
    assert(rListaWsp.size() <= ILOSC_WIERZCHOLKOW);
    int Ind = -1;
    for(Wektor3D Wsp : rListaWsp)
        Wierzcholek[++Ind] = Wsp;
}

/*
  * Funkcja przeciążająca operator '<<' dla klasy Prostokąt. Wczytuje do strumienia
  * wyjściowego wierzchołki prostokąta  
  *
  *  StrmWy - Referncja na klase ostream 
  *  Pr - Referencja na obiekt klasy Prostopadloscian, który zawiera informacje o Wierzcholkach
  * Prostopadlosciana 
  *
  *  Warunki wstepne:
  *   Obiekt Pr musi mieć juz wcześniej zainicjowane wierzchołki prostokąta 
  * początkowego. To przeciążenie tylko je wczytuje, a nie inicjalizuje.
  *
  *  Warunki koncowe:
  * Prawidłowo wczytane wierzchołki prostokąta do strumienia wyjściowego
  *
  * Zwracane wartości:
  * Referncja na Obiekt (StrmWy) klasy ostream
  */

std::ostream& operator <<(std::ostream &StrmWy,const Prostopadloscian &Pr)
{
    for(int i=0;i<ILOSC_WIERZCHOLKOW;++i){
        StrmWy<<Pr.Wierzcholek[i];
        if(i%2)//jeśli i jest liczba nieparzysta 
            StrmWy<<std::endl;
    }
    for(int i=0;i<2;++i) //wyświetlamy jeszcze raz dwa ostatnie wierzcholki zeby "domknać" prostopadłościan
        StrmWy<<Pr.Wierzcholek[i];
    StrmWy<<std::endl;
    return StrmWy;
}


/*
  * 
  * Metoda klasy Prostopadloscian zajmuje się obrotem prostokąta o zadany kąt, użytkownik ma
  * również możliwość powielenia tej operacji x razy, wpisując odpowiednią ilośc 
  * powtórzeń. Metoda pyta użytkownika o kąt w stopniach a następnie operuje na
  * odpowiednich wzorach do obrotu każdego punktu prostokąta wokół środka 
  * układu współrzędnych.
  *
  *   MatRot  - Jest to referncja na obiekt klasy Macierz2x2, który zawiera 
  *  informacje na temat naszej macierzy rotacji, która zawiera odpowiednie 
  *  sinusy/cosinusy kąta obrotu prostokąta. Ta macierz jest niezbedna
  *  do wykorzystania zastosowaego wzoru na obrot jednego danego punktu 
  *  wokół środka układu współrzednych(Wierzcholek[i] = MacRot*Wierzcholek[i]),
  *  gdzie Wierzcholek to jest punky posiadający współrzedne x i y.
  *  
  *   Wierchołek[] - tablica zawierająca wierchołki prostokąta
  *
  *  Warunki wstepne:
  *  Obiekt klasy prostokąt musi zawierać wprowadzone wcześniej 
  *  współrzędne wierzchołków prostokąta początkowego, który będzie obracany.
  *
  *  Warunki koncowe:
  * Obrócony prostokąt o zadany kąt podany przez użytkownika i jeśli użytkownik 
  * zażyczył sobie wiekszej ilości wykonainia operacji obrotu to ten obrót musi 
  * być powtórzony tyle razy ile użytkownik sobie zażyczył
  *
  */

int Prostopadloscian::ObrotProstopadloscianu(Macierz3x3 &MacRot)
{    
    //int i, Operacja = 0;

    //while(Operacja<IloscPowtorzen){
        for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
            Wierzcholek[i] = MacRot*Wierzcholek[i];        
        }
        //++Operacja;
    //}

    //this->DlugoscBokow();

    //this->SprawdzDlugoscBokow();
    return 0;
}

int Prostopadloscian::ObrotProstopadloscianu(Macierz3x3 &MacRot1, Macierz3x3 &MacRot2)
{
    Macierz3x3 MacRotTym = MacRot1*MacRot2;
    for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
        Wierzcholek[i] = (MacRotTym)*Wierzcholek[i];        
    }
    return 0;
}
        
    /*Możliwość obliczenia kąta między bokami*/
   /* double kat;
    
    kat =((P0P3[X]*P0P1[X])+(P0P3[Y]*P0P1[Y]))/
    ((sqrt(pow(P0P3[X], 2)+pow(P0P3[Y], 2)))*
    (sqrt(pow(P0P1[X], 2)+pow(P0P1[Y], 2))));

    std::cout<<"Kat pomiedzy bokami: "<<double(kat)<<std::endl;*/

   /* return 0;
}*/

 /*
  * Funkcja która przesuwa prostokąt o zadany wektor
  *
  * Wktr- Referencja na obiekt klasy Wektor3D
  *
  *  Warunki wstepne:
  * Obiekt przekazywany do funkcji przez referncje powinine posiadać indormacje na
  * temat wspólrzencyh x i y wektora w tym przypadku punktu
  *
  *  Warunki koncowe:
  * Przsunięty prostokąt o zadany wektor. tz odpowiednio dodane dwa wektory i odpowie-
  * dnio dane na temat nowych punktów przypisane do przekazanego przez referencje obiektu
  *
  */

void Prostopadloscian::PrzesunProstopadloscian(const Wektor3D &Wktr)
{
    for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
        Wierzcholek[i] = Wierzcholek[i] + Wktr;        
    }
}


 /*
  * Funkcja Obliczająca dlugosc bokow Prostopadlosciana za pomocą odpowiedniego wzoru
  *
  *  Opis poszczegolnych parametrow wywolania funkcji, np.
  * Wktr - Referncja na obiekt klasy Wekttor2D
  * n1 - indeks współrzednej odpowiedniego wierzchołka
  * n2 - indeks współrzednej odpowiedniego wierzchołka
  *
  *  Warunki wstepne:
  * Przekazany przez refernncje obiekt klasy Wektor3D zawierający informacje na temat
  * współrzencyh wektora/punktu , wartośći n1 i n2 powinny mieć odpowiednie wartośći
  * indeksów wierzchołków/
  *
  *  Warunki koncowe:
  *  Odpowiednio obliczona za pomocą wzoru dlugość boku prostokąta i odpowiednio 
  * przypisana wartość długości boku prostokąta do składowych obiektu.
  *
  */

void Prostopadloscian::ObliczDlugoscBokow()
{
    Wektor3D WektoryMiedzyWierzcholkami[ILOSC_WIERZCHOLKOW+4];
    int IndWktr = 0;
    /*Obliczamy wektory między wszystkimi wierzcholkami, które bedą nam potrzebne do obliczenia długosci bokow*/
    for(int i = 0; i<ILOSC_WIERZCHOLKOW;i+=2){
        WektoryMiedzyWierzcholkami[IndWktr] = Wierzcholek[i] - Wierzcholek[i+1];
        ++IndWktr;
    }
    for(int i = 0; i<ILOSC_WIERZCHOLKOW-2;++i){
        WektoryMiedzyWierzcholkami[IndWktr] = Wierzcholek[i] - Wierzcholek[i+2];        
        ++IndWktr;
    }    
    for(int i = 0; i<ILOSC_WIERZCHOLKOW-6;++i){        
        WektoryMiedzyWierzcholkami[IndWktr] = Wierzcholek[i] - Wierzcholek[i+6];        
        ++IndWktr;
    }
    std::vector<double> WszystkieDlugosciBokow; //tworze kontener sekwencyjny który będe mógł łatwo uporządkować i znalezc najdluzsze i najkrotsze boki
    for(int i=0;i<ILOSC_WIERZCHOLKOW+4;++i)
        WszystkieDlugosciBokow.push_back(sqrt(pow(WektoryMiedzyWierzcholkami[i][X], 2)+pow(WektoryMiedzyWierzcholkami[i][Y], 2)+pow(WektoryMiedzyWierzcholkami[i][Z], 2))); //dodajemy na koniec vectora obliczona dlugosc boku

    /*Porzadkujemy Obiekt klasy vector, który zawiera długości boków prostokąta od najkrotszego do najdluzszego boku*/
    sort(WszystkieDlugosciBokow.begin(), WszystkieDlugosciBokow.end());

    /*Przyporozdkujemy wedlug kolejnosci odpowiednie booki i przypiszemy je do pol dlugosci bokow prostopadloscianu odpowiednio:
     DlugoscBokuKrotszego, DlugoscBokowPorzecznych, DlugoscBokuDluzszego ( zakładając oczywiście, że boki poprzeczne bedą wartością pomiędzy najkrotszym bokiem a najdluzszym)
     Funkcja for_each() powoduje wykonanie wskazanej funkcji dla kazdego elementu kontenera w podanym przedziale(tutaj cały zakres kontenera i funkcja ta to 
     PrzyporzodkowanieBokow)*/
   // for_each(WszystkieDlugosciBokow.begin(), WszystkieDlugosciBokow.end(), PrzyporzadkowanieBokow);

   std::vector<double>::iterator pr;
   int i;
    for(pr = WszystkieDlugosciBokow.begin(),i=0; pr != pr+ILOSC_BOKOW-1, i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuKrotkiego[i]= *pr;
    for(pr = WszystkieDlugosciBokow.begin()+ILOSC_BOKOW,i=0; pr != pr+ILOSC_BOKOW-1, i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuPoprzecznego[i]= *pr;                
    for(pr = WszystkieDlugosciBokow.begin()+(2*ILOSC_BOKOW),i=0; pr != WszystkieDlugosciBokow.end(), i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuDluzszego[i]= *pr;                
}

/*void Prostopadloscian::PrzyporzadkowanieBokow(double & WszystkieDlugosciBokow)
{   
    for(int i=0;i<ILOSC_BOKOW;++i)
        DlugoscBokuKrotkiego[i] = 
}*/
//Funkcja pomocnicza
bool BokiRowne(double a, double b){
    return fabs(a-b)<EPSILON;
}

/*Funkcja sprawdzająca poprawność długośći przeciwleglych boków prostopadloscianu*/
void Prostopadloscian::SprawdzDlugoscBokow()
{
    ObliczDlugoscBokow();
    if((BokiRowne(DlugoscBokuDluzszego[0], DlugoscBokuDluzszego[1]))&&(BokiRowne(DlugoscBokuDluzszego[2], DlugoscBokuDluzszego[3]))){
        std::cout<<":) Dluzsze przeciwlegle boki sa sobie rowne."<<std::endl;
    }
    else
        std::cout<<":O Dluzsze przeciwlegle boki nie sa rowne !!!"<<std::endl;

    WyswietlDlugosciBokow(DlugoscBokuDluzszego);
    
    if((BokiRowne(DlugoscBokuKrotkiego[0], DlugoscBokuKrotkiego[1]))&&(BokiRowne(DlugoscBokuKrotkiego[2], DlugoscBokuKrotkiego[3]))) {//jeśli boki równe 
        std::cout<<":) Krotsze przeciwlegle boki sa sobie rowne."<<std::endl;
    }
    else
        std::cout<<":O Krotsze przeciwlegle boki nie sa rowne !!!"<<std::endl;

    WyswietlDlugosciBokow(DlugoscBokuKrotkiego);
    
    if((BokiRowne(DlugoscBokuPoprzecznego[0], DlugoscBokuPoprzecznego[1]))&&(BokiRowne(DlugoscBokuPoprzecznego[2], DlugoscBokuPoprzecznego[3]))){
        std::cout<<":) Poprzeczne przeciwlegle boki sa sobie rowne."<<std::endl;
    }
    else
        std::cout<<":O Poprzeczne przeciwlegle boki nie sa rowne !!!"<<std::endl;

    WyswietlDlugosciBokow(DlugoscBokuPoprzecznego);        
}

void Prostopadloscian::WyswietlDlugosciBokow(const double *DlugoscBoku)
{
    std::cout<<"Dlugosc pierwszego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[0]<<std::endl;
    std::cout<<"  Dlugosc drugiego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[1]<<std::endl;
    std::cout<<"Dlugosc trzeciego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[2]<<std::endl;
    std::cout<<"Dlugosc czwartego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[3]<<std::endl<<std::endl;
}

/*Destruktor*/
Prostopadloscian::~Prostopadloscian(){}


