//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H

#include "Individual.h"
#include "Problem.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int newPopulationSize, double newMutationProbability, double newCrossingProbability,
                     SmartPointer<Problem> problem) : problem(problem), population (new vector<SmartPointer<Individual>>),
                                                      bestSolution(new Individual(problem)) {
        populationSize = newPopulationSize;
        mutationProbability = newMutationProbability;
        crossingProbability = newCrossingProbability;
    }
    GeneticAlgorithmRunOutcome run();

    const SmartPointer<Individual> getBestSolution() const;

private:
    void generatePopulation();
    void cross();
    void mutate();
    void evaluate();
    int parentIndexOutOfEncounter(SmartPointer<vector<SmartPointer<Individual>>> population, int encounterSize);
    bool isValid();

    SmartPointer<Problem> problem;
    SmartPointer<vector<SmartPointer<Individual>>> population;
    SmartPointer<Individual> bestSolution;
    int populationSize;
    double mutationProbability;
    double crossingProbability;
    const static int ENCOUNTER_SIZE = 2;
    const static int ITERATIONS = 1000;
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
