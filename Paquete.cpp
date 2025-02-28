#include <iostream>
#include <string>
#include <sstream>

#include "Librerias.h"

using namespace std;


Paquete :: Paquete () {}

Paquete :: Paquete (IP ipDestino, IP ipOrigen, double dIDPagina, int iIDPaquete, int iTotalPaquetes)
{
	m_ipDestino = ipDestino;
	m_ipOrigen = ipOrigen;

	m_dIDPagina = dIDPagina;
	m_iIDPaquete = iIDPaquete;
	m_iTotalPaquetes = iTotalPaquetes;
}

string Paquete :: toString ()
{
	stringstream stringStream;

	stringStream << "Paquete, ID = " << m_iIDPaquete << ", Pagina.ID = " << m_dIDPagina;
	stringStream << ". Origen = " << m_ipOrigen.toString() << ", Destino = " << m_ipDestino.toString();
	string szAuxString = stringStream.str();

	return szAuxString;
}

double Paquete :: getIDPagina ()
{
	return m_dIDPagina;
}

unsigned int Paquete :: getTotalPaquetes ()
{
	return m_iTotalPaquetes;
}

int Paquete :: getIDPaquete ()
{
	return m_iIDPaquete;
}

IP Paquete :: getIPDestino ()
{
	return m_ipDestino;
}

IP Paquete :: getIPOrigen ()
{
	return m_ipOrigen;
}

bool Paquete :: operator < (const Paquete &paquete2)
{
	return m_iIDPaquete < paquete2.m_iIDPaquete;
}

bool Paquete :: operator > (const Paquete &paquete2)
{
	return m_iIDPaquete > paquete2.m_iIDPaquete;
}

bool Paquete :: operator == (const Paquete &paquete2)
{
	return m_iIDPaquete == paquete2.m_iIDPaquete;
}
