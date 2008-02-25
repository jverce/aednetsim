#include <map>
#include "Router.cpp"
#include "Matriz.cpp"

#define INF 999
#define MAXN 100  

class Admin
{
	private:
		Matriz m_MatrizOriginal;
		Matriz m_MatrizActualizada;
		map<int, Router*> m_aRefRouters;
		map<Router*, int> m_aDestRouters;
       
        
		void getMatrizOriginal()
		{
			LectorArchivoTexto lector;

			m_MatrizOriginal = lector.getMatriz();
		}

		Router* getRouterPorDestino(int iDestino)
		{
			return m_aRefRouters[iDestino];
		}

		int getDestinoPorRouter(Router* router)
		{
			return m_aDestRouters[router];
		}
		
		void actualizarMatriz()
		{
		}

		void dijkstra(int iOrigen)
		{
		}
};

void Admin::dijkstra (int iOrigen){
     int Costo[MAXN];          /* D   distancias minima desde s al nodo i */
     int NextHop[MAXN];      /* ruta hacia el nodo i desde s */
     int permanente[MAXN]; /
     LectorArchivoTexto lector;
     int n_Routers = lector.getRouters();     
     
     priority_queue< pair<int,int> > Cola;
     pair <int,int> nodo;
     
     int Vi, Vj;     
                   
         for (int i=1; i<= n_Routers; i++){
             costo[i] = INF,
             NextHop[i] = -1,
             permanente[i] = false;
         }
         Costo[s] = 0;
         Cola.push( pair <int,int> (Costo[iOrigen], iOrigen) );
 
     while( !pq.empty() )
     {
            nodo = Cola.top();  Cola.pop();
            Vi = nodo.second;
            if ( !permanente[Vi] ) {
               permanente[Vi] = true;
               for (Vj = 1; Vj <= n; Vj++){
                   if ( !permanente[Vj] && m_MatrizActualizada.getElemento(Vi , Vj)] > 0 && D[Vi] + m_MatrizActualizada.getElemento(Vi , Vj) > D[Vj] ){
                      D[Vj] = D[Vi] + m_MatrizActualizada.getElemento(Vi ; Vj);
                      NextHop[Vj] = Vi,;
                      Cola.push( pair <int,int> (-D[Vj], Vj) );
					}
                }
            }
     }
}

     for ( int cci = 1 ; cci <= n_Routers; cci++){
         m_aRefRouters[cci] = getRouterPorDestino(NextHop[cii]);
     
     
     }


     
     
};
