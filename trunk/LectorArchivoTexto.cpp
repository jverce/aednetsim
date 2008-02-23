#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

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
//		int Matriz_Adyacencia[MAX_N_ROUTER][MAX_N_ROUTER];
		int** Matriz_Adyacencia;

	
	public:
		LectorArchivoTexto();
		int getAnchoBanda(int Router1 , int Router2);
		int getNumeroPcs(int Router);
		int* getRoutersConectados(int Router);
		void Routers();
		int getRouters();
		int** Matriz();
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


int** LectorArchivoTexto::Matriz(){
	
	Matriz_Adyacencia = (int**) malloc(sizeof(int) * MAX_N_ROUTER * 2);
		for (int i = 0; i< MAX_N_ROUTER ; i++){
			for (int j = 0; j < MAX_N_ROUTER ; j++ ){
				**Matriz_Adyacencia = getAnchoBanda(i,j);
				(*Matriz_Adyacencia)++;
			}
		
		}
	return Matriz_Adyacencia;

};


int main (){
	LectorArchivoTexto Lector;
	cout << Lector.getRouters()<< endl;
	cout << Lector.Matriz() << endl;
	return 0;






}
