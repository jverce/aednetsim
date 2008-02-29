#ifndef __PAQUETE_H__
#define __PAQUETE_H__

#include <string>

using namespace std;

class Paquete
{
	private:
	
		double m_dIDPagina;
		int m_iIDPaquete;
		IP m_ipDestino;
		IP m_ipOrigen;

	public:
	
		Paquete(IP ipDestino, IP ipOrigen, double dIDPagina, int iIDPaquete);
		string toString();
		double getIDPagina();
		int getIDPaquete();
		IP getIPDestino();
		IP getIPOrigen();
		bool operator < (const Paquete &paquete2);
		bool operator > (const Paquete &paquete2);
		bool operator == (const Paquete &paquete2);
};
#endif
