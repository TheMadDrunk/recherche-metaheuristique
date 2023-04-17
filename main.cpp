#include <bits/stdc++.h>
#include "TSP.hpp"
#include "optimisation_algorithms.hpp"

using namespace std;

int main(){
    cout<<"Entrer le nom du fichier : \n";
    string nomfichier = "berlin52";
    //cin>>nomfichier;

    fstream file(nomfichier,ios::in);
    if(!file.is_open()){
        cout<<"Error while openning the file\n";
        return -1;
    }
    
    Path initpath = read_path(file);

    cout<<"init path\n";
    print_indices(initpath);

    Path optimazed_path = escalade_simple(initpath);
    cout<<"escalade simple\n";
    print_indices(optimazed_path);

    // optimazed_path = escalade_simple_antiplateau(initpath);
    // cout<<"escalade simple antiplateau\n";
    // print_indices(optimazed_path);
    
    optimazed_path = escalade_complete(initpath,10);
    cout<<"escalade complete\n";
    print_indices(optimazed_path);

    optimazed_path = recuit_simule(initpath,0.90);
    cout<<"recuit simule\n";
    print_indices(optimazed_path);
    
    return 0;
}