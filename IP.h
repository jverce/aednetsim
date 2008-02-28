#ifndef __IP_H__
#define __IP_H__


class IP
{
	private:
	
		int m_iPrimerOcteto;
		int m_iSegundoOcteto;

	public:
	
		IP(int i1Oct, int i2Oct);
		void setPrimerOcteto(int i1Oct);
		int getPrimerOcteto();
		void setSegundoOcteto(int i2Oct);
		int getSegundoOcteto();
		string toString();
};
#endif
