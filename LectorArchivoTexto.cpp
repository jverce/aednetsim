#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Matriz.cpp"

#define NOMBRE_ARCHIVO "Datos.txt"
#define OTRA_COLUMNA ' '
#define OTRA_FILA '\n'
#define MAX_N_ROUTER 256

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
		int* getRoutersConectados(int Router);
		void Routers();
		int getRouters();
		Matriz getMatriz();
};

LectorArchivoTexto::LectorArchivoTexto() 
{	
	Datos = fopen( NOMBRE_ARCHIVO, "r+t" );
	
	if( Datos == NULL) {
		printf( "No es posible abrir el archivo Datos.txt\n" );
	}

	Routers();
}

int LectorArchivoTexto::getAnchoBanda(int Router1, int Router2) {
    ifstream datos(NOMBRE_ARCHIVO);
	if ( Router1 > n_Routers || Router2 > n_Routers) { 
		
		return 0;
	} else {
		char t_AnchoBanda[50];
		
		for (int i = 1 ; i <= (Router1 - 1) ; i ++) {
			while (datos.get() != OTRA_FILA );
		} 
				
		for (int i = 1 ; i <= (Router2 - 1) ; i ++) {
			while (datos.get() != OTRA_COLUMNA);
		} 
			
		datos.get(t_AnchoBanda, 50, OTRA_COLUMNA);
		datos.clear();
			
		return (atoi(t_AnchoBanda));     
	}                       
};

int LectorArchivoTexto::getNumeroPcs(int Router) {
	char t_NumeroPcs[100];
	ifstream datos(NOMBRE_ARCHIVO);
	
	for (int i = 1 ; i <= (Router - 1) ; i ++) {
		while (datos.get() != OTRA_FILA);
	} 		
	
	while(datos.get() != '*');
	datos.get(t_NumeroPcs, 100, '\n');
	datos.clear();
		
	return (atoi (t_NumeroPcs));
};

void LectorArchivoTexto::Routers() {
	ifstream datos (NOMBRE_ARCHIVO);

	n_Routers = 0;
	while(!datos.eof()) {
		if (datos.get() == OTRA_FILA ){
			n_Routers++;
		}
	}

	datos.clear();
};

int* LectorArchivoTexto::getRoutersConectados(int Router) {

	int c = 0;
	
	for (int i=0; i < n_Routers ; i++) {
		if (getAnchoBanda(Router, i+1) != 0) {
			ListaRouters[c] = i+1;
			c++;	
		}
	}


	return ListaRouters;
};

int LectorArchivoTexto::getRouters() {
	return n_Routers;
};


Matriz LectorArchivoTexto::getMatriz(){
	Matriz m;
		for (int cii = 1; cii <= MAX_N_ROUTER; cii++){
			for (int cij = 1 ; cij <= MAX_N_ROUTER; cij++){
				m.setElemento(cii-1, cij-1 , getAnchoBanda(cii,cij));
			}
		
		}


	return m;

};


int main (){
	LectorArchivoTexto Lector;
	cout << Lector.getRouters()<< endl;
	
	Matriz m;
	m = Lector.getMatriz();
	m.printMatriz(Lector.getRouters());
	
	return 0;






}
