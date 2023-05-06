#include "TSP.hpp"
#include "optimisation_algorithms.hpp"
#include "genetic_algorithm.hpp"
#include <cmath>
#include <algorithm>

Path escalade_simple_antiplateau(Path init_path)
{
    bool maxlocal;
    int plateau = 0;
    Path current = init_path;
    do
    {
        maxlocal = true;
        Path next = successeur_2opt(current);
        if (next < current)
        {
            current = next;
            maxlocal = false;
            plateau = 0;
        }
        else if (next == current and next.arr != current.arr and plateau < 500)
        {
            current = next;
            maxlocal = false;
            plateau++;
        }
    } while (!maxlocal);

    return current;
}

Path escalade_simple(Path init_path)
{
    bool maxlocal;
    Path current = init_path;
    do
    {
        maxlocal = true;
        Path next = successeur_2opt(current);
        if (next < current)
        {
            current = next;
            maxlocal = false;
        }
    } while (!maxlocal);

    return current;
}

Path escalade_complete(Path init_path, int nStart)
{
    Path best = init_path, random_start = init_path;

    while (nStart--)
    {

        Path next = escalade_simple(path_shuffle(init_path));
        if (next < best)
            best = next;
    }
    return best;
}

double compute_init_temperature(Path path, double startP)
{
    long double deltamean = 0;
    int size = 100;
    for (int i = 0; i < size; i++){
        deltamean += abs(path_shuffle(path).value - path_shuffle(path).value);
    }

    deltamean /= size;
    
    return  - deltamean / log(startP);
}

// probability between 0.0 and 1.0
bool random_bool_with_prob( double prob ) 
{
    prob*=100;
    int nb = rand()%100;
    if(prob >= nb)
        return true;

    return false;
}

Path recuit_simule(Path init_path,double alpha)
{

    double T, init_T = T = compute_init_temperature(init_path, 0.5);
    
    int essais = (int)pow(init_path.arr.size()/2, 2);

    Path current = init_path;
    double dE;
    while (T/init_T > 0.1)
    {
        for (int i = 0; i < essais; i++)
        {
            Path next = path_shuffle(current);//random path
            dE = next.value-current.value;

            if (dE<0 or random_bool_with_prob(exp(-dE/T)))
                current = next;
        }
        
        T*=alpha;
    }

    return current;
}

Path genetic_algorithm(Path init_path,int aim_value,int popu_size){
    vector<Path> population = init_population(init_path,popu_size);
    int gen_size = init_path.arr.size();
    Path best = init_path;

    while (best.value > aim_value)
    {
        cout<<"selection\n";
        vector<Path> selected = selection(population,popu_size/2);
        cout<<"croisement\n";
        vector<Path> children = croisement(selected);
        cout<<"mutation\n";
        //children = mutation(children,1.75/double(popu_size*gen_size));
        children = mutation(children,0.2);

        population.insert(population.end(),children.begin(),children.end());
           
        sort(population.begin(),population.end(),[](Path& l,Path& r){return l.value < r.value;});
        population.erase(population.begin()+popu_size,population.end());
        //print_population(population);
        
        best = population[0];
        cout<<"best : "<<best.value<<'\n';
    }   

    return best;
    
}