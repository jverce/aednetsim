#include <iostream>
#include <cstdlib>


#ifndef _WINDOWS_H_	
	#include <conio.h>
#endif



#include "Librerias.h"

#define SALUDO1 "+------------------------------+"
#define SALUDO2 "|                              |"
#define SALUDO3 "|        A.  E.  D.            |"
#define SALUDO4 "|      N e t   S i m           |"
#define SALUDO5 "|                              |"
#define SALUDO6 "|                      2008(c) |"
#define SALUDO7 "+------------------------------+"

using namespace std;

void printSaludo ();

int main (int argc, char* argv[])
{
	int iVueltas;
	Admin admin;
	
	printSaludo();

	if (argc > 1)
	{
		iVueltas = atoi(argv[1]);
	}
	else
	{
		cout << "Ingrese la cantidad de iteraciones que desea simular: ";
		cin >> iVueltas;
	}

	admin.start(iVueltas);
	
	
	#ifdef _CONIO_H_
		_getch();
	#endif


}


void printSaludo ()
{
 	 cout << SALUDO1 << endl;
  	 cout << SALUDO2 << endl;
 	 cout << SALUDO3 << endl;
 	 cout << SALUDO4 << endl;
 	 cout << SALUDO5 << endl;
 	 cout << SALUDO6 << endl;
 	 cout << SALUDO7 << endl;
	 
	 cout << endl;	  	  	  	   	  	 
}
