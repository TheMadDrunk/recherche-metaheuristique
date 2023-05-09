#include "genetic_algorithm.hpp"
#include "optimisation_algorithms.hpp"
#include <bits/stdc++.h>

vector<Path> init_population(Path path,int size){
    vector<Path> out;
    for(int i =0;i<size;i++)
        out.push_back(path_shuffle(path));

    return out;
}


vector<Path> selection(vector<Path>& population,int size){
    long double sum=0;
    long double prob_sum=0;
    long double minimum = population[0].value;
    for_each(population.begin(),population.end(),[&](Path& path){
        sum+=path.value;
        if(minimum > path.value)
            minimum = path.value;
    });
    for_each(population.begin(),population.end(),
    [&](Path& path){
        prob_sum+=sum/path.value;
    });
    

    vector<Path> out;

    while (size>out.size())
        for(Path& p : population){
            if(random_bool_with_prob((sum/p.value)/prob_sum)){
                out.push_back(p);
            }
        }
            
            
    return out;
}

Path crossover(Path parent1,Path parent2){
    int size = parent1.arr.size();

    Path child;
    set<Point> not_visited(parent1.arr.begin(),parent1.arr.end());

    
    child.arr.insert(child.arr.begin(),parent1.arr.begin(),parent1.arr.begin()+size/2);

    for(Point& p : child.arr)
        not_visited.erase(p);

    for(int i = size/2;i<size;i++){
        if(not_visited.count(parent2.arr[i]) == 0){
            child.arr.push_back(*not_visited.begin());
            not_visited.erase(not_visited.begin());
        }
        else {
            child.arr.push_back(parent2.arr[i]);
            not_visited.erase(parent2.arr[i]);
        }
    }

    compute_value(child);

    return child;
}

vector<Path> croisement(vector<Path>& population){
    vector<Path> out;
    
    int size = population.size();

    for(int i = 0;i<size;i++){
        int idx1 = rand()%size,idx2 = rand()%size;

        Path child1 = crossover(population[idx1],population[idx2]);
        Path child2 = crossover(population[idx2],population[idx1]);

        out.push_back(child1);
        out.push_back(child2);
    }

    return out;
}

vector<Path> mutation(vector<Path>& population,double prob){
    vector<Path> out;
    
    for(Path& p : population)
        if(random_bool_with_prob(prob))
            out.push_back(random_swap(p));

    return out;
}

void print_population(vector<Path>& population){
    for_each(population.begin(),population.end(),[](Path& p){cout<<p.value<<' ';});
    cout<<'\n';
}


