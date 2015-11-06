#include "tsp.h"

/* takes a TSP problem definition 
   and applies the simulated annealing algorithm to it */

int simulated_annealing(CITY * tsp_prob,int cc, double init_temp)
{
	int nTry = 0, nAcc = 0; double t, r, p, oldE, newE;
	TOUR* oldT = generate_random_tour();
	TOUR* iniT = copy_tour(oldT);
	TOUR* bestT = copy_tour(oldT);
	double leastE = energy(tsp_prob, oldT);
	double initE = leastE;
	TOUR* newT;
	srand(time(NULL));
	
	while(nTry < cc)
	{
			t = (double)(cc - nTry)*(init_temp/cc);
			oldE = energy(tsp_prob, oldT);
			newT = generate_mutation(oldT);
			newE = energy(tsp_prob, newT);
			
			if(newE < oldE)
			{
				delete_tour(oldT);
				oldT = copy_tour(newT);
				delete_tour(newT);
				nAcc++;
				
				if(newE < leastE)
				{
					delete_tour(bestT); 
					bestT = copy_tour(oldT);
					leastE = newE;
				}
			}
			else
			{
				p = exp((oldE - newE)/t);
				if(p > 1)	printf("\n~~~~~~~~~~   %f\n", p);
				r = (double)rand()/RAND_MAX;
				if(r <= p)
				{
					delete_tour(oldT);
					oldT = copy_tour(newT);
					delete_tour(newT);
					nAcc++;
				}
			}
			
			nTry++;
	}		
	
	printf("\n\n\n\nThe initial tour:\n");
	show_tour(iniT);
	printf("The energy of the initial tour (%f).\n", initE);
	printf("\nInitial temperature: %f.", init_temp);
	printf("\nNumber of tours tried %d.", nTry);
	printf("\nNumber of tours accepted %d.", nAcc);
	printf("\n\nThe best tour:\n");
	show_tour(bestT);
	printf("The energy of the best tour (%f).\n\n\n", leastE);
	
	return 0;
}

int main()
{
		CITY *tsp_prob;        

		tsp_prob = generate_standard_TSP();
		simulated_annealing(tsp_prob, 100000, 100);

		return 0; 

}

