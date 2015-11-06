#ifndef _cs1571_as2_CrossOverMap_h
#define _cs1571_as2_CrossOverMap_h

#include "defs.h"

class CrossOverMap {
	protected:
		vector<cityID> first;
		vector<cityID> second;
		int lower;
		int upper;
	public:
		cityID map(cityID i);
		CrossOverMap& flip();

		void display();

		CrossOverMap(const vector<cityID>& f, const vector<cityID>& s, int l, int u);

};		

#endif