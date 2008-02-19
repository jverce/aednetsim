#include <map>

class Tabla
{
	private:
		map<int, Router*> m_aMapaDestinos;

	public:
		void crearEntrada (int iDestino, Router* nextHop)
		{
			m_aMapaDestinos[iDestino] = nextHop;
		}

		Router* getNextHop (int iDestino) 
		{
			return m_aMapaDestinos[iDestino];
		}
}
