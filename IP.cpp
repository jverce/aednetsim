#include <string>
#include <sstream>

class IP
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
	
		void setPrimerOcteto(int i1Oct)
		{
			m_iPrimerOcteto = i1Oct;
		}

		int getPrimerOcteto()
		{
			return m_iPrimerOcteto;
		}

		void setSegundoOcteto(int i2Oct)
		{
			m_iSegundoOcteto = i2Oct;
		}

		int getSegundoOcteto()
		{
			return m_iSegundoOcteto;
		}

		string toString()
		{
			stringstream stringStream;
			
			stringStream << getPrimerOcteto() << "." << getSegundoOcteto();
			string szAuxString = stringStream.str();

			return szAuxString;
		}
};
