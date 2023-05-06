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

Path successeur_2opt(Path &initial_path);

Path path_shuffle(Path path);

bool operator==(const Point &l, const Point &r);

bool operator<(const Point &l, const Point &r);

bool operator==(const Path &l, const Path &r);

bool operator<(const Path &l, const Path &r);

#endif