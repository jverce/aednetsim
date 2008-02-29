#include <list>

#include "Librerias.h"

using namespace std;

template <class C> void Buffer <C> :: insert(C elem)
{
	m_aLista.push_back(elem);
	m_iSize++;
}

template <class C> void Buffer <C> :: sort()
{
	m_aLista.sort();
}

template <class C> bool Buffer <C> :: empty()
{
	return m_aLista.empty();
}

template <class C> C Buffer <C> :: get()
{
	C elem = m_aLista.front();
	m_aLista.pop_front();
	return elem;
}
