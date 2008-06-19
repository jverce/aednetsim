#include <list>

#include "Librerias.h"

using namespace std;

void Buffer :: insert (Paquete* elem)
{
	m_aLista.push_back(elem);
	m_iSize++;
}

void Buffer :: sort ()
{
	m_aLista.sort();
}

bool Buffer :: empty ()
{
	return m_iSize == 0;
}

Paquete* Buffer :: get ()
{
	Paquete* elem = m_aLista.front();
	m_aLista.pop_front();
	m_iSize--;
	
	return elem;
}
