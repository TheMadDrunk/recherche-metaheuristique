#include "TSP.hpp"
#include "optimisation_algorithms.hpp"
#include <cmath>

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
    srand(time(0));
    if(prob >= rand()%100)
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