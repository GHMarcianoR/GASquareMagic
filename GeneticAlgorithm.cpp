//
// Created by zumbi on 05/07/17.
//

#include <cstdlib>
#include <iostream>
#include "GeneticAlgorithm.h"
#include "timer.h"
Population* GeneticAlgorithm::evolvePulation(Population *pop)
{
    Population* newPopulation = new Population(pop->size(),sizeSquare,false);

   /* if(elitism)
    {
        newPopulation->saveIndividual(0,pop->getFittest());
    }*/
    for(int i = 0; i<pop->size(); i++)
    {
        Individual* ind1 = tournamentSelection(pop);
        Individual* ind2 = tournamentSelection(pop);
        Individual* newIndiv = crossOver(ind1,ind2);
        newIndiv->mutation();
        newIndiv->calcFitness();
        newPopulation->saveIndividual(i,newIndiv);
    }
    newPopulation->sortPopulation();
    return newPopulation;
}
Individual* GeneticAlgorithm::tournamentSelection(Population* pop)
{
    Population* tournament = new Population(tournamentSize,sizeSquare,false);
    Individual* fittest;
    int id;

    for(int i = 0; i<tournamentSize; i++)
    {
        id = rand() % tournamentSize;
        tournament->saveIndividual(i,pop->getIndividual(id));
    }
    tournament->sortPopulation();
    fittest =  tournament->getFittest();
    delete tournament;
    return fittest;
}
Individual* GeneticAlgorithm::crossOver(Individual *ind1, Individual *ind2)
{
    Individual* newIndividual = new Individual(sizeSquare);
    int* geneInd1 = ind1->inverseSquence();
    int* geneInd2 = ind2->inverseSquence();
    int* geneNewIndividual = new int[sizeSquare*sizeSquare];
    int percent = (int) (sizeSquare*sizeSquare*0.55);
    int len = sizeSquare*sizeSquare;


    for(int index = 0; index<percent; index++)
       geneNewIndividual[index] = geneInd1[index];

    for(int index =percent; index<len; index++)
        geneNewIndividual[index] = geneInd2[index];

    newIndividual->reverseSequence(geneNewIndividual);
    delete geneInd1;
    delete geneInd2;
    delete geneNewIndividual;
    return newIndividual;
}
void GeneticAlgorithm::findSolution() {

    Population* pop = new Population(sizePopulation,sizeSquare,true);
    Population* newp = NULL;
    int gen = 0;
    double start, finish;
    bool found = false;
    while( gen != generations)
    {
        GET_TIME(start);
        gen++;
        newp = this->evolvePulation(pop);

        if(newp->getFittest()->getFitness() == 0)
        {

            std::cout<<"0,"<<gen<<",";
            found = true;
            delete pop;
            break;
        }
        delete pop;
        pop = newp;
        GET_TIME(finish);
      //  std::cout<<"Generation: "<<gen<<" Time: "<<finish-start<<std::endl;
    }
    if(!found)
    {
        /*std::cout<<"Found Solution"<<std::endl;
        std::cout<<"Generations "<<gen<<std::endl;
        pop->getFittest()->print();*/
        std::cout<<pop->getFittest()->getFitness()<<","<<gen<<",";
    }

    delete newp;

}
