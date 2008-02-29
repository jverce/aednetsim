#ifndef __LECTORARCHIVOTEXTO_H__
#define __LECTORARCHIVOTEXTO_H__

#include <list>

using namespace std;

class LectorArchivoTexto { 

	private:
		int n_Routers;
		int n_Pc;
		int AnchoBanda;
		FILE *Datos;
		int ListaRouters[128];
		
	
	public:
		LectorArchivoTexto();
		int getAnchoBanda(int Router1 , int Router2);
		int getNumeroPcs(int Router);
		list<int> getRoutersConectados(int Router);
		void Routers();
		int getCantRouters();
		Matriz<int> getMatriz();
};
#endif
