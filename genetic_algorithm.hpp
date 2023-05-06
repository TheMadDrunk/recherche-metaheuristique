#ifndef GA_H
#define GA_H

#include "TSP.hpp"

vector<Path> init_population(Path path,int size);
//operateur d'evaluation :
//selection
vector<Path> selection(vector<Path>& population,int size);

//croisement
vector<Path> croisement(vector<Path>& population);

//mutation
vector<Path> mutation(vector<Path>& population,double prob);

void print_population(vector<Path>& population);

#endif