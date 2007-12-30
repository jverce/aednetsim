#include <list>
#include <cstdlib>
#include <ctime>

using namespace std;

public class Pagina
{

private:
	list<Paquete> m_ListaPaquetes;
	int m_iCantPaquetes;
	IP m_IPDestino;
	IP m_IPOrigen;

	float m_fIDPagina;

public:
	Pagina(int iCantPaquetes, IP ipDestino, IP ipOrigen);
	Pagina(list<Paquete> listaPaquetes);
	int getCantPaquetes();
	IP getIPDestino();
	Paquete getPaquete(int ii);
};