#ifndef _cs1571_as3_Population_h
#define _cs1571_as3_Population_h

#include <utility>
#include <iostream>

#include "defs.h"
#include "Path.h"
#include "Country.h"

using namespace std;

class Population 
{
		protected:
				Country* country;
				Path paths[MAX_POPULATION_SIZE];
				Path newpaths[MAX_POPULATION_SIZE];
				double energies[MAX_POPULATION_SIZE];

				int npc;									// counter for insertion to newpaths
				int size;
				double survival_rate;
				double mutation_rate;

				void breed(const Path& parent1, const Path& parent2);

		public:
				Population& initialize(int initsize);
				Population& next_gen();
				Population& ga(int gen);					// let the population live for gen generations
				Path best();

				Population& insert(const Path& newpath);	
				Path& getPathAt(int index);
				pair<Path,Path> pick_a_pair_random() const;				// selects a pait of parents

				void display() const;
				ostream& display(ostream& s) const;

				//	Population();
				Population(Country* c, double survival, double mutation);
				//	Population(int initsize);
				Population(Country* c, int initsize, double survival, double mutation);
				~Population();

};

#endif