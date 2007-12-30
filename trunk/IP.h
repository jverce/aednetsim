#include <string>

using namespace std;

public class IP
{
private:
	int m_iPrimerOcteto;
	int m_iSegundoOcteto;

public:
	IP(int i1Oct, int i2Oct);
	int getPrimerOcteto();
	int getSegundoOcteto();
	void setPrimerOcteto(int i1Oct);
	void setSegundoOcteto(int i2Oct);
	string toString();
};