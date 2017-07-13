//
// Created by zumbi on 28/06/17.
//

#ifndef GAMAGICSQUARE_INDIVIDUAL_H
#define GAMAGICSQUARE_INDIVIDUAL_H

#include <vector>
class Individual {
    int **square;
    int size;
    int fitness;
    int magic_costant;
public:
    Individual(int n);
    ~Individual();
    void initialize();
    void print();
    void calcFitness();
    int getFitness();
    int *inverseSquence();
    void reverseSequence(int* invSequence);
    void mutation();
};


#endif //GAMAGICSQUARE_INDIVIDUAL_H
