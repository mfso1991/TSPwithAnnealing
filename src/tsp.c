#include "tsp.h"

/*  number of cities, it is set whenever TSP problem is generated */
int MAX_CITIES =0;

/* initialize various random number generators */
int RANDOM_SEED_X = 10;
int RANDOM_SEED_Y = 21;
int RANDOM_TOUR_SEED = 10;


/* checks if the two cities have the same coordinates (helper function) */
int is_same(CITY *city1, CITY *city2)
{
		if(city1->x == city2->x && city1->y == city2->y)
				return 1;
		else return 0;  
}


/* generates a TSP problem with num_cities cities */
/* returns an array of cities of appropriate size */

CITY *generate_TSP(int num_cities)
{
		CITY *list_of_cities = (CITY*)malloc(num_cities*sizeof(CITY));  
		int mod_operator = 0;
		MAX_CITIES = num_cities;        

		//mod_operator = num_cities;
		mod_operator = (int)ceil(sqrt((double)num_cities));
		//printf("mod_operator %d\n", mod_operator);



		srandom((unsigned) time(NULL));


		//possible bug here
		for(int i = 0; i < num_cities; i++)
		{
				list_of_cities[i].x = ((double)random())/RAND_MAX*mod_operator ;
				//list_of_cities[i].x = (double)random()% sqrt_num_cities;
		}

		for(int i = 0; i < num_cities; i++)
		{
				list_of_cities[i].y = (double)random()/RAND_MAX*mod_operator ;
				//list_of_cities[i].y = (double)random()% sqrt_num_cities;
		}

		for(int i = 0; i < num_cities; i++)
		{
				for(int j = 0; j < num_cities; j++)
				{
						//printf("Entering with j=%d\n", j);    
						if(i != j)      
								if(is_same(&list_of_cities[i], &list_of_cities[j]))     
								{

										list_of_cities[i].x = (double)random()/RAND_MAX*mod_operator ;
										list_of_cities[i].y = (double)random()/RAND_MAX*mod_operator ;
										j = -1;
										/*
										   printf("two cities with same coordinates found");       
										   printf("change the random seeds...\n"); 
										 */
										//      exit(0);
								}
				}       
		}

		/*
		   for(int i = 0; i < num_cities; i++)
		   {
		   printf("%d %d\n", list_of_cities[i].x, list_of_cities[i].y);    
		   }
		 */

		return list_of_cities;
}

/* loads the standard TSP problem from the file std_tsp.txt */
CITY *generate_standard_TSP()
{
		//must initialize MAX_CITIES var

		FILE *fptr = fopen("std_tsp.txt", "r+");
		CITY *list_of_cities; // = (CITY*)malloc(num_cities*sizeof(CITY));      

		if(fptr == NULL)
		{
				printf("Error opening standard problem file\n");
				exit(0);
		}
		fscanf(fptr, "%d", &MAX_CITIES);
		list_of_cities = (CITY*)malloc(MAX_CITIES*sizeof(CITY));        
		for(int i = 0; i < MAX_CITIES; i++)
		{
				fscanf(fptr, "%lf%lf", &list_of_cities[i].x, &list_of_cities[i].y); 
				printf("%f %f\n", list_of_cities[i].x, list_of_cities[i].y);
		}
		fclose(fptr);
		printf("\n Loading standard TSP ...");
		//             show_cities(list_of_cities);
		return list_of_cities;
}

/** helper function */
void shift_array(int *array, int index)
{
		//assume -1 as the last elementof the array
		do      
		{
				array[index] = array[index + 1];        
				index++;
		}while(array[index] != -1);
}


/* generates a random tour to initialize the simulated annealing algorithm */
/* requires global variable MAX_CITIES to be set appropriately, this is done by
   generate_TSP or generate_standard_TSP functions */
TOUR *generate_random_tour()
{
		int city_list[MAX_CITIES + 1];  
		TOUR *random_tour = (int *)malloc(MAX_CITIES*sizeof(int));       
		int tmp = 0;

		/* MAX_CITIES should be set properly */
		srandom((unsigned)time(NULL)); 
		for(int i=0; i < MAX_CITIES; i++)
				city_list[i] = i;       
		city_list[MAX_CITIES] = -1;
		for(int i =0 ; i < MAX_CITIES; i++)     
		{
				tmp = random()%(MAX_CITIES - i);
				random_tour[i] = city_list[tmp];
				shift_array(city_list, tmp);
		}
		return random_tour;             
}

/* prints the tour */
void show_tour(TOUR  *a_tour)
{
		for(int i =0; i < MAX_CITIES; i++)
				printf("%d->", a_tour[i]);
		printf("\n");
		//printf("%d\n", a_tour[0]);
}

