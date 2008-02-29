#include <list>

#include "Librerias.h"

using namespace std;

void Buffer<C> :: insert(C elem)
{
	m_aLista.push_back(elem);
	m_iSize++;
}

void Buffer<C> :: sort()
{
	m_aLista.sort();
}

bool Buffer<C> :: empty()
{
	return m_aList.empty();
}

C Buffer<C> :: get()
{
	C elem = m_aLista.front();
	m_aLista.pop_front();
	return elem;
}
