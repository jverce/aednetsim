#ifndef __TABLA_H__
#define __TABLA_H__

#include <map>
#include <string>

class Paquete;

using namespace std;

class Tabla
{
	private:
		map<int, Router*> m_aMapaDestinos;
		map<Router*, int> m_aMapaCarga;
		map<Router*, int> m_aMapaBandWidth;

	public:
		Tabla ();
		void crearEntradaDestinos (int iDestino, Router* nextHop);
		Router* getNextHop (Paquete* paquete);
		Router* getNextHop (int iDestino);
		void crearEntradaCarga (Router* interfaz, int iCarga);
		int getCarga (Router* interfaz);
		void crearEntradaBandWidth (Router* router, int iBandWidth);
		int getBW (Router* router);
		string toString ();
};
#endif
