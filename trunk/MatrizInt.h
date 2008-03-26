#ifndef __MATRIZINT_H__
#define __MATRIZINT_H__


using namespace std;

class MatrizInt
{
	private:
		static const int VALOR_INICIAL = 0;
		int m_aiMatriz[NUM_MAX_ROUTERS][NUM_MAX_ROUTERS];

	public:
		MatrizInt ();
		void setElemento (int iFila, int iColumna, int iElemento);
		int getElemento (int iFila, int iColumna);
		void printMatriz (int iFilas);
};
#endif
