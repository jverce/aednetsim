#include <map>
#include <string>
#include <sstream>

class Tabla
{
	private:
		map<int, Router*> m_aMapaDestinos;
		map<Router*, int> m_aMapaCarga;
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

		void crearEntradaCarga(Router* interfaz, int iCarga)
		{
			m_aMapaCarga[interfaz] = iCarga;
		}

		int getCarga(Router* interfaz)
		{
			return m_aMapaCarga[interfaz];
		}

		void crearEntradaBandWidth(Router* router, int bandWidth)
		{
			m_aMapaBandWidth[router] = bandWidth;
		}

		int getBW(Router* router)
		{
			return m_aMapaBandWidth[router];
		}

		string toString()
		{
			map<int, Router*> :: iterator it = m_aMapaDestinos.begin();

			while (it != m_aMapaDestinos.end())
			{
				stringstream stringStream; 
				stringStream
					<< "Destino: " << it -> first << '\t' 
					<< "Ruta: " << m_aMapaDestinos -> second -> getId() << endl;

			}

			return stringStream.str();
		}
};
