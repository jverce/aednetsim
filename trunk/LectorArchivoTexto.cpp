#include <fstream>
#include <iostream>
#include <stdio.h>

#define NOMBRE_ARCHIVO "Datos.txt"
#define OTRA_COLUMNA ' '
#define OTRA_FILA '\n'

using namespace std;

class LectorArchivoTexto { 

	private:
		int n_Routers;
		int n_Pc;
		int AnchoBanda;
		FILE *Datos;
		char ListaRouters[128];

	
	public:
		Lector();
		int getAnchoBanda(int Router1 , int Router2);
		int getNumeroPcs(int Router);
		char* getRoutersConectados(int Router);
		void Routers();
		int getRouters();
};

LectorArchivoTexto::LectorArchivoTexto() 
{	
	Datos = fopen( NOMBRE_ARCHIVO, "r+t" );
	
	if( Datos == NULL) {
		printf( "No es posible abrir el archivo Datos.txt\n" );
	}

	getRouters();
}

int LectorArchivoTexto::getAnchoBanda(int Router1, int Router2) {
    ifstream datos(NOMBRE_ARCHIVO);
	if ( Router1 >= n_Routers || Router2 >= n_Routers) { 
		cout << "Numeros de Routers invalidos" << endl;	
		
		return -1;
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

	n_Routers = 1;
	while(!datos.eof()) {
		if (datos.get() == OTRA_FILA ){
			n_Routers++;
		}
	}

	datos.clear();
};

char* LectorArchivoTexto::getRoutersConectados(int Router) {
	ifstream datos (NOMBRE_ARCHIVO);
	int c = 1;
	
	for (int i=1; i <= n_Routers ; i++) {
		if (getAnchoBanda(Router, i) != 0) {
			ListaRouters[c] = 'i';
			c++;	
		}
	}

	datos.clear();

	return ListaRouters;
};

int LectorArchivoTexto::getRouters() {
	return n_Routers;
};
