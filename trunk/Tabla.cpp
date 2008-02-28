#include "Tabla.h"
	
		void Tabla::crearEntradaDestinos(int iDestino, Router* nextHop)
		{
			m_aMapaDestinos[iDestino] = nextHop;
		}

		Router* Tabla::getNextHop(int iDestino) 
		{
			return m_aMapaDestinos[iDestino];
		}

		void Tabla::crearEntradaCarga(Router* interfaz, int iCarga)
		{
			m_aMapaCarga[interfaz] = iCarga;
		}

		int Tabla::getCarga(Router* interfaz)
		{
			return m_aMapaCarga[interfaz];
		}

		void Tabla::crearEntradaBandWidth(Router* router, int bandWidth)
		{
			m_aMapaBandWidth[router] = bandWidth;
		}

		int Tabla::getBW(Router* router)
		{
			return m_aMapaBandWidth[router];
		}

		string Tabla::toString()
		{
			map<int, Router*> :: iterator it = m_aMapaDestinos.begin();

			while (it != m_aMapaDestinos.end())
			{
				stringstream stringStream; 
				stringStream
					<< "Destino: " << it -> first << '\t' 
					<< "Ruta: " << m_aMapaDestinos -> second -> getId() << endl;

			}

			return stringStream.str();
		}

