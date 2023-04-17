#ifndef TSP_H
#define TSP_H

using namespace std;

#include <iostream>
#include <vector>

struct Point
{
    int x,y,indice;
};

struct Path
{
    vector<Point> arr;
    double value;
};


double distance(const Point& a,const Point& b);

void compute_value(Path& tsp);

Point read_point(fstream& file);

Path read_path(fstream& file);

void print_indices(Path path);

Path escalade_simple(Path init_path);

Path escalade_simple_antiplateau(Path init_path);

Path escalade_complete(Path init_path,int nStart);

Path recuit_simule(Path init_path,double alpha);

#endif