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

		list<Paquete> m_ListaPaquetes;

		Tabla m_TablaEnrutamiento;

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
			return (m_TablaEnrutamiento.getNextHop(paquete))
		}

		Paquete getAt(list<Paquete> lista, int iindex)
		{
			list<Paquete>::iterator it = lista.begin();

			for (int cii = 0; cii < iindex; cii++)
				it++;

			return (*it);
		}

	public:
		Router(int i1Oct)
		{
			m_i1Oct = i1Oct;
			m_iCantHosts = 0;

			Tabla tablaEnrutamiento(i1Oct);
			m_TablaEnrutamiento = tablaEnrutamiento;

			string szFileName = "Router_" + i1Oct + ".log";
			m_ArchivoSalida.open(szFileName);
		}

		void setTabla(Tabla tabla)
		{
			m_TablaEnrutamiento = tabla;
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

		void recibir(Pagina pagina)
		{
			meterEnLista(pagina);
			m_ListaPaquetes.sort();
		}

		void recibir(Paquete paquete)
		{
			meterEnLista(paquete);
			m_ListaPaquetes.sort();
		}

		void enviar()
		{
			map<Router*, queue<Paquete>>::iterator iiterator_1 = m_ColasVecinos.begin();

			for (int cii = 0; cii < m_ColasVecinos.size(); cii++) {
				Router* iRouter = (*iiterator_1).first;

				list<Paquete>::iterator iiterator_2 = m_ListaPaquetes.begin();
				for (int cij = 0; 
						(cij < m_TablaEnrutamiento.getBW(iRouter)) || 
						(iiterator_2 == m_ListaPaquetes.end()); iiterator_2++) {
					if (m_TablaEnrutamiento.getNextHop(*iiterator_2) == iRouter) {
						m_ColasVecinos[iRouter].push(*iiterator_2);
						m_ListaPaquetes.erase(iiterator_2);

						cij++;
					}
				}

				iiterator_1++;
			}

			map<Router*, queue<Paquete>>::iterator iiterator = m_ColasVecinos.begin();

			while (iiterator != m_ColasVecinos.end()) {

				for (int cii = 0; cii < (*iiterator).second.size(); cii++) {
					(*iiterator).first->recibir((*iiterator).second.front());
					(*iiterator).second.pop();
				}

				iiterator++;
			}
		}


};

