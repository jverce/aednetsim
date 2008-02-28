#include <fstream>
#include <string>
#include <list>
#include <map>
#include <queue>

#include "Classes.h"

using namespace std;

public class Router
{
	private:
		int m_i1Oct;
		int m_iCantHosts;

		ofstream m_ArchivoSalida;

		list<Host*> m_ListaHosts;
		map<Router*, queue<Paquete>> m_ColasVecinos;
		Buffer<Paquete> m_Buffer;
		list<Paquete> m_ListaPaquetes;
		Tabla m_TablaEnrutamiento;

		bool isVecino (Router* router)
		{
			map<Router*, queue<Paquete>> :: iterator it = m_ColasVecinos.begin();
			
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

		void vaciarBuffer()
		{
			m_Buffer.sort();
			while (!m_Buffer.empty())
			{
				meterEnLista(m_Buffer.get());
			}
		}

		void meterEnLista(Pagina pagina)
		{
			for (int cii = 0; cii < pagina.getCantPaquetes(); cii++) {
				m_ListaPaquetes.push_back(pagina.getPaquete(cii));
				m_ArchivoSalida << "Entra_ " + pagina.getPaquete(cii).toString() << endl;
			}		
		}

		void meterEnLista(Paquete paquete)
		{
			m_ListaPaquetes.push_back(paquete);
			m_ArchivoSalida << "Entra_ " + paquete.toString() << endl;
		}

		Router* elegirInterfaz(Paquete paquete)
		{
			Router* router = m_TablaEnrutamiento.getNextHop(paquete.getIPDestino().getPrimerOct());

			if (isVecino(router))
				return router;
			else
				return m_TablaEnrutamiento.getNextHop(router -> getId());
		}

		Paquete getAt(list<Paquete> lista, int iIndex)
		{
			list<Paquete> :: iterator it = lista.begin();

			for (int cii = 0; cii < iIndex; cii++)
				it++;

			return (*it);
		}

	public:
		Router(int i1Oct)
		{
			m_i1Oct = i1Oct;
			m_iCantHosts = 0;

			string szFileName = "Router_" + i1Oct + ".log";
			m_ArchivoSalida.open(szFileName);
		}

		int getId()
		{
			return m_i1Oct;
		}

		void setTabla(Tabla tabla)
		{
			m_TablaEnrutamiento = tabla;
			m_ArchivoSalida << "La tabla de enrutamiento ha cambiado." << endl;
			m_ArchivoSalida << "Nueva tabla de enrutamiento: " << endl;
			m_ArchivoSalida << m_Tabla.toString() << endl;
		}

		list<Host*> getListaHosts()
		{
			return m_ListaHosts;
		}

		int getCarga(int iDestino)
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

		void agregarHost(Host* host)
		{
			m_ListaHosts.push_back(host);
			m_iCantHosts++;
		}

		void agregarVecino(Router* vecino)
		{
			queue<Paquete> cola;

			m_ColasVecinos[vecino] = cola;	
		}

		int getCarga(Router* interfaz)
		{
			return getCarga(interfaz -> getId());
		}

		void recibir(Pagina pagina)
		{
			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_Buffer.insert(getPaquete(cii));
			}
		}

		void recibir(Paquete paquete)
		{
			m_Buffer.insert(paquete);
		}

		void enviar()
		{
			vaciarBuffer();

			map<Router*, queue<Paquete>> :: iterator it_1 = m_ColasVecinos.begin();

			while (it_1 != m_ColasVecinos.end())
			{
				Router* routerDestino = (*it_1).first;

				list<Paquete> :: iterator it_2 = m_ListaPaquetes.begin();
				for (int cij = 0; 
						(cij < m_TablaEnrutamiento.getBW(routerDestino)) || 
						(it_2 != m_ListaPaquetes.end()); it_2++)
				{
					if (m_TablaEnrutamiento.getNextHop(*it_2) == routerDestino) 
					{
						m_ColasVecinos[routerDestino].push(*it_2);
						m_ListaPaquetes.erase(it_2);

						cij++;
					}
				}

				it_1++;
			}

			map<Router*, queue<Paquete>> :: iterator it = m_ColasVecinos.begin();

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
};

