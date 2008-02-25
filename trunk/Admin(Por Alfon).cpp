#include <map>
#include "LectorArchivoTexto.cpp"

#include <queue>
#include <cstring>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define INF 999
#define MAXN 100  

using namespace std;

class Admin
{
	private:
		Matriz m_MatrizOriginal;
		Matriz m_MatrizActualizada;
	/*	map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;*/
        map<int , int > Tabla_Destino_NextHop;       
        
	/*	void getMatrizOriginal()
		{
			LectorArchivoTexto lector;

			m_MatrizOriginal = lector.getMatriz();
		};/*

		Router* getRouterPorDestino(int iDestino)
		{
			return m_aRefRouters[iDestino];
		};

		int getDestinoPorRouter(Router* router)
		{
			return m_aDestRouters[router];
		};
		
		void actualizarMatriz()
		{
		};*/
public:
		void dijkstra(int iOrigen);
	    void mostrar_tabla ();
   		void getMatrizOriginal();
};

void Admin::getMatrizOriginal()
		{
			LectorArchivoTexto lector;

			m_MatrizActualizada = lector.getMatriz();
		};
void Admin::mostrar_tabla(){
     cout << Tabla_Destino_NextHop[4]<< endl;
     for (int i = 1 ; i<= 4 ; i++) {
             cout << "Para llegar al destino " << i << " hay que mandar el paquete a: " << Tabla_Destino_NextHop[i] <<endl;
                          
                          
     }
  
  
     };

void Admin::dijkstra (int iOrigen){
     int Costo[MAXN];          /* D   distancias minima desde s al nodo i */
     int NextHop[MAXN];      /* ruta hacia el nodo i desde s */
     int permanente[MAXN]; 
     LectorArchivoTexto lector;
     int n_Routers = lector.getRouters();     
     
     priority_queue< pair<int,int> > Cola;
     pair <int,int> nodo;
     
     int Vi, Vj;     
                   
         for (int i=1; i<= n_Routers; i++){
             Costo[i] = INF,
             NextHop[i] = -1,
             permanente[i] = false;
         }
         Costo[iOrigen] = 0;
         Cola.push( pair <int,int> (Costo[iOrigen], iOrigen) );
 
     while( !Cola.empty() )
     {
            nodo = Cola.top();  Cola.pop();
            Vi = nodo.second;
            if ( !permanente[Vi] ) {
               permanente[Vi] = true;
               for (Vj = 1; Vj <= n_Routers; Vj++){
                   if ( !permanente[Vj] && (m_MatrizActualizada.getElemento(Vi-1 , Vj-1)) > 0 && Costo[Vi] + m_MatrizActualizada.getElemento(Vi-1 , Vj-1) < Costo[Vj] ){
                      Costo[Vj] = Costo[Vi] + m_MatrizActualizada.getElemento(Vi-1 , Vj-1);
                      NextHop[Vj] = Vi;
                      Cola.push( pair <int,int> (-Costo[Vj], Vj) );
					}
                }
            }
     }

      
     for ( int cci = 1 ; cci <= n_Routers ; cci++ ){
         Tabla_Destino_NextHop[cci] = NextHop[cci];
     
     
     }
     
};

     
int main (){
	LectorArchivoTexto Lector;
	cout << Lector.getRouters()<< endl;
	
	Matriz m;

	m = Lector.getMatriz();
	m.printMatriz(Lector.getRouters());
	Admin admin;
	admin.getMatrizOriginal();
	admin.dijkstra(1);
	admin.mostrar_tabla();
	int c;
	cin >> c;

	
	
	return 0;






}


     
     

