#include <math.h>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include<algorithm>
#include "Prostopadloscian.hh"

/*!
 * \file 
 * \brief Definicja metód klasy Prostopadloscian
 *
 *  Plik zawiera definicję metód klasy Prostopadloscian.
 */

/*! 
*  Konstruktor Domyślny, który iniciajlizuje nowo tworzony obiekt klasy 
* Prostopadloscian. Wypełania każde pole klasy zerami.
*/
Prostopadloscian::Prostopadloscian()
{
    for(Wektor3D& Wsp : Wierzcholek)
        Wsp = {0,0, 0};
    for(double& Bok: DlugoscBokuDluzszego)
        Bok = 0;
    for(double&Bok : DlugoscBokuKrotkiego)
        Bok =0;
    for(double&Bok : DlugoscBokuPoprzecznego)
        Bok =0;        
}   

/*! 
*  Konstruktor parametryczny klasy Prostokat, który Inicjalizuje obiekt klasy Prosokąt odpowiednimi argumentami podanymi przez użytkownika
* za pomocą listy inicjalizacyjnej, dzięki szablonowi initializer_list z biblioteki standardowej
* 
* \param[in] rListaWsp - Referencja do obietku szablonu klasy z biblioteki standardowej initilizer_list pozwala ona na inicjalizacje obiektu 
* klasy Prostopadloscian za pomocą listy inicjalizacyjnej 
* 
* \pre Ilośc inicjalizowanych wierzchołków prostopadłsocianu nie może być wieksza od Ilosci wierzchokkow prostoapdlosciaunu czyli nie 
* może być wieksza od 8.
* \post Zainicializowany obiekt klasy Prosopadloscian danymi przez użytkownika wierzchołkami, jeśli użytkownik podał mniej niż 
* 8 wierzchołków reszta jest inicializowana jako wierchołek o współrzednej 0, umożliwa to wywołanie Kontruktora domyślnego klasy Prostopadloscian
 [ : Prostopadloscian() ] za pomocą listy inicjalizacyjnej przed wywołaniem naszego konstruktora parametrycznego.
* 
*/
Prostopadloscian::Prostopadloscian(const std::initializer_list<Wektor3D> &rListaWsp) : Prostopadloscian() 
{
    assert(rListaWsp.size() <= ILOSC_WIERZCHOLKOW);
    int Ind = -1;
    for(Wektor3D Wsp : rListaWsp)
        Wierzcholek[++Ind] = Wsp;
}

/*!
  * Funkcja przeciążająca operator '<<' dla klasy Prostopadloscian. Wczytuje do strumienia
  * wyjściowego wierzchołki prostokąta  
  *
  *  \param[in] StrmWy - Referncja na klase ostream 
  *  \param[in] Pr - Referencja na obiekt klasy Prostopadloscian, który zawiera informacje o Wierzcholkach
  * Prostopadlosciana 
  *
  *  \pre Obiekt Pr musi mieć juz wcześniej zainicjowane wierzchołki prostopadłośćianu
  * początkowego. To przeciążenie tylko je wczytuje, a nie inicjalizuje.
  *
  * \post Prawidłowo wczytane wierzchołki prostokąta do strumienia wyjściowego
  *
  * \return Referncja na Obiekt (StrmWy) klasy ostream
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


/*!
  * 
  * Metoda ([jednoarguemntowa], instnieje również metoda dwuargumentowa do obrotu Prostopadloscianu)
  * klasy Prostopadloscian zajmuje się obrotem Prostopadloscianu o zadany kąt, 
  *
  *  \param[in] MatRot  - Jest to referncja na obiekt klasy Macierz3x3, który zawiera 
  *  informacje na temat naszej macierzy rotacji, która zawiera odpowiednie 
  *  sinusy/cosinusy kąta obrotu prostokąta. Ta macierz jest niezbedna
  *  do wykorzystania zastosowaego wzoru na obrot jednego danego punktu 
  *  wokół środka układu współrzednych(Wierzcholek[i] = MacRot*Wierzcholek[i]),
  *  gdzie Wierzcholek to jest punky posiadający współrzedne x, y i z.
  *  
  *  \pre
  *  Obiekt klasy prostopadloscian musi zawierać wprowadzone wcześniej 
  *  współrzędne wierzchołków prostopadloscianu początkowego, który będzie obracany.
  *
  *  \post
  * Obrócony prostopadloscian o zadany kąt podany przez użytkownika 
  *
  */

int Prostopadloscian::ObrotProstopadloscianu(const Macierz3x3 &MacRot)
{    
        for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
            Wierzcholek[i] = MacRot*Wierzcholek[i];        
        }
    return 0;
}

/*!
  * 
  * Metoda ([dwuoarguemntowa] ) klasy Prostopadloscian zajmuje się obrotem Prostopadloscianu o zadany kąt, 
  * MEtoda dwuarguemnotwa od jednoargumentowej różni się tym że może ona przyjąc dwie macierze Rotacji.
  * Jest to wykorzystywane podczas np gdy użytkownik podaje sekwencje obrotów wokół danej osi. 
  * Pozwala to zwiększyc efektywność programu gdy mamy dana sekwencje obrotów wokól danych osi.
  *
  *  \param[in] MatRot1  - Jest to referncja na obiekt klasy Macierz3x3, który zawiera 
  *  informacje na temat naszej macierzy rotacji, która zawiera odpowiednie 
  *  sinusy/cosinusy kąta obrotu prostokąta. Ta macierz jest niezbedna
  *  do wykorzystania zastosowaego wzoru na obrot jednego danego punktu 
  *  wokół środka układu współrzednych(Wierzcholek[i] = MacRot*Wierzcholek[i]),
  *  gdzie Wierzcholek to jest punky posiadający współrzedne x, y i z.
  * 
  * \param[in] MatRot2 - Referncja do obiektu klasy Macierz3X3. Jest to druga macierz która zawiera
  * następne wpisane kąty(zaraz po MacRot1) podane przy wporwadzaniu sekwencji obrotow 
  *  
  *  \pre
  *  Obiekt klasy prostopadloscian musi zawierać wprowadzone wcześniej 
  *  współrzędne wierzchołków prostopadloscianu początkowego, który będzie obracany.
  *
  *  \post
  * Obrócony prostopadloscian o zadane sekwecnje kątów podane przez użytkownika 
  *
  */

