#ifndef OA_H
#define OA_H

Path escalade_simple(Path init_path);

Path escalade_simple_antiplateau(Path init_path);

Path escalade_complete(Path init_path,int nStart);

Path recuit_simule(Path init_path,double alpha);

#endif