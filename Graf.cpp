#include <iostream>
#include <ctime>
#include"Graf.h"
#include"Lista.h"
#include"Elementy.h"
#define MAXINT  247483647
using namespace std;

//Funkcja generująca losowy graf
//gestosc - gestosc grafu
void Graf::generuj_graf(int gestosc)
{
	srand(time(NULL)); //Zeby nie losowac tych samych liczb
    
    int wierz_pocz, wierz_kon, waga;
    float krawedzie = gestosc*V*(V-1)/200;  //V - Ilość wierzcholkow - Parametr klasy graf
    
    cout<<endl<< "Licza wierzcholkow = " << V << ", Liczba krawedzi = " << krawedzie << ", Gestosc grafu = " << gestosc << endl; //Wyswietla grafy podczas dzilania algorytmu
    
    for(int i = 0; i < krawedzie; i++)
	{
        wierz_pocz = rand() % V; //Losowanie wierzcholka poczatkowego i koncowego
        wierz_kon = rand() % V;
        while(wierz_pocz == wierz_kon) //Zeby wierzcholek nie mogl byc zarowno poczatkowym i koncowym
		{ 
            wierz_pocz = rand() % V;
            wierz_kon = rand() % V;
        }
        waga = rand() % V + 1;

    dodaj_krawedz(wierz_pocz, wierz_kon, waga); //Dodanie krawedzi do listy
    dodaj_krawedz(wierz_kon, wierz_pocz, waga); //Dodanie odwroconej krawedzi do listy, poniewaz graf jest nieskierowany
	}

}


//Funkcja wykonujaca algorytm Dijkstry dla listy
//gestosc - gestosc grafu
void Graf::Dijkstra_Lista(int gestosc)
{
	bool *QS;                // Zbiory Q i S, sprawdzenie w ktorym zbiorze jest dany wierzcholek
  	ListaSasiedztwa **graf;  // Tablica list sąsiedztwa
  	ListaSasiedztwa *pw,*rw;

  	int i, j, x, y, w, u;

  	int v = 0; //Wierzcholek startowy
  	int n = V; //Liczba wierzcholkow
  	int m = gestosc*V*(V-1)/200;//Ilosc krawedzi

    //Tablice dynamiczne
  	int *d = new int [n];  // Tablica kosztów dojścia
  	int *p = new int [n];  // Tablica poprzedników
  	QS = new bool [n];     // Zbiory Q i S
  	graf = new ListaSasiedztwa * [n];  // Tablica list sąsiedztwa, tworzenie obiektow na liscie
  	int *S = new int [n];  // Stos

  	   //Inicjacja tablicy dynamicznych
	   for(i = 0; i < n; i++)
  	{
	    d[i] = MAXINT;
	    p[i] = -1;
	    QS[i] = false;
	    graf[i] = NULL;
	}
    //Obiekty sa stworzone, ale lista sasiedztwa nie jest wypelniona
  	
    //Odczytanie danych wejściowych
  	int wierz_start = 0; //Wierzcholek startowy
  	Krawedz *tmp = getLista(wierz_start).getKrawedz(); //Pobieranie krawedzi z listy krawedzi
  	for(i = 0; i < 2*m; i++)
	  {
  		if(tmp == NULL) //Jesli wierzcholek nie ma poloczenia
		  { 
  			wierz_start++; //Inkrementacja wierzcholka
  			while(getLista(wierz_start).getKrawedz() == NULL) //Dopoki nie znajdzie wierzcholka z poloczeniem
  				wierz_start++;
  			    if(wierz_start<n) tmp = getLista(wierz_start).getKrawedz();
  		  }
  		x = tmp->getStart();  //Odczytywanie wierzcholka poczatkowego
  		y = tmp->getKoniec(); //Odczytanie wierzcholka koncowego
  		w = tmp->getWaga();   //Odczytanie wagi
  		pw = new ListaSasiedztwa; // Tworzenie elemntu listy sasiedztwa
  		pw->v = y; //Przypisywnie wierzcholka docelowego do listy
  		pw->w = w; //Przypisanie wagi krawedzi
  		pw->next = graf[x];//Tworzenie nastepnego polaczenia
  		graf[x] = pw; //Dolaczanie elementu do listy
  		if(tmp->getNext() != NULL) tmp = tmp->getNext(); //Sprawdzenie czy dany wierzcholek ma kolejne polaczenie, jesli nie to przechodzi do nastepnego miejsca w liscie
  		else if(wierz_start<n) tmp = getLista(++wierz_start).getKrawedz(); //Przejscie do kolejnego wierzcholka
  	}


  	d[v] = 0;    // Koszt dojścia v jest zerowy

    for(i = 0; i < n; i++) //Szukanie wierzcholka w Q o najmniejszym kojscie dojscia d
  	{
	    for(j = 0; QS[j]; j++);
	    for(u = j++; j < n; j++)
	      if(!QS[j] && (d[j] < d[u])) u = j;

	    QS[u] = true; // Przeniesienie znalezionego wierzcolka do S
	   
	    for(pw = graf[u]; pw; pw = pw->next)   // Modyfikacja odpowiednio wszystkich sąsiadów u, którzy są w Q
	      if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
	      {
	        d[pw->v] = d[u] + pw->w;
	        p[pw->v] = u;
	      }
  	}

    //Test dzialania algorytmu
	/*int sptr = 0; // Wskaźnik stosu
    for(i = 1; i < n; i++)
    {
       cout <<"Sciezka"<< i << ": ";
       for(j = i; j > -1; j = p[j]) S[sptr++] = j; // Ścieżkę przechodzimy od końca ku początkowi, zapisując na stosie kolejne wierzchołki
       while(sptr) cout << S[--sptr] << " "; // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu
       cout << " $" << d[i] << endl; // Na końcu ścieżki wypisujemy jej koszt
    }*/




  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

  for(i = 0; i < n; i++)
  {
    pw = graf[i];
    while(pw)
    {
      rw = pw;
      pw = pw->next;
      delete rw;
    }
  }

  delete [] graf;

}

