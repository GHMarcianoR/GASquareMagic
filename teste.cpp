//
// Created by zumbi on 04/07/17.
//

#include "teste.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

class Subject{
public:
    int* genotype;
    int size;
    double fitness;
    int aux = 0;
    vector<pair<int, int> > line;
    vector<pair<int, int> > column;

    vector<pair<int, int> > a;

    Subject(int n){
        size = n;
        genotype = new int[size];
        fitness = NULL;
    }

    virtual Subject* clone(){
        Subject* s = new Subject(size);
        s->fitness = fitness;
        for(int i = 0; i < size; i++)
            s->genotype[i] = genotype[i];
        return s;
    }

    ~Subject(){
        delete [] genotype;
    }
};

class Problem{
public:
    virtual Subject* Create() = 0;
    virtual void Print(Subject* s) = 0;
    virtual void Fitness(Subject* s) = 0;
    virtual void Mutation(Subject* s) = 0;
    virtual void Crossover(Subject* a, Subject* b) = 0;
};

class MagicSquare : public Problem{
public:
    int n;
    int genSize;
    int totalSum;
    int result;

    MagicSquare(int n){
        this->n = n;
        genSize = n * n;
        totalSum = 0;
        for(int i = 1; i <= n * n; i++)
            totalSum += i;
    }

    ~MagicSquare(){
    }

    Subject* Create(){
        Subject* s = new Subject(genSize);
        int pool[genSize];
        for(int i = 0; i < n * n; i++)
            pool[i] = i + 1;

        int j = 0;
        for(int i = genSize; i > 0; i--, j++){
            int pos = rand() % i;
            s->genotype[j] = pool[pos];
            swap(pool[genSize - j - 1], pool[pos]);
        }
        return s;
    }

    void Print(Subject* s){
        cout << "{";
        for(int i = 0; i < n * n; i++){
            cout << s->genotype[i] << ", ";
        }
        cout << "}" << endl;
    }

    static bool sortLineColumn(pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    }

    void Fitness(Subject* s){
        bool pool[n * n];
        for(int i = 0; i < n * n; i++)
            pool[i] = false;

        s->fitness = 0.0;
        int sum;
        int fitness[2 * n + 2];

        //lines
        for(int i = 0; i < n; i++){
            sum = 0;
            for(int j = n * i; j < n * i + n; j++){
                sum += s->genotype[j];
                pool[s->genotype[j] - 1] = true;
            }

            fitness[i] = sum;

            s->line.push_back(make_pair(i, sum));
        }

        //repeated numbers
        for(int i = 0; i < n * n; i++)
            if(pool[i] == false){
                s->fitness = INFINITY;
                return;
            }

        //columns
        for(int i = 0; i < n; i++){
            sum = 0;
            for(int j = i; j < genSize; j += n)
                sum += s->genotype[j];

            fitness[n + i] = sum;

            s->column.push_back(make_pair(i, sum));
        }

        sort(s->line.begin(), s->line.end(), sortLineColumn);
        sort(s->column.begin(), s->column.end(), sortLineColumn);

        //diagonals
        sum = 0;
        for(int i = 0; i < genSize; i += (n + 1))
            sum += s->genotype[i];

        fitness[2 * n] = sum;
        sum = 0;
        for(int i = genSize - n; i > 0; i -= (n - 1))
            sum += s->genotype[i];

        fitness[2 * n + 1] = sum;

        sort(fitness, fitness + 2 * n + 2);

        s->fitness = (fitness[2 * n + 1] - fitness[0]);
        s->aux = fitness[0];
    }

    void Mutation(Subject* s){
        //vai até 6
        int a = s->line[0].first * n + s->column[0].first;
        int b = s->line[n - 1].first * n + s->column[n - 1].first;
        swap(s->genotype[a], s->genotype[b]);
    }

