#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifndef _cs1571_tsp_h
#define _cs1571_tsp_h

/* RAND_MAX is the maximum number that can be generated 
by both random and srandom functions. We have found out that some systems 
do set it correctly, some don't. The following lines allow you to set the value
if it is not defined properly by the system. We use 2147483647 as a default */

#ifdef RAND_MAX
#undef RAND_MAX
#define RAND_MAX 2147483647
#endif


/*** structure CITY ****/
typedef struct _city
{
	double x;
	double y;	
	_city()
	{
		x = -1;
		y = -1;	
	}
}CITY;


/* A tour is represented as an array of integers, labeling different cities. 
A pointer to a TOUR will represent a pointer to this array */
typedef int TOUR;


/*** USEFUL FUNCTIONS *********************/


/* generates a TSP problem with num_cities */
CITY *generate_TSP(int num_cities);

/* loads the standard TSP problem from the file std_tsp.txt */
CITY *generate_standard_TSP();


/* generates a random tour to initialize the simulated annealing algorithm */
/* requires global variable MAX_CITIES to be set appropriately, this is done
   automatically by generate_TSP or generate_standard_TSP functions */
TOUR *generate_random_tour();

/* prints the tour */
void show_tour(TOUR *a_tour);

/* prints the TSP problem definition */
void show_cities(CITY *tsp_prob);


/* makes a copy of a tour */
TOUR *copy_tour(TOUR *tour_src);

/* deletes a tour */
void delete_tour (TOUR *a_tour);

/* generates a mutation of a tour, 
  -- it creates a new tour by allocating the free memory to it
  -- use delete_tour to dispose the allocated memory */
TOUR *generate_mutation(TOUR *a_tour);

/* computes the energy of a tour */
double energy(CITY *tsp_prob, TOUR *a_tour);


#endif
