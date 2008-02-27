#include <map>
#include <list>
#include "Router.cpp"
#include "Matriz.cpp"
#include "Constantes.h"

using namespace std;

class Admin
{
	private:
		Matriz<int> m_iMatrizOriginal;
		Matriz<double> m_dMatrizActualizada;
		int m_iCantRouters;
		map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;
		map<int, int > m_Tabla_Destino_nextHop; 
        
		void inicializarTodo()
		{
			LectorArchivoTexto lector;

			m_iMatrizOriginal = lector.getMatriz();
			m_iCantRouters = lector.getRouters();
			crearRouters(m_iCantRouters, lector);
			crearGrafo(lector);
			actualizarMatriz();
		}

		void crearRouters(int iCantRouters, LectorArchivoTexto lector)
		{
			for (int cii = 0; cii < iCantRouters; cii++)
			{
				Router* router = new Router(cii);
				m_aRefRouters[cii] = router;
				m_aDestRouters[router] = cii;

				for (int cij = 0; cij < lector.getNumeroPcs(cii); cij++)
				{
					Host* host = new Host(cii, cij);
					router -> agregarHost(host);
				}
			}
		}

		void crearGrafo(LectorArchivoTexto lector)
		{
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				list<int> aiLista = lector.getRoutersConectados(cii);
				list<int> :: iterator it = aiLista.begin();

				while ( it != aiLista.end() )
				{
					m_aRefRouters[cii] -> agregarVecino(m_aRefRouters[it -> front()]);
					aiLista.pop_front();

					it++;
				}

				for (int cij = 0; cij < lector.getNumeroPcs(cii); cij++)
				{
					m_aRefRouters[cii] -> agregarHost(new Host(cii, cij));
				}
			}
		}
		
		void actualizarMatriz()
		{
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				for (int cij = 0; cij < m_iCantRouters; cij++)
				{
					if (cii != cij)
					{
						double dNuevoCosto =
						( 1 / (double) m_iMatrizOriginal.getElemento(cii, cij) ) *
						( 1 + m_aRefRouters[cii] -> getCarga(m_aRefRouters[cij]) );

						m_dMatrizActualizada.setElemento(cii, cij, dNuevoCosto);
					}
					else
					{
						m_dMatrizActualizada.setElemento(cii, cij, PROPIO_ROUTER);
					}
				}
			}
		}

		void dijkstraJuanjo(int iOrigen)
		{
			priority_queue<pair<double, int>> aColaDePares;
			pair<double, int> nodoTemporal;
			int iVertice1;
			int iVertice2;
			double adDistMinimas[m_iCantRouters];
			int aiNextHop[m_iCantRouters];
			bool abListo[m_iCantRouters];

			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				adDistMinimas[cii] = INF;
				aiNextHop[cii] = PROPIO_ROUTER;
				abListo[cii] = false;
			}

			adDistMinimas[iOrigen] = 0;
			aColaDePares.push(pair<double, int> (adDistMinimas[iOrigen], iOrigen));

			while ( !adDistMinimas.empty() )
			{
				nodoTemporal = aColaDePares.top();
				aColaDePares.pop();

				iVertice1 = nodoTemporal.second;

				if ( !abListo[iVertice1] )
				{
					abListo[iVertice1] = true;

					for (iVertice2 = 0; iVertice2 < m_iCantRouters; iVertice2++)
					{
						if (
						!abListo[iVertice2] &&
						m_dMatrizActualizada.getElement(iVertice1, iVertice2) > 0 &&
						( adDistMinimas[iVertice1] + 
						m_dMatrizActualizada.getElement(iVertice1, iVertice2) )
						< adDistMinimas[iVertice2] )
						{
							adDistMinimas[iVertice2] = 
							m_dMatrizActualizada[iVertice1][iVertice2] +
							adDistMinimas[iVertice1];
							
							aiNextHop[iVertice2] = iVertice1;
							
							aColaDePares.
							push(pair<double, int> (-adDistMinimas[iVertice2], iVertice2));
						}
					}
				}
			}

			Tabla tabla;
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				if (aiNextHop[cii] != PROPIO_ROUTER)
				{
					tabla.crearEntradaDestinos(cii, m_aRefRouters[aiNextHop[cii]]);
				} 
				else
				{
					tabla.crearEntradaDestinos(cii, m_aRefRouters[aiNextHop[iOrigen]]);
				}
			}

			m_aRefRouters[iOrigen] -> setTabla(tabla);

		}

	public:
		Router* getRouterPorDestino(int iDestino)
		{
			return m_aRefRouters[iDestino];
		}

		int getDestinoPorRouter(Router* router)
		{
			return m_aDestRouters[router];
		}
		
		void start (int iVueltas)
		{
			inicializarTodo();
			
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				list<Host*> :: iterator iterator = m_aRefRouters[cii] -> getListaHosts().begin();
				while ( !iterator.end() )
				{
					(*iterator) -> enviar();
					iterator++;
				}
			}

			for (int cii = 0; cii < iVueltas; cii++)
			{
				actualizarMatriz();
				for (int cij = 0; cij < m_iCantRouters; cij++) 
				{
					dijkstraJuanjo(cii);
				}

				for (int cij = 0; cij < CICLOS_ACTUALIZACION; cij++)
				{
					for (int cik = 0; cik < m_iCantRouters; cik++)
					{
						m_aRefRouters[cik] -> enviar();
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
