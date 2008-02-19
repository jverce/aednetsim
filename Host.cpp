#include "Classes.h"

public class Host
{

	private:
		IP m_IP;
		int m_iRandomNumber;
	
		ofstream m_ArchivoSalida;

		Router* m_Gateway;

		IP generarDestino()
		{
			m_iRandomNumber = calcularRandom(admin.getCantRouters());

			IP ip(m_iRandomNumber, calcularRandom(admin.getCantHosts(m_iRandomNumber)));
	
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
		Host(int i1Oct, int i2Oct)
		{
			setIP(i1Oct, i2Oct);
	
			string szAuxString = "Host_" + m_IP.toString() + ".log";
			m_ArchivoSalida.open(szAuxString);
		
			srand((unsigned) time(0));
	
			m_Gateway = admin.getGateway(this, i1Oct);
		}

		void setIP(int i1Oct, int i2Oct)
		{
			getIP().setPrimerOcteto(i1Oct);
			getIP().setSegundoOcteto(i2Oct);
		}

		IP getIP()
		{
			return m_IP;
		}	

		void enviar()
		{
			Pagina pagina;
			pagina = generarPagina();
	
			m_Gateway->(recibir(pagina));

			for (int cii = 0; cii < pagina.getCantPaquetes(); cii++)
				m_ArchivoSalida << "Sale_ " + pagina.getPaquete(cii).toString() << endl;		
		}
	
		void recibir(Pagina pagina)
		{
			for (int cii = 0; cii < pagina.getCantPaquetes(); cii++)
				m_ArchivoSalida << "Entra_ " + pagina.getPaquete(cii).toString() << endl;			
		}
};
