#include <iostream>
#include<fstream>
#include"Funkcje.h"
using namespace std;

int main()
{
   int wybor;
   while(1)
   {
	   cout<<"Menu Programu"<<endl;
	   cout<<"1. Wygeneruj graf do pliku \n2. Wczytaj graf z pliku i przeprowadz testy \n3. Wygenruj losowy graf i przeprowadz testy\n4. Zakoncz program\n";
	   cout<<"Wybrana opcja   ";
       cin>>wybor;
       switch(wybor) //Menu programu
	   {
   	      case 1:
	          zapis_do_pliku();
   	      break;
   	      case 2:
   		      wczytanie_z_pliku();
          break;
	      case 3:
	          losowy();
	      break;
	      case 4:
	          return 0;
	      break;
        }
    }
}