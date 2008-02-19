#include <map>

class Tabla
{
	private:
		map<int, Router*> m_aMapaDestinos;
		map<Router*, int> m_aMapaBandWidth;

	public:
		void crearEntradaDestinos(int iDestino, Router* nextHop)
		{
			m_aMapaDestinos[iDestino] = nextHop;
		}

		Router* getNextHop(int iDestino) 
		{
			return m_aMapaDestinos[iDestino];
		}

		void crearEntradaBandWidth(Router* router, int bandWidth)
		{
			m_aMapaBandWidth[router] = bandWidth;
		}

		int getBW(Router* router)
		{
			return m_aMapaBandWidth[router];
		}
};
