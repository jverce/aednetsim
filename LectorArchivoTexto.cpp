#include "clases.h"

class LectorArchivoTexto {

private:
	int n_Router;
	int n_Pc;
	int AnchoBanda;
	FILE *Datos;
	
public:
	Lector(); 
	int getAnchoBanda(int Router1 , int Router2);
	int getNumeroPcs(Int Router);
	int getRoutersConectados(int Router);
	
};

Lector::Lector() {
	char nombre[10] = "Datos.txt";
	Datos = fopen( nombre, "r" );
	if( !Datos ){
		printf( "No es posible abrir el archivo Datos.txt\n" );
	};
}

Lector::getAnchoBanda(int Router1, int Router2) {
		for (int i = 1 ; i < Router1 , i ++){
			while (fgetc(fichero) != '\n' ){};
		}; // Puenteo en Router
		for (int i = 1 ; i < Router2 , i ++){
			while (fgetc(fichero) != ' '){};
		}; // Puntero en  Router destino
		
		while (fgetc(fichero) != ' ') {
			
		
		}		//Leer el ancho de banda
	

};

