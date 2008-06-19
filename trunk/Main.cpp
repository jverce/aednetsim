#include <iostream>
#include <cstdlib>

#include "Librerias.h"

using namespace std;

int main (int argc, char* argv[])
{
	int iVueltas;
	Admin admin;

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
}
