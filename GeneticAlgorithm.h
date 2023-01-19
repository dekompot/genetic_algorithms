//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H

#include "Individual.h"
#include "Problem.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int newPopulationSize, double newMutationProbability, double newCrossingProbability) {
        populationSize = newPopulationSize;
        mutationProbability = newMutationProbability;
        crossingProbability = newCrossingProbability;
    }
    SmartPointer<Individual> solve(SmartPointer<Problem> problem);
private:
    vector<SmartPointer<Individual>> generatePopulation(SmartPointer<Problem> problem);
    void cross(vector<SmartPointer<Individual>> *population);
    void mutate(vector<SmartPointer<Individual>> *population);
    Individual getBestSolution(Individual currBestSolution, vector<SmartPointer<Individual>> *population);
    int populationSize;
    double mutationProbability;
    double crossingProbability;
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
