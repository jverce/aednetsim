#ifndef __ADMIN_H__
#define __ADMIN_H__

#include <map>


using namespace std;

class Admin
{
	private:		
		MatrizInt m_iMatrizOriginal;
		MatrizDouble m_dMatrizActualizada;
		int m_iCantRouters;
		map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;
		map<int, int> m_Tabla_Destino_nextHop; 
		
		void inicializarTodo ();
		void crearRouters (LectorArchivoTexto lector);
		void crearGrafo (LectorArchivoTexto lector);		
		void actualizarMatriz ();
		void dijkstra (int iOrigen);

	public:	
		Router* getRouterPorDestino (int iDestino);
		int getDestinoPorRouter (Router* router);
		int getCantRouters ();
		void start (int iVueltas);
		
};
#endif
