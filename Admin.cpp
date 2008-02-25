#include <map>
#include "Router.cpp"
#include "Matriz.cpp"

#define INF 999  

class Admin
{
	private:
		Matriz m_MatrizOriginal;
		Matriz m_MatrizActualizada;
		int m_iCantRouters;
		map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;
		map<int, int> m_Tabla_Destino_nextHop; 
        
		void incializarTodo()
		{
			LectorArchivoTexto lector;

			m_MatrizOriginal = lector.getMatriz();
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

		void dijkstra(int iOrigen);
};

void Admin::dijkstra (int iOrigen)
{
	int cantRouters = m_iCantRouters;
	int costo[cantRouters];          /* D   distancias minima desde s al nodo i */
	int nextHop[cantRouters];      /* ruta hacia el nodo i desde s */
	bool permanente[cantRouters]; 
     
	priority_queue< pair<int, int> > cola;
	pair <int, int> nodo;

	int Vi, Vj;     

	for (int i=1; i<= cantRouters; i++) {
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
			for (Vj = 1; Vj <= cantRouters; Vj++) {
				if ( 
					!permanente[Vj] && 
					m_MatrizActualizada.getElemento(Vi , Vj) > 0 && 
					D[Vi] + m_MatrizActualizada.getElemento(Vi , Vj) > D[Vj] ) {
						D[Vj] = D[Vi] + m_MatrizActualizada.getElemento(Vi, Vj);
						nextHop[Vj] = Vi;
						cola.push( pair <int,int> (-D[Vj], Vj) );
				}
			}
		}
	}


	for ( int cci = 1 ; cci <= cantRouters; cci++)
		m_Tabla_Destino_nextHop[cci] = nextHop[ci];
};
