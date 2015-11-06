#include <iostream>
#include "defs.h"
#include "Path.h"
#include "Country.h"
#include "randomc.h"
#include "City.h"
#include "common.h"

//-------------------------------------------------------------------------
Path::Path() 
{
		assert(country.size() == NUM_CITIES);

		for (int i = 0; i < country.size(); i++) {									// I know this doesn' make sense
				cities[i] = country[i].id();										// the code needs to ripen a bit
		}; 
		energy_valid = false;
};

//-------------------------------------------------------------------------
Path::Path(const Path& otherPath)
{
		energy_valid = false;

		for (int i = 0; i < NUM_CITIES; i++)
		{
				cities[i] = otherPath[i];
		}		
		
}

//-------------------------------------------------------------------------
cityID Path::operator[](int index) const
{
		return cities[index];
}

//-------------------------------------------------------------------------
Path::Path(Country& cntr)
{														// creates path 1 -> 2 -> ... -> n -> 1
		for (int i = 0; i < cntr.size(); i++) {
				cities[i] = cntr[i].id();
		};
		energy_valid = false;
		energy();
};

//-------------------------------------------------------------------------
Path::~Path() {
		energy_valid = false;	
};

//-------------------------------------------------------------------------
Path& Path::mutate() {															// mutates the path by exchanging 2 random cities

		int i = rnd.IRandom(0, NUM_CITIES-1);
		int j = rnd.IRandom(0, NUM_CITIES-1);

		// mutates the path by exchanging 2 random cities, inversion works better
		/*	
			cityID tmp = cities[i];
			cities[i] = cities[j];
			cities[j] = tmp;
		 */

		// inversion operator	
		int mx = max(i,j); 
		int mn = min(i,j);

		int tmp;
		while ( mx > mn ) {
				tmp = cities[mx];
				cities[mx] = cities[mn];
				cities[mn] = tmp;	

				mx--; mn++;
		};

		energy_valid = false;
		return *this;

};

//-------------------------------------------------------------------------
Path& Path::randomize() {														// swap cities around randomly a number of times

		City tmp;

		for (int i = 0; i < 2*NUM_CITIES ; i++ ) {
				mutate();
		};

		energy_valid = false;
		return *this;
};

//-------------------------------------------------------------------------
Path& Path::apply(CrossOverMap& map) {

		for (int i = 0; i < NUM_CITIES; i++) {
				cities[i] = map.map(cities[i]);
		};

		energy_valid = false;
		return *this;
};

//-------------------------------------------------------------------------
void Path::anneal(int cc, double temp) 
{

		/* STUDENTS: DO NOT USE, THIS METHOD HAS BEEN CRIPPLED 
		 * do that you don't get solution to part a with the assignment*/
		int round = cc;
		double orig_temp = temp;

		// cout << "DEBUG: Path::anneal() " << round << endl;
		while ( round > 0 ) {
				// mutate
				double oe = energy();										// constant-time in-place recomputation possible !

				int i = rnd.IRandom(0, country.size()-1);
				int j = rnd.IRandom(0, country.size()-1);

				// point mutation
				// cityID tmp = cities[i];
				// cities[i] = cities[j];
				// cities[j] = tmp;

				// inversion
				int mx = max(i,j);
				int mn = min(i,j);

				int tmp;
				while ( mx > mn ) {
						tmp = cities[mx];
						cities[mx] = cities[mn];
						cities[mn] = tmp;

						mx--; mn++;
				};
				// end inversion

				bool temp_en = energy_valid;
				energy_valid = false;

				double ne = energy();
				

				/******************************************************************************
				 * Here comes the key part
				 */
				
				// compiler is being annoying
				oe = oe - ne;
				if (temp_en)
				{
					ne = ne - oe;
				}
				
				/******************************************************************************/

				// linear cooling
				// TODO: astract this, cooling schedule needs not be linear
				temp = (orig_temp * round)/cc;
				round--;
		};
};	

//-------------------------------------------------------------------------
double Path::energy() 
{
		if (energy_valid) return cached_energy;

		double e = 0;
		for (int i = 0; i < NUM_CITIES - 1; i++) 
		{
				assert(cities[i] < NUM_CITIES);
				e += country.ManhDist(cities[i],cities[i+1]);
		};
		e += country.ManhDist(cities[NUM_CITIES-1],cities[0]);

		cached_energy = e;
		energy_valid = true;
		return e;
};

//-------------------------------------------------------------------------
bool Path::operator<(const Path& rhs) const 
{
		return const_cast<Path*>(this)->energy() > const_cast<Path&>(rhs).energy();				
		// this is reversed because the pq places the largest element on top
};

//-------------------------------------------------------------------------
void Path::display() const 
{
		for (int i = 0; i < NUM_CITIES; i++ ) 
		{
				assert( (i < NUM_CITIES) && (cities[i] < NUM_CITIES) );
				country[cities[i]].display();
				cout << " -> ";
		};
		
		country[cities[0]].display();
		cout << endl;
};

//-------------------------------------------------------------------------
std::auto_ptr< vector<cityID> > Path::genom(int start, int end) const
{
		assert ( end - start + 1 > 0);
		
		std::auto_ptr< vector<cityID> > g(new vector<cityID>());
		g->clear();
		
		for (int i = start; i <= end ; i++) 
		{
				g->push_back(cities[i]);
		};
		
		return g;
};