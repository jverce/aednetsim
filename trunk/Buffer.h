#include <list>

using namespace std;

class Buffer
{
	private:
	
		list<Paquete*> m_aLista;
		int m_iSize;

	public:

		void insert(Paquete* elem);
		void sort();
		bool empty();
		Paquete* get();
};
