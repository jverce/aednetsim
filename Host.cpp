#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <list>

#include "Librerias.h"

using namespace std;

IP Host :: generarDestino ()
{
	m_iRandomNumber = calcularRandom(m_Admin -> getCantRouters());

	IP ip(
	m_iRandomNumber, 
	calcularRandom(
		m_Admin -> getRouterPorDestino(m_iRandomNumber) -> getListaHosts().size()));
	
	return ip;
}

Pagina Host :: generarPagina ()
{		
	Pagina pagina(calcularRandom(NUM_MAX_PAQ_POR_PAG), generarDestino(), m_IP, rand());

	return pagina;
}	
	
int Host :: calcularRandom (int iLim)
{	
	if (iLim <= 1)
	{
		return 0;
	}

	return (rand() % (iLim-1));
}	


Host :: Host (int i1Oct, int i2Oct, Admin* admin, unsigned int iSeed)
{
	setIP(i1Oct, i2Oct);
	m_Admin = admin;
	
	string szAuxFileName = "Host_" + m_IP.toString() + ".log";
	char* szFileName = new char[szAuxFileName.size() + 1];
	strcpy(szFileName, szAuxFileName.c_str());

	m_ArchivoSalida.open(szFileName);

	srand(iSeed);
	
	m_Gateway = m_Admin -> getRouterPorDestino(i1Oct);
}

void Host :: setIP (int i1Oct, int i2Oct)
{
	m_IP.setPrimerOcteto(i1Oct);
	m_IP.setSegundoOcteto(i2Oct);
}

IP Host :: getIP ()
{
	return m_IP;
}	

void Host :: enviar ()
{
	Pagina pagina;
	pagina = generarPagina();
	
	m_Gateway -> recibir(pagina);

	for (unsigned int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
	{
		m_ArchivoSalida << "Sale_ " + pagina.getPaquete(cii) -> toString() << endl;
	}
	
	m_ArchivoSalida << endl;
}
	
void Host :: recibir (Pagina pagina)
{
	m_ArchivoSalida << "Entra_ PAGINA " << endl;
	m_ArchivoSalida << pagina.toString() << endl << endl;
}

