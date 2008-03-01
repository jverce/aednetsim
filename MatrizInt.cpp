#include <iostream>

#include "Librerias.h"

using namespace std;

		MatrizInt::MatrizInt()
		{
			for (int cii = 0; cii < NUM_MAX_ROUTERS; cii++)
			{
				for (int cij = 0; cij < NUM_MAX_ROUTERS; cij++)
				{
					m_aiMatriz[cii][cij] = VALOR_INICIAL;
				}
			}
		}

		void MatrizInt::setElemento(int iFila, int iColumna, int iElemento)
		{
			m_aiMatriz[iFila][iColumna] = iElemento;
		}

		int MatrizInt::getElemento(int iFila, int iColumna)
		{
			return m_aiMatriz[iFila][iColumna];
		}

		void MatrizInt::printMatriz(int iFilas)
		{
			for (int cii = 0; cii < iFilas; cii++) {
				for (int cij = 0; cij < iFilas; cij++) {
					cout << m_aiMatriz[cii][cij] << " ";
				}

				cout << endl;
			}
		}

