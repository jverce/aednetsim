#include <cstdlib>

class Pagina
{

	private:
		list<Paquete> m_ListaPaquetes;
		int m_iCantPaquetes;
		IP m_IPDestino;
		IP m_IPOrigen;
		double m_dIDPagina;

	public:
		Pagina(int iCantPaquetes, IP ipDestino, IP ipOrigen)
		{
			srand((unsigned) time(0));

			m_dIDPagina = rand();

			m_iCantPaquetes = iCantPaquetes;
			m_IPDestino = ipDestino;
			m_IPOrigen = ipOrigen;

			for (int cii = 0; cii < iCantPaquetes; cii++) 
			{
				Paquete paquete(ipDestino, ipOrigen, m_dIDPagina, (cii + 1));
				m_ListaPaquetes.push_back(paquete);
			}
		}

		Pagina(list<Paquete> listaPaquetes)
		{
			m_ListaPaquetes = listaPaquetes;
			m_iCantPaquetes = listaPaquetes.size();

			list<Paquete> :: iterator it = listaPaquetes.begin();
			m_dIDPagina = it -> getIDPagina();
			m_IPDestino = it -> getIPDestino();
			m_IPOrigen = it ->getIPOrigen();
		}

		int getCantPaquetes()
		{
			return m_iCantPaquetes;
		}

		IP getIPDestino()
		{
			return m_IPDestino;
		}

		Paquete getPaquete(int iPos)
		{
			list<Paquete> :: iterator it = m_ListaPaquetes.begin();

			for (int cii = 0; cii < iPos; cii++)
			{
				it++;
			}

			return (*it);
		}
};

