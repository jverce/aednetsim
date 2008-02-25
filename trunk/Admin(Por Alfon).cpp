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
	    void mostrar_tabla (int g);
   		void getMatrizOriginal();
};

void Admin::getMatrizOriginal()
		{
			LectorArchivoTexto lector;

			m_MatrizActualizada = lector.getMatriz();
		};
void Admin::mostrar_tabla(int g){

    
  
     for (int i = 1 ; i<= 4 ; i++) {
     cout << "Paquetes con Destino Router: " << i << " Enviarlos a: ";
         switch (Tabla_Destino_NextHop[i]){
            case -1:
                 cout << " PC" << endl;
                 break;
            default:
                    if (Tabla_Destino_NextHop[i] == g) {cout << "Router: " << i << endl;  }
                    else {
                    
                   cout << "Router: " << Tabla_Destino_NextHop[i] << endl;   }
                 
              
            
            
            
            
            
            
            
            
         }
              
              
              
              
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

	
	Matriz m;

	m = Lector.getMatriz();
	cout << "Con la siguiente Matriz de adyacencia: " << endl;
	m.printMatriz(Lector.getRouters());
	Admin admin;
	admin.getMatrizOriginal();
	
    
    cout << "Elija un router: " << endl;
    int g;
    cin >> g;
    cout << "La siguiente tabla de enrrutamiento se agregaria el Router: " << endl;
	admin.dijkstra(g);
	admin.mostrar_tabla(g);
	int c;
	cin >> c;

	
	
	return 0;






}


     
     

