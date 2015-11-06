#ifndef _cs1571_as3_defs_h
#define _cs1571_as3_defs_h

typedef int cityID;

// Standard Template Library
#include <vector>
#include <map>

using namespace std;


// General parameters
const int NUM_CITIES = 60;				// please keep at this value, the code uses that asssumption
										// sorry for the incovenience

// Genetic algorithm parameters
const int MAX_POPULATION_SIZE = 501;

// various options for the genetic algorithm

const bool dump_population = false;			// whether to display detailed population

// Simulated annealing parameters

const double TEMPERATURE = 50.0;
const int COOLING_CYCLES = 250 * 1000;

#endif