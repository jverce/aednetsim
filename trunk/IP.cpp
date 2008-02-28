#include "IP.h"

		IP::IP(int i1Oct, int i2Oct)
		{
			setPrimerOcteto(i1Oct);
			setSegundoOcteto(i2Oct);
		}
	
		void IP::setPrimerOcteto(int i1Oct)
		{
			m_iPrimerOcteto = i1Oct;
		}

		int IP::getPrimerOcteto()
		{
			return m_iPrimerOcteto;
		}

		void IP::setSegundoOcteto(int i2Oct)
		{
			m_iSegundoOcteto = i2Oct;
		}

		int IP::getSegundoOcteto()
		{
			return m_iSegundoOcteto;
		}

		string IP::toString()
		{
			stringstream stringStream;
			
			stringStream << getPrimerOcteto() << "." << getSegundoOcteto();
			string szAuxString = stringStream.str();

			return szAuxString;
		}

