#include "Country.h"
#include "randomc.h"

#include <fstream>
#include <time.h>

#include "common.h"

//-------------------------------------------------------------------------
Country::Country() {
		cities.clear();
		num_cities = 0;
};

//-------------------------------------------------------------------------
void Country::read_from_file() {						/* using legacy code */
		/* TODO: no consistency checks */
		double x,y;
		ifstream inp;

		inp.open("std_tsp.txt",ios::in);
		inp >> num_cities;
		// cout << "DEBUG: Country::read_from_file() - Read number " << num_cities << endl;
		for(int i = 0; i < num_cities; i++) {
				inp >> x >> y;
				// cout << "DEBUG: x= " << x << "   y = " << y << endl;
				City c(x,y,i);
				cities.push_back(c);							// inserts the new City into this Country
		};
		// cout << "DEBUG: Country::read_from_file() - Closing file " << endl;
		inp.close();
};

//-------------------------------------------------------------------------
void Country::generate_random() {
		double x,y;
		double side = sqrt(double(num_cities));
		for(int i = 0; i < num_cities; i++) {
				x = rnd.Random() * side;				// random position within the square that makes the cities about the same density
				y = rnd.Random() * side;				// a good random generator never returns the same number for a long run of tries
				City c(x,y,i);
				cities.push_back(c); 			 	            // inserts the new City into this Country
		};	
};

//-------------------------------------------------------------------------
double Country::ManhDist(cityID c1, cityID c2) {
		double d = fabs(cities[c1].getx() - cities[c2].getx()) + 
				fabs(cities[c1].gety() - cities[c2].gety());
		return d;
};

//-------------------------------------------------------------------------
double sqr(double x) {
		return x*x;
};

//-------------------------------------------------------------------------
double Country::RealDist(cityID c1, cityID c2) {
		return sqrt(sqr(cities[c1].getx() - cities[c2].getx()) + 
						sqr(cities[c1].gety() - cities[c2].gety()));
};

//-------------------------------------------------------------------------
City& Country::operator[](cityID c) {
		return cities[c];
};

//-------------------------------------------------------------------------
int Country::size() {
		return cities.size();
};