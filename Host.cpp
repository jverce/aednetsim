#include <list>
#include <cstdlib>

#include "Classes.h"

class Host
{

	private:
		IP m_IP;
		int m_iRandomNumber;
	
		ofstream m_ArchivoSalida;

		Router* m_Gateway;
		Admin* m_Admin;

		IP generarDestino()
		{
			m_iRandomNumber = calcularRandom(m_Admin -> getCantRouters());

			IP ip(
					m_iRandomNumber, 
					calcularRandom(
						m_Admin -> 
						getRouterPorDestino(m_iRandomNumber) ->
						getListaHosts.
						size()));
	
			return ip;
		}

		Pagina generarPagina()
		{		
			Pagina pagina(calcularRandom(100), generarDestino(), m_IP);
		
			return pagina;
		}	
	
		int calcularRandom(int iLim)
		{	
			return ((int) (rand() * iLim)) + 1;
		}	

	public:
		Host(int i1Oct, int i2Oct, Admin* admin)
		{
			setIP(i1Oct, i2Oct);
			m_Admin = admin;
	
			string szAuxString = "Host_" + m_IP.toString() + ".log";
			m_ArchivoSalida.open(szAuxString);
		
			srand((unsigned) time(0));
	
			m_Gateway = m_Admin -> getRouterPorDestino(i1Oct);
		}

		void setIP(int i1Oct, int i2Oct)
		{
			m_IP.setPrimerOcteto(i1Oct);
			m_IP.setSegundoOcteto(i2Oct);
		}

		IP getIP()
		{
			return m_IP;
		}	

		void enviar()
		{
			Pagina pagina;
			pagina = generarPagina();
	
			m_Gateway -> recibir(pagina);

			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_ArchivoSalida << "Sale_ " + pagina.getPaquete(cii).toString() << endl;		
			}
		}
	
		void recibir(Pagina pagina)
		{
			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_ArchivoSalida << "Entra_ " + pagina.getPaquete(cii).toString() << endl;			
			}
		}
};
