#include "Population.h"
#include "Country.h"
#include "randomc.h"

#include <queue>
#include "common.h"

const double CORR_CONSTANT = 1.0/10.0;

//-------------------------------------------------------------------------
Population::Population(Country* c, double survival, double mutation) :
	   survival_rate(survival),
   	   mutation_rate(mutation)	   
{
		size = 0;
		this->country = c;	
};

//-------------------------------------------------------------------------
Population::Population(Country* c, int initsize, double survival, double mutation) :
		country(c),
		size(initsize),
		survival_rate(survival),
        mutation_rate(mutation)
{
		initialize(size);
};

//-------------------------------------------------------------------------
Population::~Population() 
{ 
};

//-------------------------------------------------------------------------
Population& Population::initialize(int initsize) 
{

		assert(size < MAX_POPULATION_SIZE);

		size = initsize;
		for (int i = 0; i < size; i++) {
				paths[i].randomize();
		};
		return *this;
};

//-------------------------------------------------------------------------
Population& Population::insert(const Path& p) 
{
		assert (size < MAX_POPULATION_SIZE - 1);

		paths[size++] = p;
		return *this;
};

//-------------------------------------------------------------------------
pair<Path, Path> Population::pick_a_pair_random() const
{
		/* STUDENTS: I suggest having a couple of methods like this to implement 
		 * your way of selecting the pair to use for breeding */

		/* Paths are stored in array 'paths'. New paths belong to 'newpaths'. */
			
		int i = rnd.IRandom(0, NUM_CITIES-1);
		int j = rnd.IRandom(0, NUM_CITIES-1);
		return make_pair(paths[i],paths[j]);
};

//-------------------------------------------------------------------------
Population& Population::next_gen() {
		
		// do a sort according to energy -- heapsort using inner heap of pqueue
		best();						// does a sort internally

		npc	= 0;					/* new path counter -- counter for inserting new paths */

		/* STUDENTS: Here you should implement your selection strategy. You are given
		 * complete freedom in how to do this. It may be natural to call the method 
		 * 'pick_a_pair' to perform some probabilistic selection.
		 * 
		 * Call the method 'breed' with two parents to insert a new individual into the population.
		 * Since we want to keep the population size constant, make sure you call it this->size times
		 * minus the number of surviving individuals. Do not forget to apply mutation with probability
		 * mutation_rate. Count your new individuals with 'npc' counter.
		 * 
		 */

		int count = 0;
		for ( ; count < size/2; count++)
		{
			int j = rnd.IRandom(0, NUM_CITIES-1);
			breed(paths[0], paths[j]);
		}

		for ( ; count < size; count++)
		{
			pair<Path, Path> p = pick_a_pair_random();
			breed(p.first, p.second);
		}
		
		assert( npc == size );

		for (int i = 0; i < size ; i++) {
			paths[i] = newpaths[i];
		};
		
		return *this;
};

//-------------------------------------------------------------------------
void Population::breed(const Path& parent1, const Path& parent2) {

		int x = rnd.IRandom(0, NUM_CITIES-1);
		int y = rnd.IRandom(0, NUM_CITIES-1);
		int l = x < y ? x : y;
		int u = x < y ? y : x;

		std::auto_ptr< vector<cityID> > g1 = parent1.genom(l,u);
		std::auto_ptr< vector<cityID> > g2 = parent2.genom(l,u);

		CrossOverMap map(*g1, *g2, l, u);

		if (rnd.Random() > 0.5) 
		{
				Path tmp(parent1);
				newpaths[npc] = tmp.apply(map);
		} 
		else 
		{
				Path tmp(parent2);
				newpaths[npc] = tmp.apply(map.flip());
		};
		
		if (rnd.Random() < mutation_rate) newpaths[npc].mutate();
		
		npc++;
};


//-------------------------------------------------------------------------
Path& Population::getPathAt(int index) 
{
		return paths[index];
};

//-------------------------------------------------------------------------
Population& Population::ga(int gen) 
{
		for (int i = gen; i >0 ; i--) 
		{
				if (dump_population) 
				{
						cout << "Generation " << gen - i ;
						display(cout);
				};
				next_gen();
		};
		return *this;
};

//-------------------------------------------------------------------------
void Population::display() const
{
		display( cout );
}

//-------------------------------------------------------------------------
ostream& Population::display(ostream& s) const {
	
		s << " - printing out the population..." << endl;	
		
		for (int i = 0; i < size; i++) {
				paths[i].display();
		};
		
		return s;
}

//-------------------------------------------------------------------------
Path Population::best() {

		priority_queue<Path> pq;

		for (int i = 0; i < size; i++) {
				pq.push(paths[i]);                           // now pq contains all paths, sorted according to energy
		};

		for (int i = 0; i < size; i++) {
				paths[i] = pq.top();
				pq.pop();
		};

		return paths[0];
};