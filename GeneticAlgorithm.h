//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H


#include "Individual.h"
#include "Problem.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, double mutationProbability, double crossingProbability){
        this->populationSize = populationSize;
        this->mutationProbability = mutationProbability;
        this->crossingProbability = crossingProbability;
    }
    Individual solve(SmartPointer<Problem> problem);
private:
    vector<SmartPointer<Individual>> generatePopulation(SmartPointer<Problem> problem);
    vector<SmartPointer<Individual>> cross(vector<SmartPointer<Individual>> population);
    vector<SmartPointer<Individual>> mutate(vector<SmartPointer<Individual>> population);
    Individual getBestSolution(vector<SmartPointer<Individual>> population);
    int populationSize;
    double mutationProbability;
    double crossingProbability;

};


#endif //MINIPROJEKT_GENETICALGORITHM_H
