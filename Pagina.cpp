#include <cstdlib>

public class Pagina
{

	private:
		list<Paquete> m_ListaPaquetes;
		int m_iCantPaquetes;
		IP m_IPDestino;
		IP m_IPOrigen;
		float m_fIDPagina;

	public:
		Pagina(int iCantPaquetes, IP ipDestino, IP ipOrigen)
		{
			srand((unsigned) time(0));

			m_fIDPagina = rand();

			m_iCantPaquetes = iCantPaquetes;
			m_IPDestino = ipDestino;
			m_IPOrigen = ipOrigen;

			for (int cii = 0; cii < iCantPaquetes; cii++) {
				Paquete paquete(ipDestino, ipOrigen, m_fIDPagina, (cii + 1));
				m_ListaPaquetes.push_back(paquete);
			}
		}

		Pagina(list<Paquete> listaPaquetes)
		{
			m_ListaPaquetes = listaPaquetes;
			m_iCantPaquetes = listaPaquetes.size();

			list<Paquete>::iterator iiterator = listaPaquetes.begin();
			m_fIDPagina = (*iiterator).getIDPagina();
			m_IPDestino = (*iiterator).getIPDestino();
			m_IPOrigen = (*iiterator).getIPOrigen();
		}

		int getCantPaquetes()
		{
			return m_iCantPaquetes;
		}

		IP getIPDestino()
		{
			return m_IPDestino;
		}

		Paquete getPaquete(int ii)
		{
			list<Paquete>::iterator it = m_ListaPaquetes.begin();

			for (int cii = 0; cii < (ii - 1); cii++)
				it++;

			return (*it);
		}
};

