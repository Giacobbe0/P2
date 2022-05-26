#ifndef graf_h
#define graf_h
#include<iostream>
#include <fstream>
#include"Lista.h"
#include"Elementy.h"

//Klasa Graf
//Przechowuje graf i algorytmy
class Graf
{
	int V; //Ilosc wierzcholkow
	Lista *lista;

public:

	Graf(int tmp) //Konstruktor grafu
	{ 
		V = tmp;
		lista = new Lista[tmp];
	}
    
	//Funkcja dodajaca krawedzie do listy
	void dodaj_krawedz(int wierz_pocz, int wierz_kon, int waga)
	{
		lista[wierz_pocz].dodaj(wierz_pocz, wierz_kon, waga);	//Lista krawedzi tworzona w konstruktorze
	}

    //Funkcja zwracajaca element z listy
	Lista getLista(int i)
	{
		return lista[i];
    }

	//Funkcja zwracajaca ilisoc wierzcholkow
	int getWierzcholki()
	{ 
		return V; 
	}

    //Prototypy funkcji
    void generuj_graf(int gestosc); 
	void Dijkstra_Lista(int gestosc);
	void Dijkstra_Macierz(int gestosc);

};

std::ostream &operator << (std::ostream &strOut, Graf *nowy_graf);

#endif