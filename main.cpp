#include <iostream>
#include "GeneticAlgorithm.h"
#include "timer.h"
int main(int argc, char* args[]){
    srand(time(NULL));
    int sizePopulation = atoi(args[1]);
    int numberGenerations = atoi(args[2]);
    int tournamentSize = atoi(args[3]);
    double start,finish;
    //Elitism
    int sizeSquare = atoi(args[4]);
    GET_TIME(start);
    GeneticAlgorithm* ga = new GeneticAlgorithm(sizePopulation,numberGenerations,tournamentSize,true,sizeSquare);
    ga->findSolution();
    GET_TIME(finish);
    std::cout<<finish-start<<std::endl;
    delete ga;

    return 0;
}