#include "Librerias.h"

int main ()
{
	int iVueltas;
	Admin admin;

	cout << "Ingrese la cantidad de iteraciones que desea simular: ";
	cin >> iVueltas;

	admin.start(iVueltas);
}
