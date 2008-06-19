#ifndef __PAQUETE_H__
#define __PAQUETE_H__

#include <string>

using namespace std;

class Paquete
{
	private:
		double m_dIDPagina;
		int m_iIDPaquete;
		int m_iTotalPaquetes;
		IP m_ipDestino;
		IP m_ipOrigen;

	public:
		Paquete ();
		Paquete (IP ipDestino, IP ipOrigen, double dIDPagina, int iIDPaquete, int iTotalPaquetes);
		string toString ();
		double getIDPagina ();
		int getIDPaquete ();
		unsigned int getTotalPaquetes ();
		IP getIPDestino ();
		IP getIPOrigen ();
		bool operator < (const Paquete &paquete2);
		bool operator > (const Paquete &paquete2);
		bool operator == (const Paquete &paquete2);
};
#endif
