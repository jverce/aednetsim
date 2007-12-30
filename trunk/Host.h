#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

public class Host : public I_Intercambiador, private I_Generador
{

private:
	IP m_IP;
	int m_iRandomNumber;
	
	ofstream m_ArchivoSalida;

	Router* m_Gateway;

	IP generarDestino();
	Pagina generarPagina();
	int calcularRandom(int ilim);

public:
	Host(int i1Oct, int i2Oct);
	void setIP(int i1Oct, int i2Oct);
	IP getIP();
	void enviar();
	void recibir(Pagina pagina);
};