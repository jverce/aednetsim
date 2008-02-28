#include "Admin.h"
        
		void Admin::inicializarTodo()
		{
			LectorArchivoTexto lector;

			m_iMatrizOriginal = lector.getMatriz();
			m_iCantRouters = lector.getCantRouters();
			crearRouters(lector);
			crearGrafo(lector);
			actualizarMatriz();
		}

		void Admin::crearRouters(LectorArchivoTexto lector)
		{
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				Router* router = new Router(cii);
				m_aRefRouters[cii] = router;
				m_aDestRouters[router] = cii;
			}
		}

		void Admin::crearGrafo(LectorArchivoTexto lector)
		{
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				list<int> aiLista = lector.getRoutersConectados(cii);
				list<int> :: iterator it = aiLista.begin();

				while ( it != aiLista.end() )
				{
					m_aRefRouters[cii] -> agregarVecino(m_aRefRouters[*it]);
					it++;
				}

				for (int cij = 0; cij < lector.getNumeroPcs(cii); cij++)
				{
					m_aRefRouters[cii] -> agregarHost(new Host(cii, cij, this));
				}
			}
		}
		
		void Admin::actualizarMatriz()
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

		void Admin::dijkstra(int iOrigen)
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

				for (int cij = 0; cij < m_iCantRouters; cij++)
				{
					tabla.crearEntradaBandWidth(
					m_aRefRouters[cij],
					m_iMatrizOriginal.getElemento(cii, cij));
				}
			}

			m_aRefRouters[iOrigen] -> setTabla(tabla);

		}

		Router* Admin::getRouterPorDestino(int iDestino)
		{
			return m_aRefRouters[iDestino];
		}

		int Admin::getDestinoPorRouter(Router* router)
		{
			return m_aDestRouters[router];
		}

		int Admin::getCantRouters()
		{
			return m_iCantRouters;
		}
		
		void Admin::start (int iVueltas)
		{
			inicializarTodo();
			
			for (int cii = 0; cii < m_iCantRouters; cii++)
			{
				list<Host*> :: iterator it = m_aRefRouters[cii] -> getListaHosts().begin();
				while ( !it.end() )
				{
					(*it) -> enviar();
					it++;
				}
			}

			for (int cii = 0; cii < iVueltas; cii++)
			{
				actualizarMatriz();
				for (int cij = 0; cij < m_iCantRouters; cij++) 
				{
					dijkstra(cii);
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


		
