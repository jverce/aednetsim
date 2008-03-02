#ifndef __PAGINA_H__
#define __PAGINA_H__

#include <list>
#include <string>

using namespace std;

class Pagina
{

	private:
	
		list<Paquete*> m_ListaPaquetes;
		int m_iCantPaquetes;
		IP m_IPDestino;
		IP m_IPOrigen;
		double m_dIDPagina;

	public:
		
		Pagina();
		Pagina(int iCantPaquetes, IP ipDestino, IP ipOrigen, unsigned int iSeed);
		Pagina(list<Paquete> listaPaquetes);
		int getCantPaquetes();
		IP getIPDestino();
		Paquete getPaquete(int iPos);
		string toString();
};
#endif
