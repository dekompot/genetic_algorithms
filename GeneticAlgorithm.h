//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_GENETICALGORITHM_H
#define MINIPROJEKT_GENETICALGORITHM_H

#include <utility>

#include "Individual.h"
#include "Problem.h"

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int newPopulationSize, double newMutationProbability, double newCrossingProbability,
                     SmartPointer<Problem> problem, SmartPointer<mt19937> generator) : problem(problem),
                                                                                       bestSolution(new Individual(problem,generator)),
                                                                                       generator(std::move(generator)) {
        populationSize = newPopulationSize;
        mutationProbability = newMutationProbability;
        crossingProbability = newCrossingProbability;
    }
    GeneticAlgorithmRunOutcome run();

    SmartPointer<Individual> getBestSolution() const;

private:
    void generatePopulation();
    void cross();
    void mutate();
    void evaluate();
    int parentIndexOutOfEncounter(int encounterSize);
    bool isValid();

    SmartPointer<Problem> problem;
    vector<SmartPointer<Individual>> population;
    SmartPointer<Individual> bestSolution;
    SmartPointer<mt19937> generator;
    int populationSize;
    double mutationProbability;
    double crossingProbability;
    const static int ENCOUNTER_SIZE = 2;
    const static int ITERATIONS = 1000;
};


#endif //MINIPROJEKT_GENETICALGORITHM_H
