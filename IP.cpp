#include "Classes.h"

public class IP
{
private:
	int m_iPrimerOcteto;
	int m_iSegundoOcteto;

public:
	IP(int i1Oct, int i2Oct)
	{
		setPrimerOcteto(i1Oct);
		setSegundoOcteto(i2Oct);
	}
	
	int getPrimerOcteto()
	{
		return m_iPrimerOcteto;
	}

	int getSegundoOcteto()
	{
		return m_iSegundoOcteto;
	}

	void setPrimerOcteto(int i1Oct)
	{
		m_iPrimerOcteto = i1Oct;
	}

	void setSegundoOcteto(int i2Oct)
	{
		m_iSegundoOcteto = i2Oct;
	}

	string toString()
	{
		string szAuxString = ((string) getPrimerOcteto()) + "." + ((string) getSegundoOcteto());

		return szAuxString;
	}
};
