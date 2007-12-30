#include "Classes.h"

public class Paquete
{
private:
	float m_fIDPagina;
	int m_iIDPaquete;
	IP m_ipDestino;
	IP m_ipOrigen;

public:
	Paquete(IP ipDestino, IP ipOrigen, float fIDPagina, int iIDPaquete)
	{
		m_ipDestino = ipDestino;
		m_ipOrigen = ipOrigen;
		
		m_iIDPaquete = iIDPaquete;
		m_fIDPagina = fIDPagina;
	}

	string toString()
	{
		string szAuxString = "Paquete, ID = " + m_iIDPaquete + ", Pagina.ID = " + m_fIDPagina;

		return szAuxString;
	}

	float getIDPagina()
	{
		return m_fIDPagina;
	}

	int getIDPaquete()
	{
		return m_iIDPaquete;
	}

	IP getIPDestino()
	{
		return m_ipDestino;
	}

	bool operator < (const Paquete &paquete2)
	{
		if (m_iIDPaquete < paquete2.m_iIDPaquete)
			return true;
		else
			return false;
	}

	bool operator > (const Paquete &paquete2)
	{
		if (m_iIDPaquete > paquete2.m_iIDPaquete)
			return true;
		else
			return false;
	}

	bool operator == (const Paquete &paquete2)
	{
		if (m_iIDPaquete == paquete2.m_iIDPaquete)
			return true;
		else
			return false;
	}
};