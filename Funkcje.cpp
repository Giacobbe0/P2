#include <iostream>
#include<fstream>
#include"Funkcje.h"
#include"Graf.h"
using namespace std;

//Funkcja zapisujaca czas dzailania algorytmu do pliku dla kilku testow
//lista[] - tablica zmiennych zawierajacych czas dla listy
//macierz[] - tablica zmiennych zawierajacych czas dla macierzy
void zapis_czasu(double lista[], double macierz[])
{
	ofstream plik, plik2;
	plik.open("Czasy lista.txt"); //Otwarcie plikow
	plik2.open("Czasy macierz.txt");

	for (int i = 0; i < 20; ++i)
	{
		plik<<lista[i]<<"\n"; //Zapis wynikow do plikow
		plik2<<macierz[i]<<"\n";
	}
}

//Funkcja zapisujaca czas dzailania algorytmu do pliku dla pojedynczego testu
//lista - zmienna zawierajaca czas dla listy
//macierz - zmienna zawierajaca czas dla macierzy
void zapis_czasu_2(double lista, double macierz)
{
	ofstream plik, plik2;
	plik.open("Czas lista.txt"); //Otwarcie plikow
	plik2.open("Czas macierz.txt");
	plik<<lista<<"\n";   //Zapis wynikow do plikow
	plik2<<macierz<<"\n";
}

//Funkcja generujaca i zapisujaca graf do pliku
void zapis_do_pliku()
{
	int krawedzie,wierzcholki,wierz_start,waga;
	double gestosc;
	string nazwa;
	ofstream plik;
	cout<<"Podaj nazwe pliku do zapisania grafu   ";
	cin >> nazwa;

	plik.open(nazwa);
	cout << "Podaj ilosc wierzcholkow, wierzcholek startowy oraz gestosc z przedzialu (0-1>" << endl;
	cin >> wierzcholki >> wierz_start >> gestosc;
	if(gestosc>0&&gestosc<=1) //Gestosc tylko z przedzialu 0-1
	{
	krawedzie = (wierzcholki * (wierzcholki - 1)) / 2; // Wzor na ilosc krawedzi w grafie 
		if (plik.good())
		{
			plik << (int)(krawedzie*gestosc) << " " << wierzcholki << " " << wierz_start << endl; //Zapisanie w pierszej lini pliku informacji o grafie

			for (int i = 0; i < wierzcholki; i++)
			{
				for (int j = i; j < wierzcholki; j++)
				{
					if (i != j)
					{
						waga = rand() % 100 + 1; //Losowanie wagi krawedzi
						plik << i << " " << j << " " << waga << endl; //Zapis krawedzi wraz z waga do pliku 
						plik << j << " " << i << " " << waga << endl; //Zapis odwroconej krawedzi do pliku, poniewaz graf jest nieskierowany
					}
				}
			}
					cout<<"Wygenerowano graf do pliku "<<nazwa<<endl;
		}
		else
		{
			printf("zla nazwa pliku \n");
		}
	}
	else
	{
		cout<<"Wybrano zla gestosc"<<endl;
	}
	plik.close();
}

//Funkcja wczytujaca graf z pliku i wykonujaca testy efektywnosci dla tego grafu
void wczytanie_z_pliku()
{
    string nazwa;
	ifstream plik;
	clock_t start;
	clock_t stop;
	double czas1, czas2;
	int krawedzie, wierzcholki, wierz_start;
	int wierz_pocz, wierz_kon, waga; 

	cout<<"Podaj nazwe pliku do wczytania grafu     ";
	cin >> nazwa;
	plik.open(nazwa);
	plik >> krawedzie; //Wczytanie z pliku informacji o grafie
	plik >> wierzcholki;
	plik >> wierz_start;
	
	float gestosc = (200*krawedzie)/(wierzcholki*(wierzcholki-1));//Obliczenie gestosci grafu ze wzoru
	Graf *nowy_graf = new Graf(wierzcholki); //Tworzenie pustego szablonu grafu

	for(int i = 0; i < krawedzie; i++) //Wczytywanie grafu z pliku
	{
    	plik >> wierz_pocz; //Wczytanie z pliku sciezek wraz z waga
        plik >> wierz_kon;
        plik >> waga;

    	nowy_graf->dodaj_krawedz(wierz_pocz, wierz_kon, waga); //Dodanie krawedzi do grafu
    	nowy_graf->dodaj_krawedz(wierz_kon, wierz_pocz, waga); //Dodanie odwroconej grawedzi do grafu, poniewaz graf jest nieskierowany
	}

    czas1 = 0; //Przeprowadzenie testow dla listy
	start = clock();
	nowy_graf->Dijkstra_Lista(gestosc);
    stop = clock();
	czas1 += double(stop - start) / CLOCKS_PER_SEC;
	cout<< "Czas wykonywania algorytmu dla listy: " <<czas1<< " s" << endl;	

    czas2 = 0; //Przeprowadzenie testow dla macierzy
    start = clock();
	nowy_graf->Dijkstra_Macierz(gestosc);
	stop = clock();
	czas2 += double(stop - start) / CLOCKS_PER_SEC;	
	cout<< "Czas wykonywania algorytmu dla macierzy: " <<czas2<< " s" << endl;

	zapis_czasu_2(czas1, czas2); //Zapis wynikow do pliku
}

//Funkcja generujaca losowe grafy i wykonujaca dla nich testy efektywnosci
void losowy()
{
	int Wierzcholki[5] = { 10,50,100,200,300 };//Liczby wierzcholkow
	int Gestosc[4] = { 25,50,75,100 };//Warosc gestosci w procentach

	clock_t start;
	clock_t stop;
	double czas1, czas2;
	double czasy1[20], czasy2[20];
	int q=0;

	for(int i = 0; i < 4; i++) //Dla kazdej gestosci
	{
		for(int j = 0; j < 5; j++) //Dla kazdej liczby wierzcholkow
		{
			Graf *nowy_graf = new Graf(Wierzcholki[j]); //Tworzenie wierzcholkow grafu
            nowy_graf->generuj_graf(Gestosc[i]); //Tworzenie krawedzi grafu
			czas1 = 0;

			for(int k=0; k<100; k++) //Tworzenie 100 losowych grafow
			{
				start = clock(); //Przeprowadzenie testow dla listy
				nowy_graf->Dijkstra_Lista(Gestosc[i]);
				stop = clock();
				czas1 += double(stop - start) / CLOCKS_PER_SEC;
			}
			
			cout<< "Czas wykonywania algorytmu dla listy: " <<czas1/100<< " s" << endl; //Wyswietlenie usrednionego czasu
			czasy1[q] = czas1/100; //Zapis do zmiennej usrednionego czasu

			czas2 = 0;

			for(int l=0; l<100; l++) //Tworzenie 100 losowych grafow
			{
				start = clock(); //Przeprowadzenie testow dla macierzy
				nowy_graf->Dijkstra_Macierz(Gestosc[i]);
				stop = clock();
				czas2 += double(stop - start) / CLOCKS_PER_SEC;
			}
			
			cout<< "Czas wykonywania algorytmu dla macierzy: " <<czas2/100<< " s" << endl; //Wyswietlenie usrednionego czasu
			czasy2[q] = czas2/100; //Zapis do zmiennej usrednionego czasu
			q++;
		}
	}
	zapis_czasu(czasy1, czasy2); //Zapis wynikow do pliku
}