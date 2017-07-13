//
// Created by zumbi on 04/07/17.
//

#ifndef GAMAGICSQUARE_COMPARATOR_H
#define GAMAGICSQUARE_COMPARATOR_H


#include "Individual.h"

class Comparator
{
public:
    Comparator();
    bool operator()(Individual* a, Individual* a1)
    {
        return a->getFitness() < a1->getFitness();
    }
};

#endif //GAMAGICSQUARE_COMPARATOR_H
