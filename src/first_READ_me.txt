
The makefile provided may not work with a regular make command on some of the machines. 
Please try to use gmake if this happens.  

*************************************************************************
The C++ code in this directory implements the genetic algorithm for
solving the TSP problem. 

The key function you need to know is:

void ga(Country& prob_descr, int num_generations, int population_size, double prob_mutation, double survival_rate)

that takes five parameters:
1.   country -- describes the problem (please don't change)
2.   number of generations to simulate
3.   population size (max 500 or play with defs.h)
4.   mutation probability (value between 0 and 1)
5.   survival rate (value between 0 and 1) - how much of the old
     population is kept in the new population. 


The GA function can be found in file main3d.cpp. 

****************************************************************************