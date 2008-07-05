#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "Librerias.h"

using namespace std;


bool Router :: isVecino (Router* router)
{
	map< Router*, queue<Paquete*> > :: iterator it = m_ColasVecinos.begin();
	while ( it != m_ColasVecinos.end() )
	{
		if ( (it->first) == router)
		{
			return true;
		}

		it++;
	}
			
	return false;
}

bool Router :: isMismoRouter (Router* router)
{
	return router == this;
}

void Router :: vaciarBufferInt ()
{
	m_BufferIntermedio.sort();
	while (!m_BufferIntermedio.empty())
	{
		meterEnLista(m_BufferIntermedio.get());
	}
}

void Router :: vaciarBufferIntLocal ()
{
	while (!m_BufferIntermedioLocal.empty())
	{
		cargarEnColasLocales(m_BufferIntermedioLocal.get());
	}
}

void Router :: meterEnLista (Paquete* paquete)
{
	m_ColasVecinos[elegirInterfaz(paquete)].push(paquete);
}

Router* Router :: elegirInterfaz (Paquete* paquete)
{
	return elegirInterfaz(paquete->getIPDestino().getPrimerOcteto());
}

Router* Router :: elegirInterfaz (int iRouterId)
{
	Router* router_1 = m_TablaEnrutamiento->getNextHop(iRouterId);
	Router* router_2 = m_Admin->getRouterPorDestino(iRouterId);

	if (isMismoRouter(router_1))
	{
		return router_2;
	}
	else
	{
		return elegirInterfaz(router_1->getId());
	}
}

Paquete* Router :: getAt (list<Paquete*> lista, int iIndex)
{
	list<Paquete*> :: iterator it = lista.begin();
	for (int cii = 0; cii < iIndex; cii++)
	{
		it++;
	}

	return (*it);
}

string Router :: toString ()
{
	stringstream strStream;

	strStream << "Router numero " << m_i1Oct;

	return strStream.str();
}

string Router :: toString (int iNum)
{
	stringstream strStream;

	strStream << iNum;

	return strStream.str();
}

Router :: Router (int i1Oct, Admin* admin)
{
	m_i1Oct = i1Oct;
	m_Admin = admin;
	m_iCantHosts = 0;
	m_TablaEnrutamiento = NULL;

	string szAuxFileName = "Router_" + toString(i1Oct) + ".log";
	char* szFileName = new char[szAuxFileName.size() + 1];
	strcpy(szFileName, szAuxFileName.c_str());
			
	m_ArchivoSalida.open(szFileName);
}

int Router :: getId ()
{
	return m_i1Oct;
}

void Router :: setTabla (Tabla* tabla)
{
	delete m_TablaEnrutamiento;

	m_TablaEnrutamiento = tabla;

	m_ArchivoSalida << "La tabla de enrutamiento ha cambiado." << endl;
	m_ArchivoSalida << "Nueva tabla de enrutamiento: " << endl;
	m_ArchivoSalida << m_TablaEnrutamiento->toString() << endl;
}

list<Host*> Router :: getListaHosts ()
{
	return m_ListaHosts;
}

int Router :: getCarga (int iDestino)
{
	return m_ColasVecinos[elegirInterfaz(iDestino)].size();
}

void Router :: agregarHost (Host* host)
{
	m_ListaHosts.push_back(host);
	m_iCantHosts++;
			
	m_aRefHosts[host->getIP().getSegundoOcteto()] = host;
			
	queue<Paquete*> cola;
	m_ColasLocales[host] = cola;
}

void Router :: agregarVecino (Router* vecino)
{
	queue<Paquete*> cola;

	m_ColasVecinos[vecino] = cola;	
}

int Router :: getCarga (Router* interfaz)
{
	return getCarga(interfaz->getId());
}

