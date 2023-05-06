#ifndef OA_H
#define OA_H

bool random_bool_with_prob(double prob);

Path escalade_simple(Path init_path);

Path escalade_simple_antiplateau(Path init_path);

Path escalade_complete(Path init_path,int nStart);

Path recuit_simule(Path init_path,double alpha);

Path genetic_algorithm(Path init_path,int aim_value,int popu_size);

#endif