#include <string>
#include <sstream>

public class Paquete
{
	private:
		double m_dIDPagina;
		int m_iIDPaquete;
		IP m_ipDestino;
		IP m_ipOrigen;

	public:
		Paquete(IP ipDestino, IP ipOrigen, double dIDPagina, int iIDPaquete)
		{
			m_ipDestino = ipDestino;
			m_ipOrigen = ipOrigen;

			m_iIDPaquete = iIDPaquete;
			m_dIDPagina = dIDPagina;
		}

		string toString()
		{
			stringstream stringStream;

			stringStream << "Paquete, ID = " << m_iIDPaquete << ", Pagina.ID = " << m_dIDPagina;
			string szAuxString = stringStream.str();

			return szAuxString;
		}

		double getIDPagina()
		{
			return m_dIDPagina;
		}

		int getIDPaquete()
		{
			return m_iIDPaquete;
		}

		IP getIPDestino()
		{
			return m_ipDestino;
		}

		IP getIPOrigen()
		{
			return m_ipOrigen;
		}

		bool operator < (const Paquete &paquete2)
		{
			return m_iIDPaquete < paquete2.m_iIDPaquete;
		}

		bool operator > (const Paquete &paquete2)
		{
			return m_iIDPaquete > paquete2.m_iIDPaquete;
		}

		bool operator == (const Paquete &paquete2)
		{
			 return m_iIDPaquete == paquete2.m_iIDPaquete;
		}
};
