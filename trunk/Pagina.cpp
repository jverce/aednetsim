#include <iostream>
#include <string>
#include <sstream>

#include "Librerias.h"

using namespace std;


Pagina :: Pagina () {}

Pagina :: Pagina (int iCantPaquetes, IP ipDestino, IP ipOrigen, unsigned int iSeed)
{
	srand(iSeed);

	m_dIDPagina = (double) rand() / (double) RAND_MAX;

	m_iCantPaquetes = iCantPaquetes;
	m_IPDestino = ipDestino;
	m_IPOrigen = ipOrigen;

	for (int cii = 0; cii < iCantPaquetes; cii++) 
	{
		Paquete* paquete = 
			new Paquete(ipDestino, ipOrigen, m_dIDPagina, (cii + 1), m_iCantPaquetes);
		m_ListaPaquetes.push_back(paquete);
	}
}

Pagina :: Pagina (list<Paquete*> listaPaquetes)
{
	m_ListaPaquetes = listaPaquetes;
	m_iCantPaquetes = listaPaquetes.size();

	list<Paquete*> :: iterator it_2 = listaPaquetes.begin();
	m_dIDPagina = (*it_2) -> getIDPagina();
	m_IPDestino = (*it_2) -> getIPDestino();
	m_IPOrigen = (*it_2) ->getIPOrigen();
}

int Pagina :: getCantPaquetes ()
{
	return m_iCantPaquetes;
}

IP Pagina :: getIPDestino ()
{
	return m_IPDestino;
}

Paquete* Pagina :: getPaquete (int iPos)
{
	list<Paquete*> :: iterator it = m_ListaPaquetes.begin();

	for (int cii = 1; cii < iPos; cii++)
	{
		it++;
	}

	return (*it);
}

string Pagina :: toString ()
{
	stringstream strStream;

	for (int cii = 0; cii < m_iCantPaquetes; cii++)
	{
		strStream << getPaquete(cii) -> toString() << endl;
	}

	return strStream.str();
}


