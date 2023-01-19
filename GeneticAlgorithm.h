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
    SmartPointer<vector<SmartPointer<Individual>>> generatePopulation(SmartPointer<Problem> problem);
    SmartPointer<vector<SmartPointer<Individual>>> cross(SmartPointer<vector<SmartPointer<Individual>>> population);
    void mutate(SmartPointer<vector<SmartPointer<Individual>>> population);
    SmartPointer<Individual> getBestSolution(SmartPointer<Individual> bestSolution, SmartPointer<vector<SmartPointer<Individual>>> population);
    int parentIndexOutOfEncounter(SmartPointer<vector<SmartPointer<Individual>>> population, int encounterSize);
    int populationSize;
    double mutationProbability;
    double crossingProbability;
    const static int ENCOUNTER_SIZE = 2;
    const static int ITERATIONS = 100;
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