    void Crossover(Subject* a, Subject* b){
        //Vai até 6
        int x, ay, by;
        x = rand() % a->size;

        for(int i = 0; i < a->size; i++){
            if(b->genotype[i] == a->genotype[x]){
                by = i;
            }
            if(a->genotype[i] == b->genotype[x]){
                ay = i;
            }
        }

        swap(a->genotype[x], a->genotype[ay]);
        swap(b->genotype[x], b->genotype[by]);
    }
};

class Genetic{
public:
    int generations;
    int populationSize;
    double elitism;
    Subject** population;
    Problem* problem;

    static bool sortFitness(Subject* a, Subject* b){
        bool equal = true;

        if(a->fitness == b->fitness){
            for(int i = 0; i < a->size; i++){
                if(a->genotype[i] != b->genotype[i]){
                    equal = false;
                    break;
                }
            }
            if(equal)
                b->fitness = INFINITY;
        }

        return a->fitness < b->fitness;
    }

    Genetic(int generations, int populationSize, double elitism, Problem* problem){
        this->generations = generations;
        this->problem = problem;
        this->populationSize = populationSize;
        this->elitism = elitism;
    }

    ~Genetic(){
        for(int i = 0; i < populationSize; i++)
            delete population[i];
        delete [] population;
    }

    void Search(){
        InitPopulation();
        stable_sort(population, population + populationSize, sortFitness);

        int i = 0;
        for(i; i < generations && population[0]->fitness > 0; i++){
            Operate();
            Selection();
        }

        cout << population[0]->fitness  << " , " << i << " , ";
        problem->Print(population[0]);

//            Clear();
    }

    void Operate(){
        for(int i = populationSize; i < populationSize * 2; i += 2){
            int s1, s2, a, b;
            a = rand() % populationSize;
            b = rand() % populationSize;
            population[a]->fitness < population[b]->fitness ? s1 = a : s1 = b;

            a = rand() % populationSize;
            b = rand() % populationSize;
            population[a]->fitness < population[b]->fitness ? s2 = a : s2 = b;

            population[  i  ] = population[s1]->clone();
            population[i + 1] = population[s2]->clone();

            /** Sem aplicar probabilidades de movimentos tem resultados melhores **/

//                for(int j = 0; j < rand() % population[0]->size; j++)
//                if(rand() % 100 < 50)
            Crossover(population[i], population[i + 1]);

            Fitness(population[i]);
            Fitness(population[i + 1]);

//                for(int j = 0; j < rand() % population[0]->size; j++)
//                if(rand() % 100 < 10)
            Mutation(population[i]);
//                for(int j = 0; j < rand() % population[0]->size; j++)
//                if(rand() % 100 < 10)
            Mutation(population[i + 1]);

            Fitness(population[i]);
            Fitness(population[i + 1]);
        }
    }

    void InitPopulation(){
        population = new Subject*[populationSize * 2];
        for(int i = 0; i < populationSize; i++){
            population[i] = problem->Create();
            Fitness(population[i]);
        }
    }

    void Fitness(Subject* s){
        problem->Fitness(s);
    }

    void Mutation(Subject* s){
        problem->Mutation(s);
    }

    void Crossover(Subject* a, Subject* b){
        problem->Crossover(a, b);
    }

    void Selection(){
        stable_sort(population + populationSize, population + populationSize * 2, sortFitness);
        int j = populationSize;
        for(int i = populationSize * elitism; i < populationSize; i++, j++)
            swap(population[i], population[j]);

        stable_sort(population, population + populationSize, sortFitness);

        for(int i = populationSize; i < populationSize * 2; i++)
            delete population[i];
    }

    void Clear(){
        delete [] population;
    }
};

int main(int argc, char* args[]){
    srand(472);

    srand(atoi(args[1]));
    if(atoi(args[2]) == 1){

        Problem* p = (Problem*)new MagicSquare(atoi(args[3]));
        for(int i = 0; i < 1; i++){
            Genetic* g = new Genetic(10000, 1000, 0.1, p);
            g->Search();
            delete g;
        }
        delete p;

    }

    return 0;
}