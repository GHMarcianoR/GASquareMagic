//
// Created by zumbi on 04/07/17.
//

#ifndef GAMAGICSQUARE_POPULATION_H
#define GAMAGICSQUARE_POPULATION_H

#include <vector>
#include <unordered_set>
#include "Individual.h"
class Population {
    std::vector<Individual*> vecIndividual;
    std::unordered_set<Individual*> setIndividual;
    int populationSize;
    int objective;
    int magic_constant;
public:
    Population(int sizePopulation, int sizeSquare, bool initialize);
    ~Population();
    Individual* getFittest();
    Individual* getIndividual(int ind);
    void saveIndividual(int pos,Individual *i);
    void sortPopulation();
    void print();
    int size();

};


#endif //GAMAGICSQUARE_POPULATION_H
