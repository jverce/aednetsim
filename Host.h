#ifndef __HOST_H__
#define __HOST_H__

class Host
{

	private:
	
		//Variables
		IP m_IP;
		int m_iRandomNumber;
		ofstream m_ArchivoSalida;
		Router* m_Gateway;
		Admin* m_Admin;
		
		//Metodos		
		IP generarDestino();
		Pagina generarPagina();
		int calcularRandom(int iLim);

	public:
	
		Host(int i1Oct, int i2Oct, Admin* admin);
		void setIP(int i1Oct, int i2Oct);
		IP getIP();
		void enviar();
		void recibir(Pagina pagina);
};
#endif
