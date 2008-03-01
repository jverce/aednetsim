#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "Librerias.h"

using namespace std;


		bool Router::isVecino (Router* router)
		{
			map< Router*, queue<Paquete> > :: iterator it = m_ColasVecinos.begin();
			
			while ( it != m_ColasVecinos.end() )
			{
				if ( (it -> first) == router)
				{
					return true;
				}

				it++;
			}
			
			return false;
		}

		bool Router::isMismoRouter(Router* router)
		{
			return router == this;
		}

		void Router::vaciarBuffer()
		{
			m_Buffer.sort();
			while (!m_Buffer.empty())
			{
				meterEnLista(m_Buffer.get());
			}
		}

		void Router::meterEnLista(Pagina pagina)
		{
			for (int cii = 0; cii < pagina.getCantPaquetes(); cii++) 
			{
				m_ListaPaquetes.push_back(pagina.getPaquete(cii));
				m_ArchivoSalida << "Entra_ " + pagina.getPaquete(cii).toString() << endl;
			}		
		}

		void Router::meterEnLista(Paquete paquete)
		{
			m_ListaPaquetes.push_back(paquete);
			m_ArchivoSalida << "Entra_ " + paquete.toString() << endl;
		}

		Router* Router::elegirInterfaz(Paquete paquete)
		{
			return elegirInterfaz(paquete.getIPDestino().getPrimerOcteto());
		}

		Router* Router::elegirInterfaz(int iRouterId)
		{
			Router* router = m_TablaEnrutamiento -> getNextHop(iRouterId);

			if (isVecino(router))
			{
				return router;
			}
			else
			{
				return elegirInterfaz(router -> getId());
			}
		}

		Paquete Router::getAt(list<Paquete> lista, int iIndex)
		{
			list<Paquete> :: iterator it = lista.begin();

			for (int cii = 0; cii < iIndex; cii++)
			{
				it++;
			}

			return (*it);
		}

		string Router::toString()
		{
			stringstream strStream;

			strStream << "Router numero " << m_i1Oct;

			return strStream.str();
		}

		string Router::toString(int iNum)
		{
			stringstream strStream;

			strStream << iNum;

			return strStream.str();
		}


		Router::Router(int i1Oct)
		{
			m_i1Oct = i1Oct;
			m_iCantHosts = 0;

			string szAuxFileName = "Router_" + toString(i1Oct) + ".log";
			char* szFileName = new char[szAuxFileName.size() + 1];
			strcpy(szFileName, szAuxFileName.c_str());
			
			m_ArchivoSalida.open(szFileName);
		}

		int Router::getId()
		{
			return m_i1Oct;
		}

		void Router::setTabla(Tabla* tabla)
		{
			m_TablaEnrutamiento = tabla;
			m_ArchivoSalida << "La tabla de enrutamiento ha cambiado." << endl;
			m_ArchivoSalida << "Nueva tabla de enrutamiento: " << endl;
			m_ArchivoSalida << m_TablaEnrutamiento -> toString() << endl;
		}

		list<Host*> Router::getListaHosts()
		{
			return m_ListaHosts;
		}

		int Router::getCarga(int iDestino)
		{
			list<Paquete> :: iterator it = m_ListaPaquetes.begin();
			int iCounter = 0;

			while (it != m_ListaPaquetes.end())
			{
				if ( (it -> getIPDestino().getPrimerOcteto()) == iDestino )
				{
					iCounter++;
				}
				it++;
			}

			return iCounter;
		}

		void Router::agregarHost(Host* host)
		{
			m_ListaHosts.push_back(host);
			m_iCantHosts++;
			
			m_aRefHosts[host -> getIP().getSegundoOcteto()] = host;
			
			queue<Paquete> cola;
			m_ColasLocales[host] = cola;
		}

		void Router::agregarVecino(Router* vecino)
		{
			queue<Paquete> cola;

			m_ColasVecinos[vecino] = cola;	
		}

		int Router::getCarga(Router* interfaz)
		{
			return getCarga(interfaz -> getId());
		}

		void Router::recibir(Pagina pagina)
		{
			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_Buffer.insert(pagina.getPaquete(cii));
			}
		}

		void Router::recibir(Paquete paquete)
		{
			if (paquete.getIPDestino().getPrimerOcteto() != m_i1Oct)
			{
				m_Buffer.insert(paquete);
			}
			else
			{
				recibirInterno(paquete);
			}
		}

		void Router::recibirInterno(Paquete paquete)
		{
			m_ColasLocales[m_aRefHosts[paquete.getIPDestino().getSegundoOcteto()]].push(paquete);
		}

		void Router::enviarLocal()
		{
			for (int cii = 0; cii < m_iCantHosts; cii++)
			{
				queue<Paquete> cola = m_ColasLocales[m_aRefHosts[cii]];
				list<Paquete> listaPaquetes;
				list<double> listaIdPagina;

				while (!cola.empty())
				{
					listaPaquetes.push_back(cola.front());
					listaIdPagina.push_back(cola.front().getIDPagina());
					cola.pop();
				}

				listaIdPagina.sort();
				listaIdPagina.unique();

				while (!listaIdPagina.empty())
				{
					double dIdPagina = listaIdPagina.front();
					listaIdPagina.pop_front();

					list<Paquete> :: iterator it = listaPaquetes.begin();
					list<Paquete> listaAuxiliar;
					Paquete paqAux = *it;
					while (it != listaPaquetes.end())
					{
						if ( it -> getIDPagina() == dIdPagina )
						{
							listaAuxiliar.push_back(*it);
						}

						it++;
					}

					if (listaAuxiliar.size() == paqAux.getTotalPaquetes())
					{
						Pagina pagina(listaAuxiliar);
						m_aRefHosts[cii] -> recibir(pagina);
					}
				}
			}
		}
					
		void Router::enviar()
		{
			vaciarBuffer();
			enviarLocal();

			map< Router*, queue<Paquete> > :: iterator it_1 = m_ColasVecinos.begin();

			while (it_1 != m_ColasVecinos.end())
			{
				Router* routerDestino = it_1 -> first;

				list<Paquete> :: iterator it_2 = m_ListaPaquetes.begin();
				for (int cij = 0; 
						(cij < m_TablaEnrutamiento -> getBW(routerDestino)) || 
						(it_2 != m_ListaPaquetes.end()); it_2++)
				{
					if (elegirInterfaz(*it_2) == routerDestino)
					{
						m_ColasVecinos[routerDestino].push(*it_2);
						m_ListaPaquetes.erase(it_2);

						cij++;
					}
				}

				it_1++;
			}

			map< Router*, queue<Paquete> > :: iterator it = m_ColasVecinos.begin();

			while (it != m_ColasVecinos.end()) 
			{
				for (int cii = 0; cii < it -> second.size(); ) 
				{
					it -> first -> recibir(it -> second.front());
					it -> second.pop();
				}
				
				it++;
			}

		}

