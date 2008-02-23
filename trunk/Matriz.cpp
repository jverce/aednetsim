#include "Constantes.h"

public class Matriz
{
	private:
		int VALOR_INICIAL = 0;
		int m_aiMatrix[NUM_MAX_ROUTERS][NUM_MAX_ROUTERS];

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

		void setElemento(int iFila, int iColumna, int iElemento)
		{
			m_aiMatriz[iFila][iColumna] = iElemento;
		}

		int getElemento(int iFila, int iColumna)
		{
			return m_aiMatriz[iFila][iColumna];
		}
};
