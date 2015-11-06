#ifndef _cs1571_as3_Country_h
#define _cs1571_as3_Country_h

#include "defs.h"
#include "City.h"

class Country {
	protected:
		int num_cities;
		vector<City> cities;

	public:

		Country();

		void read_from_file();
		void generate_random();

		int size();
	
		double ManhDist(cityID c1, cityID c2);
        double RealDist(cityID c1, cityID c2);
		
		City& operator[](cityID c);
};

#endif