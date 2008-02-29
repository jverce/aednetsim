#ifndef __IP_H__
#define __IP_H__

#include <string>

using namespace std;

class IP
{
	private:
	
		int m_iPrimerOcteto;
		int m_iSegundoOcteto;

	public:
	
		IP();
		IP(int i1Oct, int i2Oct);
		void setPrimerOcteto(int i1Oct);
		int getPrimerOcteto();
		void setSegundoOcteto(int i2Oct);
		int getSegundoOcteto();
		string toString();
};
#endif
