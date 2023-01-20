//
// Created by 48791 on 18.01.2023.
//

#include <random>
#include "GeneticAlgorithm.h"
#include "Outcome.h"

GeneticAlgorithmRunOutcome GeneticAlgorithm::run()
{
    if(!problem->isValid()) return GeneticAlgorithmRunOutcome::ERROR_INVALID_PROBLEM;
    if(!isValid()) return GeneticAlgorithmRunOutcome::ERROR_INVALID_ALGORITHM_PARAMETERS;
    generatePopulation();
    for (int i = 0 ; i < ITERATIONS ;i++) {
        cross();
        mutate();
        evaluate();
    }
    return GeneticAlgorithmRunOutcome::SUCCESS;
}

void GeneticAlgorithm::generatePopulation() {
    for (int i = 0 ; i < populationSize ; i++)
    {
        population->push_back(SmartPointer<Individual>(new Individual(problem)));
    }
}

void GeneticAlgorithm::cross() {
    SmartPointer<vector<SmartPointer<Individual>>> newPopulation (new vector<SmartPointer<Individual>>);
    vector<SmartPointer<Individual>> children;

    while(newPopulation->size() < populationSize)
    {
        SmartPointer<Individual> firstParent = population->at(parentIndexOutOfEncounter(population,ENCOUNTER_SIZE));
        SmartPointer<Individual> secondParent = population->at(parentIndexOutOfEncounter(population,ENCOUNTER_SIZE));
        children = firstParent->cross(secondParent,crossingProbability);
        newPopulation->push_back(children.at(0));
        newPopulation->push_back(children.at(1));
    }
}

void GeneticAlgorithm::mutate() {
    for (int i = 0 ; i < populationSize ; i++)
    {
        population->at(i)->mutate(mutationProbability);
    }
}

void GeneticAlgorithm::evaluate() {
    for (int i = 0 ; i < population->size() ; i++)
    {
        if (population->at(i)->getFitness() > bestSolution->getFitness())
        {
            bestSolution = SmartPointer<Individual>(new Individual(*population->at(i)));
        }
    }
}

int GeneticAlgorithm::parentIndexOutOfEncounter(SmartPointer<vector<SmartPointer<Individual>>> population,
                                                int encounterSize) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> individualsDistribution(0, populationSize-1);
    int parentIndex = individualsDistribution(gen), randomIndex;
    for (int i = 1 ; i < encounterSize ; i++)
    {
        randomIndex = individualsDistribution(gen);
        if(population->at(randomIndex)->getFitness() > population->at(parentIndex)->getFitness())
            parentIndex = randomIndex;
    }
    return parentIndex;
}

const SmartPointer<Individual> GeneticAlgorithm::getBestSolution() const {
    return bestSolution;
}

bool GeneticAlgorithm::isValid() {
    return populationSize > 0;
}
