#include <iostream>

#include "Librerias.h"

using namespace std;

MatrizDouble :: MatrizDouble ()
{
	for (int cii = 0; cii < NUM_MAX_ROUTERS; cii++)
	{
		for (int cij = 0; cij < NUM_MAX_ROUTERS; cij++)
		{
			m_adMatriz[cii][cij] = VALOR_INICIAL;
		}
	}
}

void MatrizDouble :: setElemento (int iFila, int iColumna, double iElemento)
{
	m_adMatriz[iFila][iColumna] = iElemento;
}

double MatrizDouble :: getElemento (int iFila, int iColumna)
{
	return m_adMatriz[iFila][iColumna];
}

void MatrizDouble :: printMatriz (int iFilas)
{
	for (int cii = 0; cii < iFilas; cii++) 
	{
		for (int cij = 0; cij < iFilas; cij++) 
		{
			cout << m_adMatriz[cii][cij] << " ";
		}
		cout << endl;
	}
}

