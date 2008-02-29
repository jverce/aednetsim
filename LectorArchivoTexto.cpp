#include "Librerias.h"

using namespace std;

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

	n_Routers = 1;
	while(!datos.eof()) {
		if (datos.get() == OTRA_FILA ){
			n_Routers++;
		}
	}

	datos.clear();
};

list<int> LectorArchivoTexto::getRoutersConectados(int Router) {

	list<int> aiLista;
	
	for (int i=0; i < n_Routers ; i++) {
		if (getAnchoBanda(Router, i) != 0) {
			aiLista.push_back(i);
		}
	}


	return aiLista;
};

int LectorArchivoTexto::getCantRouters() {
	return n_Routers;
};

Matriz LectorArchivoTexto::getMatriz(){
	Matriz matriz;

	for (int cii = 1; cii <= NUM_MAX_ROUTERS; cii++) {
		for (int cij = 1 ; cij <= NUM_MAX_ROUTERS; cij++) {
			matriz.setElemento(cii - 1, cij - 1, getAnchoBanda(cii,cij));
		}	
	}

	return matriz;

};

