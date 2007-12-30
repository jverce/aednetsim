#include <string>

using namespace std;

public class Paquete
{
private:
	float m_fIDPagina;
	int m_iIDPaquete;
	IP m_ipDestino;
	IP m_ipOrigen;

public:
	Paquete(IP ipDestino, IP ipOrigen, float fIDPagina, int iIDPaquete);
	string toString();
	float getIDPagina();
	int getIDPaquete();
	IP getIPDestino();
	bool operator<(const Paquete &paquete2);
	bool operator>(const Paquete &paquete2);
	bool operator==(const Paquete &paquete2);
};