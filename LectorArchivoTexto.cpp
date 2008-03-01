#include "Librerias.h"

using namespace std;

LectorArchivoTexto::LectorArchivoTexto() 
{	
	Datos = fopen( NOMBRE_ARCHIVO, "r+t" );
	
	if( Datos == NULL) {
		printf( "No es posible abrir el archivo Datos.txt\n" );
	}

	Routers();
	fclose(Datos);
}

int LectorArchivoTexto::getAnchoBanda(int Router1, int Router2) {
    ifstream datos(NOMBRE_ARCHIVO);
	if ( Router1 > n_Routers || Router2 > n_Routers) { 
		return 0;
	} else {
		char t_AnchoBanda[50];
		
		for (int i = 0 ; i < Router1 ; i ++) {
			while (datos.get() != OTRA_FILA );
		} 
				
		for (int i = 0 ; i < Router2 ; i ++) {
			while (datos.get() != OTRA_COLUMNA);
		} 
			
		datos.get(t_AnchoBanda, 50, OTRA_COLUMNA);
		datos.clear();
		datos.close();

		return (atoi(t_AnchoBanda));     
	}                       
};

int LectorArchivoTexto::getNumeroPcs(int Router) {
	char t_NumeroPcs[100];
	ifstream datos(NOMBRE_ARCHIVO);
	
	for (int i = 0; i < Router ; i ++) {
		while (datos.get() != OTRA_FILA);
	} 		
	
	while(datos.get() != '*');
	datos.get(t_NumeroPcs, 100, '\n');
	datos.clear();
	datos.close();
		
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
	datos.close();
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

MatrizInt LectorArchivoTexto::getMatriz(){
	MatrizInt matriz;

	for (int cii = 0; cii < n_Routers; cii++) {
		for (int cij = 0 ; cij < n_Routers; cij++) {
			matriz.setElemento(cii, cij, getAnchoBanda(cii, cij));
		}	
	}

	return matriz;

};

