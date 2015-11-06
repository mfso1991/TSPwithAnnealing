/*
CS 2710 This program demonstrates use of genetic algorithm for TSP

Tomas Singliar

DISCLAIMER:
This code is very raw and some purification & commenting is badly needed.
I know it so do not give me too hard of a time for it. This file should
be mostly allright; study the others at your own risk of offense to your
programmer instincts.

Look below for parameter descriptions.

*/


#include <iostream>

#include "defs.h"
#include "Country.h"
#include "Population.h"
#include "Path.h"
#include "randomc.h"
#include "CrossOverMap.h"
#include <time.h>
#include "common.h"

void ga(Country& prob_descr, int num_generations, int population_size, double prob_mutation, double survival_rate) {
	
	Population pop(&prob_descr, population_size, survival_rate, prob_mutation);
	int mutcount = 0;

	if (population_size > MAX_POPULATION_SIZE) {
		cout << "You have set a very large population size, increase MAX_POPULATION_SIZE in defs.h!" << endl;
		return;
	};
	
	pop.initialize(population_size);					

	Path best = pop.best();
    //cout << "This is the best random path we have, energy " << best.energy() << " :\n";
    //best.display();

	for (int i = 0; i < num_generations; i++) {

		pop.next_gen();
		
		best = pop.best();												// find the best for progress indication
    	//cout << "Generation " << i << " - best path, energy " << best.energy() << " :\n";
    	//best.display();
		
	};	

	best = pop.best();
    cout << "\nThis is the best path that has evolved, energy " << best.energy() << " (suvival rate " << survival_rate << ") :\n";
	//best.display();
	cout << "Mutations in the process: " << mutcount << endl;
};

/******************************************************************************************************
 ******************************************************************************************************/


int main() {

	cout << "This is the genetic algorithm for course CS2710 assignment 3.\n";
	
	country.read_from_file();										// initialize our country to be the standard one

	// The genetic algorithm parameters:
	// 1. 	country 			describes the problem (please don't change)
	// 2.	number of generations
	// 3.	population size (max 500 or play with defs.h)
	// 4. 	mutation probability										(0,1)
	// 5. 	survival rate (how much of the old population is kept)		(0,1)
	double g;
	for(g = 0.0; g <= 1.0; g += 0.2)	
		ga(country, 300, 300, 0.03, g);

	return 0;

};