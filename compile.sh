#!/bin/bash
echo "compiling..."
g++ main.cpp TSP.cpp genetic_algorithm.cpp optimisation_algorithms.cpp -o TSP
echo "Done"