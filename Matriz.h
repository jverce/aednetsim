#ifndef __MATRIZ_H__
#define __MATRIZ_H__


using namespace std;

template <class N> class Matriz
{
	private:
	
		static const int VALOR_INICIAL = 0;
		N m_aiMatriz[NUM_MAX_ROUTERS][NUM_MAX_ROUTERS];

	public:
	
		Matriz();
		void setElemento(int iFila, int iColumna, N iElemento);
		N getElemento(int iFila, int iColumna);
		void printMatriz(int iFilas);
};
#endif
