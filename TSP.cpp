#include <bits/stdc++.h>
#include "TSP.hpp"

double distance(const Point &a, const Point &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double length(vector<Point> &itineraire)
{
    double valeur = 0;
    for (int i = 1; i < itineraire.size(); i++)
    {
        valeur += distance(itineraire[i-1], itineraire[i]);
    }
    valeur += distance(itineraire.front(), itineraire.back());
    return valeur;
}

Point read_point(fstream &file)
{
    Point out;
    file >> out.indice >> out.x >> out.y;
    return out;
}

void print_indices(Path path)
{
    for (auto i : path.arr)
    {
        cout << i.indice << ' ';
    }
    cout << "\nval : " << path.value << '\n';
}

void compute_value(Path &tsp)
{
    tsp.value = length(tsp.arr);
}

Path read_path(fstream &file)
{
    int t;
    file >> t;

    Path out;

    while (t--)
        out.arr.push_back(read_point(file));
    compute_value(out);

    return out;
}

vector<Point> _2opt(vector<Point> &arr, int start, int end)
{
    vector<Point> out(arr.begin(), arr.end());
    reverse(out.begin() + start, out.begin() + end);
    return out;
}

Path path_shuffle(Path path)
{
    random_shuffle(path.arr.begin(), path.arr.end());
    compute_value(path);
    return path;
}

Path successeur_2opt(Path &initial_path)
{
    double length_best = initial_path.value;
    vector<Point> current_best = initial_path.arr;
    int size = initial_path.arr.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            vector<Point> successeur = _2opt(current_best, i, j);
            double successeur_length = length(successeur);
            if (successeur_length <= length_best)
            {
                length_best = successeur_length;
                current_best = successeur;
            }
        }
    }

    Path out = {current_best, length_best};
    return out;
}

Path random_swap(Path& path){
    Path swaped = path;
    int size = path.arr.size();
    
    int idx1 = rand()%size,idx2 = rand()%size;
    swap(swaped.arr[idx1],swaped.arr[idx2]);
    compute_value(swaped);
    return swaped;
}

bool operator<(const Path &l, const Path &r)
{
    return l.value < r.value;
}

bool operator==(const Path &l, const Path &r)
{
    return l.value == r.value;
}

bool operator==(const Point &l, const Point &r)
{
    return l.indice == r.indice;
}

bool operator<(const Point &l, const Point &r){
    return l.indice < r.indice;
}