/* prints the TSP problem definition */
void show_cities(CITY *cities)
{
		printf("printing cities...\n"); 
		for(int i=0; i < MAX_CITIES; i++)
		{
				printf("%f %f\n", cities[i].x, cities[i].y);    
		}       
}

/* mutates a tour by reversing the tour in between start_pos and end_pos  */
void mutate(TOUR *tour, int start_pos, int end_pos)
{
		int tmp;
		//printf("in mutate\n");
		//no error check h ere beware
		if(start_pos < 0 || end_pos >= MAX_CITIES)
		{
				printf("Error..array index out of bounds\n");   
				return; 
		}
		/*
		   if(start_pos >=end_pos)
		   printf("could not mutate\n");	
		   if(start_pos < end_pos)
		   printf("found a mutation\n");	
		 */

		if(start_pos < end_pos)
		{
				while(start_pos < end_pos)
				{
						tmp = tour[start_pos];  
						tour[start_pos] = tour[end_pos];
						tour[end_pos] = tmp;
						start_pos++;
						end_pos--;
				}       
		}
		else
		{
				if(end_pos == ( MAX_CITIES - 1 - start_pos))
				{
						while(end_pos != 0 && start_pos != (MAX_CITIES -1))
						{
								tmp = tour[start_pos];  
								tour[start_pos] = tour[end_pos];
								tour[end_pos] = tmp;
								start_pos++;
								end_pos--;
						}
						tmp = tour[start_pos];  
						tour[start_pos] = tour[end_pos];
						tour[end_pos] = tmp;
				}
				else if(end_pos > (MAX_CITIES - 1 - start_pos))
				{
						while(start_pos != MAX_CITIES -1)		
						{
								tmp = tour[start_pos];  
								tour[start_pos] = tour[end_pos];
								tour[end_pos] = tmp;
								start_pos++;
								end_pos--;
						}
						tmp = tour[start_pos];  
						tour[start_pos] = tour[end_pos];
						tour[end_pos] = tmp;

						start_pos = 0;
						end_pos--;
						while(start_pos < end_pos)
						{
								tmp = tour[start_pos];  
								tour[start_pos] = tour[end_pos];
								tour[end_pos] = tmp;
								start_pos++;
								end_pos--;
						}       
				}
				else
				{
						while(end_pos != 0)		
						{
								tmp = tour[start_pos];  
								tour[start_pos] = tour[end_pos];
								tour[end_pos] = tmp;
								start_pos++;
								end_pos--;
						}
						tmp = tour[start_pos];  
						tour[start_pos] = tour[end_pos];
						tour[end_pos] = tmp;

						end_pos = MAX_CITIES -1;
						start_pos++;
						while(start_pos < end_pos)
						{
								tmp = tour[start_pos];  
								tour[start_pos] = tour[end_pos];
								tour[end_pos] = tmp;
								start_pos++;
								end_pos--;
						}       
				}
		}
		//show_tour(tour);              
}

/* copies a tour */
TOUR *copy_tour(TOUR *tour_src)
{
		TOUR * tour_dest;

		tour_dest = (TOUR *)malloc(MAX_CITIES*sizeof(int));   
		for(int i = 0; i < MAX_CITIES; i++)
				(tour_dest)[i] = tour_src[i];
		return tour_dest;
}

/* deletes a tour */
void delete_tour (TOUR *a_tour)
{
		free(a_tour);
}

/* generates a mutation of a tour */
TOUR *generate_mutation(TOUR *a_tour)
{
		int *tmp_tour;
		int start;
		int end;
		//	printf("in generate mutation\n");
		tmp_tour = copy_tour(a_tour);   

		start = random()%MAX_CITIES;    
		end = random()%MAX_CITIES;

		mutate(tmp_tour, start, end);
		return tmp_tour;
}

/* computes the Manhattan distance between the two cities */
double calculate_MH(CITY *city1, CITY *city2)
{
		return fabs(city1->x - city2->x) + fabs(city1->y - city2->y);
}



/* computes the energy of a tour */
double energy(CITY *problem, TOUR *a_tour)
{
		double total_energy = 0;   
		for(int i = 0; i < MAX_CITIES -1; i++)
		{
				total_energy += calculate_MH(&problem[a_tour[i]], &problem[a_tour[i+1]]); 
		}               
		total_energy += calculate_MH(&problem[a_tour[0]], &problem[a_tour[MAX_CITIES - 	1]]);    //last city to initial one also is to be added
		return total_energy;
}












