#include <iostream>
#include "CrossOverMap.h"
#include <assert.h>

//-------------------------------------------------------------------------
CrossOverMap::CrossOverMap(const vector<cityID>& f, const vector<cityID>& s, int l, int u) 
{
		first = f;
		second = s;
		lower = l;
		upper = u;
		assert(f.size() == s.size());
};

//-------------------------------------------------------------------------
void CrossOverMap::display() {

		cout << "************************** This is the map: *******************" << endl;
		for (unsigned int i=0; i < first.size(); i++) {
				cout.width(4);
				cout << first[i];
		};
		cout << endl;

		for (unsigned int i=0; i < first.size(); i++) {
				cout << "   |";
		};
		cout << endl;

		for (unsigned int i=0; i < first.size(); i++) {
				cout << "   V";
		};
		cout << endl;

		for (unsigned int i=0; i < first.size(); i++) {
				cout.width(4);
				cout << second[i];
		};
		cout << endl;
		cout << "***************************************************************" << endl;
};

//-------------------------------------------------------------------------
cityID CrossOverMap::map(cityID i) {
		int index = -1;

		assert(first.size() == second.size());
		assert(first.size() > 0);									/* the whole thing can be cached using std::map */

		for (unsigned int k = 0; k < first.size(); k++) {				// find the cityID in genom
				if (first[k] == i) {
						index = k;
						break;
				};
		};

		int j = i;
		if (index == -1) {											// apply reverse fixpointed map
				bool image_in_range = true;
				while (image_in_range) {
						image_in_range = false;
						for (int k = 0; k <= upper - lower; k++) {
								if (second[k] == j) {
										j = first[k];
										image_in_range = true;
								};
						};
				};
				return j;
		}
		else 
		{														// should get here if index = -1, i is out of crossover region
				return second[index];
		}
};

//-------------------------------------------------------------------------
CrossOverMap& CrossOverMap::flip() 
{
		std::swap(first, second);
		return *this;
};