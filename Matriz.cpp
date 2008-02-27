#include "Constantes.h"
#include <iostream>

using namespace std;

template <class N> class Matriz
{
	private:
		static const int VALOR_INICIAL = 0;
		N m_aiMatriz[NUM_MAX_ROUTERS][NUM_MAX_ROUTERS];

	public:
		Matriz()
		{
			for (int cii = 0; cii < NUM_MAX_ROUTERS; cii++)
			{
				for (int cij = 0; cij < NUM_MAX_ROUTERS; cij++)
				{
					m_aiMatriz[cii][cij] = VALOR_INICIAL;
				}
			}
		}

		void setElemento(int iFila, int iColumna, N iElemento)
		{
			m_aiMatriz[iFila][iColumna] = iElemento;
		}

		N getElemento(int iFila, int iColumna)
		{
			return m_aiMatriz[iFila][iColumna];
		}

		void printMatriz(int iFilas)
		{
			for (int cii = 0; cii < iFilas; cii++) {
				for (int cij = 0; cij < iFilas; cij++) {
					cout << m_aiMatriz[cii][cij] << " ";
				}

				cout << endl;
			}
		}
};