void Router :: recibir (Pagina pagina)
{
	m_ArchivoSalida << "Entra_ PAGINA. ID = " << pagina.getID() << endl;
			
	for (unsigned int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
	{
		recibir(pagina.getPaquete(cii));
	}
	
	m_ArchivoSalida << endl;
}

void Router :: recibir (Paquete* paquete)
{
	m_ArchivoSalida << "Entra_ ";
	m_ArchivoSalida << paquete->toString() << endl;

	if (paquete->getIPDestino().getPrimerOcteto() != m_i1Oct)
	{
		m_BufferIntermedio.insert(paquete);
	}
	else
	{
		m_BufferIntermedioLocal.insert(paquete);
	}
}

void Router :: cargarEnColasLocales (Paquete* paquete)
{
	m_ColasLocales[m_aRefHosts[paquete->getIPDestino().getSegundoOcteto()]].push(paquete);
}

bool Router :: isPaginaLista (Paquete* paquete, queue<Paquete*> cola)
{
	double dIdPagina = paquete->getIDPagina();
	unsigned int iCounter = 0;
	
	while (!cola.empty())
	{
		if (cola.front()->getIDPagina() == dIdPagina)
		{
			iCounter++;
		}
		
		cola.pop();
	}
	
	return iCounter == paquete->getTotalPaquetes();
}

int Router :: getCantPaginasListas (queue<Paquete*>* cola)
{
	list<double> listaIdPaginas;
	
	queue<Paquete*> auxCola = *cola;
	while (!auxCola.empty())
	{
		if (isPaginaLista(auxCola.front(), auxCola))
		{
			listaIdPaginas.push_back(auxCola.front()->getIDPagina());
		}
		
		auxCola.pop();
	}
	
	listaIdPaginas.sort();
	listaIdPaginas.unique();
	
	return listaIdPaginas.size();
}

Pagina Router :: getPaginaVieja(queue<Paquete*>* cola)
{
	list<Paquete*> listaPaquetes;
	list<Paquete*> auxListaCola;
	queue<Paquete*> auxCola = *cola;
	double dIdPagina;
		
	while (!cola->empty())
	{
		auxListaCola.push_back(cola->front());
		cola->pop();
	}
	
	list<Paquete*> :: iterator it = auxListaCola.begin();
	while (it != auxListaCola.end())
	{
		if (isPaginaLista(*it, auxCola))
		{
			dIdPagina = (*it)->getIDPagina();
			break;
		}
		
		it++;
	}
	
	it = auxListaCola.begin();
	while (it != auxListaCola.end())
	{
		if ((*it)->getIDPagina() == dIdPagina)
		{
			listaPaquetes.push_back(*it);			
		}
		else
		{
			cola->push(*it);
		}
		
		it++;
	}
	
	listaPaquetes.sort();
	Pagina pagina(listaPaquetes);
	
	return pagina;
}	

void Router :: enviarLocal ()
{
	for (int cii = 0; cii < m_iCantHosts; cii++)
	{
		queue<Paquete*>* cola = &m_ColasLocales[m_aRefHosts[cii]];
				
		for (int cij = 0; cij < getCantPaginasListas(cola); cij++)
		{
			Pagina pagina = getPaginaVieja(cola);
			m_aRefHosts[cii]->recibir(pagina);

			m_ArchivoSalida << "Sale_ PAGINA" << endl;
			m_ArchivoSalida << pagina.toString() << endl;
		}
	}
	
	vaciarBufferIntLocal();
}
					
void Router :: enviar ()
{
	enviarLocal();

	map< Router*, queue<Paquete*> > :: iterator it = m_ColasVecinos.begin();
	while (it != m_ColasVecinos.end())
	{
		Router* routerDestino = it->first;

		for (int cij = 0; 
				(cij < m_TablaEnrutamiento->getBW(routerDestino)) &&
				!(it->second.empty()); 
				it->second.pop(), cij++)
		{
			routerDestino->recibir(it->second.front());
			m_ArchivoSalida << "Sale_ " + it->second.front()->toString() << endl;
		}

		it++;
	}
	
	vaciarBufferInt();
}

