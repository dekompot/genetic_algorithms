//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_GENETICALGORITM_H
#define MINIPROJEKT_GENETICALGORITM_H


#include "Individual.h"
#include "Problem.h"

class GeneticAlgoritm {
public:
    GeneticAlgoritm(int populationSize, double mutationProbability, double crossingProbability){
        this->populationSize = populationSize;
        this->mutationProbability = mutationProbability;
        this->crossingProbability = crossingProbability;
    }
    Individual solve(Problem problem)
    {

        return
    }
private:
    MySmartPointer<vector<Individual>> population = MySmartPointer<vector<Individual>>(nullptr);
    int populationSize;
    double mutationProbability;
    double crossingProbability;

};


#endif //MINIPROJEKT_GENETICALGORITM_H