int Prostopadloscian::ObrotProstopadloscianu(const Macierz3x3 &MacRot1,const Macierz3x3 &MacRot2)
{
    Macierz3x3 MacRotTym = MacRot1*MacRot2;
    for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
        Wierzcholek[i] = (MacRotTym)*Wierzcholek[i];        
    }
    return 0;
}
        
 /*!
  * Metoda klasy Prostopadloscian która przesuwa prostopadlościan o zadany wektor
  *
  * \param[in] Wktr- Referencja na obiekt klasy Wektor3D
  *
  * \pre
  * Obiekt przekazywany do funkcji przez referncje powinine posiadać indormacje na
  * temat wspólrzencyh x, y i z wektora w tym przypadku punktu
  *
  *  \post
  * Przsunięty prostopadłośian o zadany wektor. tz odpowiednio dodane trzy wektory i odpowie-
  * dnio dane na temat nowych punktów przypisane do przekazanego przez referencje obiektu
  *
  */

void Prostopadloscian::PrzesunProstopadloscian(const Wektor3D &Wktr)
{
    for(int i = 0;i<ILOSC_WIERZCHOLKOW;++i){
        Wierzcholek[i] = Wierzcholek[i] + Wktr;        
    }
}


 /*!
  *  Metoda oblicza Wszystkie Długości Boków prostopadłościanu i odrazu inicjalizuje odpowiednie pola klasy prostopadlsocian odpowiednimi dlugosciami bokow
  * w zależnosci, czy jest to bok długi, krótki czy poprzeczny. Program to rozpoznaje sortując kontener sekwencyjny vector w kolejności rosnącej(Najdłuższy bok to
  * to jest najdłuższy, pośredni bok to jest poprzeczny, a najkrotszy bok to jest najkrotszy)
  * 
  * \pre Obkiet klasy Prostopadloscian musi posiadac wcześniej zainicjalizowane współrzedne wierzchołków prostopadlsocianu
  * 
  * \post Zainicjalizowane pola klasy Prostopadlosian( DlugoscBokDlugiego, DlugoscBokuKrotkiego i DlugoscBokiPoprzecznego) odpowiednimi wartośćiami 
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
     DlugoscBokuKrotszego, DlugoscBokowPorzecznych, DlugoscBokuDluzszego ( zakładając oczywiście, że boki poprzeczne bedą wartością pomiędzy 
     najkrotszym bokiem a najdluzszym)*/

   std::vector<double>::iterator pr;
   int i;
    for(pr = WszystkieDlugosciBokow.begin(),i=0; pr != pr+ILOSC_BOKOW-1, i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuKrotkiego[i]= *pr;
    for(pr = WszystkieDlugosciBokow.begin()+ILOSC_BOKOW,i=0; pr != pr+ILOSC_BOKOW-1, i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuPoprzecznego[i]= *pr;                
    for(pr = WszystkieDlugosciBokow.begin()+(2*ILOSC_BOKOW),i=0; pr != WszystkieDlugosciBokow.end(), i<ILOSC_BOKOW; ++pr, ++i)
        DlugoscBokuDluzszego[i]= *pr;                
}

/*!
*  Funkcja pomocnicza, która pozwala na sprawdzenie czy dwie wartości typu double są sobie równe
*  \param[in] a - Wartość typu double
* \param[in] b - Wartość typu double
* 
* \post Informacja o tym czy dwie podane wartości typu double są sobie równe 
* 
* \retval true - jeśli dwie wartości double są sobie równe 
* * \retval false - jeśli dwie wartości double nie są sobie równe
*/
bool BokiRowne(double a, double b){
    return fabs(a-b)<EPSILON;
}

/*!
*   Funkcja sprawdzająca poprawność długośći przeciwleglych boków prostopadloscianu
* \post Wyświetlenie komunikatu o tym czy przeciwległe długośći boków są sobie rówene i wyświetlenie tych długości
*/
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

/*!
* Funkcja Wyświetlacjąca Długości odpowiednich boków
* \param[in] DlugoscBoku - stały Wskaznik wskazujący na początek przekazanej tablicy do funkcji 
* \post Wyświetlenie na standardowe wyjście długości odpowiednich boków 
*/

void Prostopadloscian::WyswietlDlugosciBokow(const double *DlugoscBoku)
{
    std::cout<<"Dlugosc pierwszego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[0]<<std::endl;
    std::cout<<"  Dlugosc drugiego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[1]<<std::endl;
    std::cout<<"Dlugosc trzeciego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[2]<<std::endl;
    std::cout<<"Dlugosc czwartego boku: "<<MANIPULATORY_WYSWIETLAJACE<<DlugoscBoku[3]<<std::endl<<std::endl;
}

/*!
* Destruktor klasy Prostopadloscian
*/
Prostopadloscian::~Prostopadloscian(){}