//Funkcja wykonujaca algorytm Dijkstry dla macierzy
//gestosc - gestosc grafu
void Graf::Dijkstra_Macierz(int gestosc){
	bool *QS;   // Zbiory Q i S, sprawdzenie w ktorym zbiorze jest dany wierzcholek
  	int i, j, x, y, w, u;
  	int **Tab;

  	int v = 0; //Wierzcholek startowy
  	int n = V; //Liczba wierzcholkow
  	int m = gestosc*V*(V-1)/200;//Ilosc krawedzi

    //Tablice dynamiczne
  	int *d = new int [n];    // Tablica kosztów dojścia
  	int *p = new int [n];    // Tablica poprzedników
  	QS = new bool [n];       // Zbiory Q i S
  	int *S    = new int [n]; // Stos

   	Tab = new int * [n]; //Tworzenie tablicy
   	for(i = 0; i < n; i++)
   		Tab[i] = new int [n];

  	//Inicjacja tablicy dynamicznych
	for(i = 0; i < n; i++)
  	{
	    d[i] = MAXINT;
	    p[i] = -1;
	    QS[i] = false;
	    for(j = 0; j < n; j++){
	    	Tab[i][j] = MAXINT;
	    	
	    }
	}

    //Odczytanie danych wejściowych
  	int wierz_start = 0; //Wierzcholek startowy
  	Krawedz *tmp = getLista(wierz_start).getKrawedz(); //Pobieranie krawedzi z listy krawedzi
  	for(i = 0; i < 2*m; i++)
	  {
  		if(tmp == NULL) //Jesli wierzcholek nie ma poloczenia
		  {
  			wierz_start++; //Inkrementacja wierzcholka
  			while(getLista(wierz_start).getKrawedz() == NULL) //Dopoki nie znajdzie wierzcholka z poloczeniem
  				wierz_start++;
  			if(wierz_start<n) tmp = getLista(wierz_start).getKrawedz();
  		  }
  		x = tmp->getStart();  //Odczytywanie wierzcholka poczatkowego
  		y = tmp->getKoniec(); //Odczytanie wierzcholka koncowego
  		w = tmp->getWaga();   //Odczytanie wagi
        
        if(Tab[x][y] > w) 
  			Tab[x][y] = w;

  		if(tmp->getNext() != NULL) tmp = tmp->getNext(); //Sprawdzenie czy dany wierzcholek ma kolejne polaczenie, jesli nie to przechodzi do nastepnego miejsca w macierzy
  		else if(wierz_start<n) tmp = getLista(++wierz_start).getKrawedz(); //Przejscie do kolejnego wierzcholka
  	}


  	d[v] = 0;  // Koszt dojścia v jest zerowy

    for(i = 0; i < n; i++) //Szukanie wierzcholka w Q o najmniejszym kojscie dojscia d
  	{
	    for(j = 0; QS[j]; j++);
	    for(u = j++; j < n; j++)
	    if(!QS[j] && (d[j] < d[u])) u = j;

	    QS[u] = true; //// Przeniesienie znalezionego wierzcolka do S

	    for(int c = u; c < n ; c++) // Modyfikacja odpowiednio wszystkich sąsiadów u, którzy są w Q
	    	for(int k = 0; k < n; k++)
			    if(!QS[k] && (d[k] > d[c] + Tab[c][k]))
			    {

			    	d[k] = d[c] + Tab[c][k];
			    	p[k] = c;
			    }

  	}

    //Test dzialania algorytmu
	/*int sptr = 0; // Wskaźnik stosu
    for(i = 1; i < n; i++)
    {
       cout <<"Sciezka"<< i << ": ";
       for(j = i; j > -1; j = p[j]) S[sptr++] = j; // Ścieżkę przechodzimy od końca ku początkowi, zapisując na stosie kolejne wierzchołki
       while(sptr) cout << S[--sptr] << " "; // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu
       cout << " $" << d[i] << endl; // Na końcu ścieżki wypisujemy jej koszt
    }*/


  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

}

//Przeciazenie operatora wyjscia dla grafu
std::ostream &operator << (std::ostream &strOut, Graf *nowy_graf){

	for(int i=0; i<nowy_graf->getWierzcholki(); ++i)
	{

		Krawedz *n_tmp = nowy_graf->getLista(i).getKrawedz();

		strOut<< i << " -> ";

		while(n_tmp != NULL)
		{
			strOut<< n_tmp->getKoniec() << "#" << n_tmp->getWaga() << ", ";
			n_tmp = n_tmp->getNext();
		}
		
		strOut<<"\n";
	}
	return strOut;
}
