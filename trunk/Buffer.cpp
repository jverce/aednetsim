#include <list>

#include "Librerias.h"

using namespace std;

void Buffer:: insert(Paquete elem)
{
	m_aLista.push_back(elem);
	m_iSize++;
}

void Buffer:: sort()
{
	m_aLista.sort();
}

bool Buffer:: empty()
{
	return m_aLista.empty();
}

Paquete Buffer:: get()
{
	Paquete elem = m_aLista.front();
	m_aLista.pop_front();
	return elem;
}
