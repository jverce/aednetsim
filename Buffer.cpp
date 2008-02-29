#include <list>

#include "Librerias.h"

using namespace std;

void Buffer :: insert(C elem)
{
	m_aLista.push_back(elem);
	m_iSize++;
}

void Buffer :: sort()
{
	m_aLista.sort();
}

bool Buffer :: empty()
{
	return m_aList.empty();
}

C Buffer :: get()
{
	C elem = m_aLista.front();
	m_aLista.pop_front();
	return elem;
}
