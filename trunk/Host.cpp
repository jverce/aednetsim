#include "Librerias.h"

using namespace std;

		IP Host::generarDestino()
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

		Pagina Host::generarPagina()
		{		
			Pagina pagina(calcularRandom(100), generarDestino(), m_IP);
		
			return pagina;
		}	
	
		int Host::calcularRandom(int iLim)
		{	
			return ((int) (rand() * iLim)) + 1;
		}	


		Host::Host(int i1Oct, int i2Oct, Admin* admin)
		{
			setIP(i1Oct, i2Oct);
			m_Admin = admin;
	
			string szAuxString = "Host_" + m_IP.toString() + ".log";
			m_ArchivoSalida.open(szAuxString);
		
			srand((unsigned) time(0));
	
			m_Gateway = m_Admin -> getRouterPorDestino(i1Oct);
		}

		void Host::setIP(int i1Oct, int i2Oct)
		{
			m_IP.setPrimerOcteto(i1Oct);
			m_IP.setSegundoOcteto(i2Oct);
		}

		IP Host::getIP()
		{
			return m_IP;
		}	

		void Host::enviar()
		{
			Pagina pagina;
			pagina = generarPagina();
	
			m_Gateway -> recibir(pagina);

			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_ArchivoSalida << "Sale_ " + pagina.getPaquete(cii).toString() << endl;		
			}
		}
	
		void Host::recibir(Pagina pagina)
		{
			for (int cii = 1; cii <= pagina.getCantPaquetes(); cii++)
			{
				m_ArchivoSalida << "Entra_ " + pagina.getPaquete(cii).toString() << endl;			
			}
		}

