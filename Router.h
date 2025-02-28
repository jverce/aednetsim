#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <fstream>
#include <list>
#include <queue>
#include <map>
#include <string>

class Host;
class Tabla;
class Admin;

using namespace std;

class Router
{
	private:
		int m_i1Oct;
		int m_iCantHosts;
		Admin* m_Admin;
		ofstream m_ArchivoSalida;
		list<Host*> m_ListaHosts;
		map< Router*, queue<Paquete*> > m_ColasVecinos;
		map< Host*, queue<Paquete*> > m_ColasLocales;
		map<int, Host*> m_aRefHosts;
		Buffer m_BufferIntermedio;
		Buffer m_BufferIntermedioLocal;
		Tabla* m_TablaEnrutamiento;
		
		bool isVecino (Router* router);
		bool isMismoRouter (Router* router);
		void vaciarBufferInt ();
		void vaciarBufferIntLocal ();
		void vaciarBufferInmediato ();
		void meterEnLista (Paquete* paquete);
		Router* elegirInterfaz (Paquete* paquete);
		Router* elegirInterfaz (int iRouterId);
		void cargarEnColasLocales (Paquete* paquete);
		bool isPaginaLista (Paquete* paquete, queue<Paquete*> cola);
		int getCantPaginasListas (queue<Paquete*>* cola);
		Pagina getPaginaVieja(queue<Paquete*>* cola);
		void enviarLocal ();
		Paquete* getAt (list<Paquete*> lista, int iIndex);
		string toString ();
		string toString (int iNum);

	public:
	
		Router (int i1Oct, Admin* admin);
		int getId ();
		void setTabla (Tabla* tabla);
		list<Host*> getListaHosts ();
		int getCarga (int iDestino);
		void agregarHost (Host* host);
		void agregarVecino (Router* vecino);
		int getCarga (Router* interfaz);
		void recibir (Pagina pagina);
		void recibir (Paquete* paquete);
		void enviar ();
};
#endif
