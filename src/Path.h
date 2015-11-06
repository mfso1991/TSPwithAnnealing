#ifndef _cs1571_as3_Path_h
#define _cs1571_as3_Path_h

#include "defs.h"
#include "City.h"
#include "CrossOverMap.h"
#include "Country.h"
#include <memory>

class Path 
{
	protected:
		cityID cities[NUM_CITIES];											// Country will be responsible for the Cities
		double cached_energy;
		bool energy_valid;
	public:
		std::auto_ptr< vector<cityID> > genom(int start, int end) const;
		Path& mutate();														// performs mutation with low probability on self
		Path& randomize();													// randomizes the path
		Path& apply(CrossOverMap& Map);										// applies map resulting from cross-over onto self
		
		void anneal(int cc, double temp);									// do simulated annealing on the path
		double energy();													// energy of the path, for simulated annealing and fitness
		void display() const;												// guess what !?
	
		bool operator< (const Path& rhs) const;
		cityID operator[](int index) const;

		Path();
		Path(Country& cntr);
		Path(const Path&);
		~Path();
};

#endif