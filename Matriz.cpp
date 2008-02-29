#include <iostream>

#include "Librerias.h"

using namespace std;

		Matriz::Matriz()
		{
			for (int cii = 0; cii < NUM_MAX_ROUTERS; cii++)
			{
				for (int cij = 0; cij < NUM_MAX_ROUTERS; cij++)
				{
					m_aiMatriz[cii][cij] = VALOR_INICIAL;
				}
			}
		}

		void Matriz::setElemento(int iFila, int iColumna, N iElemento)
		{
			m_aiMatriz[iFila][iColumna] = iElemento;
		}

		N Matriz::getElemento(int iFila, int iColumna)
		{
			return m_aiMatriz[iFila][iColumna];
		}

		void Matriz::printMatriz(int iFilas)
		{
			for (int cii = 0; cii < iFilas; cii++) {
				for (int cij = 0; cij < iFilas; cij++) {
					cout << m_aiMatriz[cii][cij] << " ";
				}

				cout << endl;
			}
		}

