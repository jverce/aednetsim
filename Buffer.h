#include <list>

using namespace std;

template <class C> class Buffer
{
	private:
	
		list<C> m_aLista;
		int m_iSize;

	public:

		void insert(C elem);
		void sort();
		bool empty();
		C get();
};
