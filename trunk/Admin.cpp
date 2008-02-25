#include <map>

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
