//
// Created by zumbi on 04/07/17.
//

#include "Population.h"
#include "Comparator.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <cstring>

Population::Population(int sizePopulation, int sizeSquare, bool initialize)
{
    populationSize = sizePopulation;
    magic_constant = sizeSquare*((int)pow(sizeSquare,2)+1)/2;
    objective = magic_constant*(sizeSquare*2 + 2);
    vecIndividual.reserve(sizePopulation);
   if(initialize)
   {
       for(int i = 0; i<populationSize; i++)
       {
           Individual* ind = new Individual(sizeSquare);
           ind->initialize();
           if (setIndividual.find(ind) == setIndividual.end())
           {
               setIndividual.insert(ind);
               vecIndividual.push_back(ind);
           }

       }
       sortPopulation();
   }

}
Population::~Population() {
     /* for(int i = 1 ; i<populationSize; i++)
      {
           delete vecIndividual[i];
      }*/
      vecIndividual.clear();
}
void Population::saveIndividual(int pos, Individual *i) {

    if(setIndividual.find(i) == setIndividual.end())
    {
        setIndividual.insert(i);
        vecIndividual.push_back(i);
    }
}
Individual* Population::getFittest() {
    return vecIndividual[0];
}
void Population::sortPopulation() {
    std::stable_sort(vecIndividual.begin(), vecIndividual.end(),Comparator());
}
void Population::print() {
    for(int i =0; i<vecIndividual.size(); i++)
        std::cout<<vecIndividual[i]->getFitness()<<" ";
    std::cout<<std::endl;
}
int Population::size()
{
    return populationSize;
}
Individual* Population::getIndividual(int ind)
{
    return vecIndividual[ind];
}