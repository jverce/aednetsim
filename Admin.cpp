#include <map>
#include "Router.cpp"
#include "Matriz.cpp"
#include "Constantes.h"

using namespace std;

class Admin
{
	private:
		Matriz m_iMatrizOriginal;
		Matriz m_iMatrizActualizada;
		int m_iCantRouters;
		map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;
		map<int, int > m_Tabla_Destino_nextHop; 
        
		void inicializarTodo()
		{
			LectorArchivoTexto lector;

			m_iMatrizOriginal = lector.getMatriz();
			m_iCantRouters = lector.getRouters();
		}

		Router* getRouterPorDestino(int iDestino)
		{
			return m_aRefRouters[iDestino];
		}

		int getDestinoPorRouter(Router* router)
		{
			return m_aDestRouters[router];
		}
		
		void actualizarMatriz()
		{
		}

		void dijkstraJuanjo(int iOrigen)
		{
			priority_queue<pair<int, int>> aiColaDePares;
			pair<int, int> nodoTemporal;
			int iVertice1;
			int iVertice2;
			int aiDistMinimas[m_iCantRouters];
			int aiNextHop[m_iCantRouters];
			int abListo[m_iCantRouters];

			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				aiDistMinimas[cii] = INF;
				aiNextHop[cii] = -1;
				abListo[cii] = false;
			}

			aiDistMinimas[iOrigen] = 0;
			aiColaDePares.push(pair<int, int> (aiDistMinimas[iOrigen], iOrigen));

			while ( !aiDistMinimas.empty() )
			{
				nodoTemporal = aiColaDePares.top();
				aiColaDePares.pop();

				iVertice1 = nodoTemporal.second;

				if ( !abListo[iVertice1] )
				{
					abListo[iVertice1] = true;

					for (iVertice2 = 0; iVertice2 < m_iCantRouters; iVertice2++)
					{
						if (
						!abListo[iVertice2] &&
						m_iMatrizActualizada.getElement(iVertice1, iVertice2) > 0 &&
						( aiDistMinimas[iVertice1] + 
						m_iMatrizActualizada.getElement(iVertice1, iVertice2) )
						> aiDistMinimas[iVertice2] )
						{
							aiDistMinimas[iVertice2] = 
							m_iMatrizActualizada[iVertice1][iVertice2] +
							aiDistMinimas[iVertice1];
							
							aiNextHop[iVertice2] = iVertice1;
							
							aiColaDePares.
							push(pair<int, int> (-aiDistMinimas[iVertice2], iVertice2));
						}
					}
				}
			}
		}


		
		void dijkstra(int iOrigen);
};

void Admin::dijkstra (int iOrigen)
{
	int n_Routers = m_iCantRouters;
	int costo[m_iCantRouters];          /* D   distancias minima desde s al nodo i */
	int nextHop[m_iCantRouters];      /* ruta hacia el nodo i desde s */
	bool permanente[m_iCantRouters]; 
     
	priority_queue< pair<int, int> > cola;
	pair <int, int> nodo;

	int Vi, Vj;     

	for (int i=1; i<= n_Routers; i++){
		costo[i] = INF;
		nextHop[i] = -1;
		permanente[i] = false;
	}
	costo[s] = 0;
	cola.push( pair <int, int> (costo[iOrigen], iOrigen) );

	while( !pq.empty() ) {
		nodo = cola.top();  cola.pop();
		Vi = nodo.second;
		if ( !permanente[Vi] ) {
			permanente[Vi] = true;
			for (Vj = 1; Vj <= n; Vj++){
				if ( 
				!permanente[Vj] && 
				m_MatrizActualizada.getElemento(Vi , Vj) > 0 && 
				D[Vi] + m_MatrizActualizada.getElemento(Vi , Vj) > D[Vj] ){
					D[Vj] = D[Vi] + m_MatrizActualizada.getElemento(Vi ; Vj);
					nextHop[Vj] = Vi,;
					cola.push( pair <int,int> (-D[Vj], Vj) );
				}
			}
		}
	}

	for ( int cii = 1 ; cci <= n_Routers; cci++)
		m_Tabla_Destino_nextHop[cii] = nextHop[ci];

};
