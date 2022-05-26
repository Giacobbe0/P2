#ifndef elementy_h
#define elementy_h

//Klasa Wierzcholek
//Przechowuje numey wierzcholkow
class Wierzcholek
{
	int numer; //Numer wierzcholka
	Wierzcholek *next; //Wskaznik na nastepny wierzcholek
	
public:

	Wierzcholek(int nr) //Konstruktor wierzcholka
	{ 
		numer = nr;
		next = NULL;
	}

	//Funkcja zwacajaca nastepna krawedz
	Wierzcholek *getNext()
	{ 
		return next;
    }

	//Funkcja ustawiajaca nastepna krawedz
	void setNext(Wierzcholek *tmp) 
	{
		 next = tmp; 
	}
};

//Klasa krawedz
//Prezechowuje krawedzie 
class Krawedz
{
	int wierz_pocz, wierz_kon; //Poczatek i koniec krawedzi
	int waga; //Waga krawedzi
	Krawedz *next; //Wskaznik na nastepny element

public:
	Krawedz(int p, int k, int w) //Konstruktor krawedzi
	{ 
		wierz_pocz = p;
		wierz_kon = k;
		waga = w;
		next = NULL;
	}

    //Funkcje zwracajace wartosci krawedzi oraz nastepne krawedzie
	Krawedz *getNext()  
	{
	   return next;
	}
	void setNext(Krawedz *tmp)
	{
		next = tmp;
    }
	int getWaga()
	{
		return waga;
	}

	int getStart()
	{
		return wierz_pocz;
	};
	int getKoniec()
	{
		return wierz_kon;
    }
};

#endif