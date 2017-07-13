//
// Created by zumbi on 05/07/17.
//

#ifndef GAMAGICSQUARE_GENETICALGORITHM_H
#define GAMAGICSQUARE_GENETICALGORITHM_H


#include "Population.h"

class GeneticAlgorithm {
    double generations;
    int sizePopulation;
    int tournamentSize;
    bool elitism;
    int sizeSquare;

public:
    GeneticAlgorithm(int sizePop, int numberGenerations, int tS, bool el,int sQ)
            :sizePopulation(sizePop), generations(numberGenerations),
             tournamentSize(tS), elitism(el), sizeSquare(sQ){}

    Population* evolvePulation(Population* pop);
    Individual* tournamentSelection(Population *pop);
    Individual* crossOver(Individual* ind, Individual* ind2);

    void findSolution();

};


#endif //GAMAGICSQUARE_GENETICALGORITHM_H
