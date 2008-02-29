#ifndef __ADMIN_H__
#define __ADMIN_H__

#include <map>
#include <string>

using namespace std;

class Tabla
{
	private:
		map<int, Router*> m_aMapaDestinos;
		map<Router*, int> m_aMapaCarga;
		map<Router*, int> m_aMapaBandWidth;

	public:
	
		void crearEntradaDestinos(int iDestino, Router* nextHop);
		Router* getNextHop(int iDestino);
		void crearEntradaCarga(Router* interfaz, int iCarga);
		int getCarga(Router* interfaz);
		void crearEntradaBandWidth(Router* router, int bandWidth);
		int getBW(Router* router);
		string toString();
};
#endif
