#ifndef __MATRIZDOUBLE_H__
#define __MATRIZDOUBLE_H__


using namespace std;

class MatrizDouble
{
	private:
	
		static const int VALOR_INICIAL = 0;
		double m_adMatriz[NUM_MAX_ROUTERS][NUM_MAX_ROUTERS];

	public:
	
		MatrizDouble();
		void setElemento(int iFila, int iColumna, double iElemento);
		double getElemento(int iFila, int iColumna);
		void printMatriz(int iFilas);
};
#endif
