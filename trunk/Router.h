#ifndef __ADMIN_H__
#define __ADMIN_H__

using namespace std;

class Router
{
	private:
		//Variables
		int m_i1Oct;
		int m_iCantHosts;
		ofstream m_ArchivoSalida;
		list<Host*> m_ListaHosts;
		map<Router*, queue<Paquete>> m_ColasVecinos;
		Buffer<Paquete> m_Buffer;
		list<Paquete> m_ListaPaquetes;
		Tabla m_TablaEnrutamiento;
		
		//Metodos
		bool isVecino (Router* router);
		void vaciarBuffer();
		void meterEnLista(Pagina pagina);
		void meterEnLista(Paquete paquete);
		Router* elegirInterfaz(Paquete paquete);
		Paquete getAt(list<Paquete> lista, int iIndex);

	public:
	
		Router(int i1Oct);
		int getId();
		void setTabla(Tabla tabla);
		list<Host*> getListaHosts();
		int getCarga(int iDestino);
		void agregarHost(Host* host);
		void agregarVecino(Router* vecino);
		int getCarga(Router* interfaz);
		void recibir(Pagina pagina):
		void recibir(Paquete paquete);
		void enviar();
};
#endif
