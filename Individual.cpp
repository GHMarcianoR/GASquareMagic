//
// Created by zumbi on 28/06/17.
//

#include <math.h>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <utility>
#include <algorithm>
#include "Individual.h"

Individual::Individual(int n) {

    size = n;
    square = new int*[size];
    for(int i = 0; i<size; i++)
        square[i] = new int;

    magic_costant = ((size*size*size)+size)/2;
}
Individual::~Individual() {
    for(int i = 0; i < size; i++)
        delete [] square[i];
    delete [] square;

}
void Individual::initialize() {
    std::unordered_set<int> setInit;
    std::unordered_set<int>::iterator it;
    int column =0,line =0,number, lenght = (size*size);

    while(setInit.size() != lenght)
    {
        number = rand() % lenght;
        setInit.insert(number);
    }
    for(it = setInit.begin(); it != setInit.end(); it++)
    {
        square[line][column] = (*it)+1;
        column++;
        if(column == size)
        {
            line++;
            column =0;
        }

    }
    this->calcFitness();
}
void Individual::print() {

    for(int i = 0; i<size; i++)
    {
        for (int j = 0; j < size; ++j) {
            std::cout<<square[i][j]<<" ";
        }
        std::cout<<"\n";
    }


}

void Individual::calcFitness() {
    int parcialLinha,parciaisColunas[size]={};
    int parciaisDig[2] ={};


    int fit[2*size+2];
    int i;
    for(i = 0; i<size; i++)
    {
        parcialLinha = 0;
        parciaisDig[1]+= square[i][size-i-1];
        parciaisDig[0] +=square[i][i];
        for(int j = 0; j<size; j++)
        {
            parcialLinha+=square[i][j];
            parciaisColunas[j]+=square[i][j];
        }
       /* std::pair<int, int> p(i,parcialLinha);
        this->line.push_back(p);*/
        fit[i] = (abs(magic_costant -parcialLinha));
    }
    for(int j = 0; j<size; j++)
          fit[i+j] = (abs(magic_costant - parciaisColunas[j]));

    fit[2*size] =(abs(magic_costant -parciaisDig[0]));
    fit[2*size+1]=(abs(magic_costant -parciaisDig[1]));

    fitness = 0;
    for(int k =0; k<2*size+2; k++)
          fitness+=fit[k];

}
int Individual::getFitness() {
    return this->fitness;
}

int* Individual::inverseSquence() {
    int* inveSequence = new int[size*size];
    int cont;
    for(int val =0; val<size*size; val++)
    {
        cont = 0;
        for(int i =0; i<size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if ((val +1 ) < square[i][j])
                    cont++;
                if (val + 1 == square[i][j])
                {
                    i = size;
                    inveSequence[val] = cont;
                    break;
                }

            }
        }
    }
    return inveSequence;
}
void Individual::reverseSequence(int *invSequence)
{
    int pos[size*size];
    int realSequence[size*size];
    for(int i = size*size; i>=0; i--)
    {
        pos[i] = invSequence[i];
        for(int j = i+1; j<size*size; j++)
            if(pos[j]>= pos[i])
                pos[j]++;
    }
    for(int i = 0; i<size*size; i++)
        realSequence[pos[i]] = i+1;
    int k = 0;
    for(int i = 0; i<size; i++)
       for(int j =0; j<size; j++,k++)
            square[i][j] = realSequence[k];
    calcFitness();
}
void Individual::mutation() {
    int x1,x2,y1,y2, numberSwaps;

    numberSwaps = rand() % (size*size)/2;
    for(int i = 0; i<numberSwaps; i++)
    {
        x1 = rand() % size;
        x2 = rand()% size;
        y1 = rand()% size;
        y2 = rand()% size;
        if ((x1 != x2) || (y1 != y2))
            std::swap(square[x1][y1], square[x2][y2]);
    }
}