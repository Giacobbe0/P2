#ifndef lista_h
#define lista_h
#include"Elementy.h"

//Struktura ListaSasiedztwa
//Reprezantujaca listę sąsiedztwa dla pojedyńczego wierzchołka
struct ListaSasiedztwa
{
	ListaSasiedztwa *next; //Wskaznik do tworzenia nastepnego polaczenia do kolejnego wierzcholka
	int v; //Para wierzchołków, początkowy oraz końcowy
	int w; //Waga krawedzi
};

//Struktura Lista
//Przechowuje liste i algorytmy
class Lista
{
	Wierzcholek *wierz; //Wierzcholek
	Krawedz *polacz;	//Polaczenie

public:
	Lista()
	{
		wierz = NULL;
		polacz = NULL;
	}

    //Funkcja dodajaca element do listy
	//wierz_pocz - wierzcholek poczatkowy grafu
	//wierz_kon - wierzcholek koncowy grafu
	//waga - waga grafu
	void dodaj(int wierz_pocz, int wierz_kon, int waga)
	{
		Wierzcholek *wierz_kon_tmp = new Wierzcholek(wierz_pocz); //Wierzcholek garfu
		Krawedz *n_tmp = new Krawedz(wierz_pocz, wierz_kon, waga); //Krawiedz grafu
		
		if(wierz == NULL) wierz = wierz_kon_tmp;

		if(polacz == NULL) polacz = n_tmp;
		else //Jesli krawedz jest juz poloczona
		{
			Krawedz *nn_tmp = polacz;
			while(nn_tmp->getNext() != NULL) //Laczymy nastepna krawedz
			nn_tmp = nn_tmp->getNext();
			nn_tmp->setNext(n_tmp);
		}
	}

    //Funkcja zwarajaca poloczenie
	Krawedz *getKrawedz()
	{
		return polacz;
    }

};

#endif