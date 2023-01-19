//
// Created by 48791 on 18.01.2023.
//

#include <random>
#include "GeneticAlgorithm.h"

SmartPointer<Individual> GeneticAlgorithm::solve(SmartPointer<Problem> problem)
{
    SmartPointer<vector<SmartPointer<Individual>>> population = generatePopulation(problem);
    SmartPointer<Individual> bestSolution = new Individual(problem);
    for (int i = 0 ; i < ITERATIONS ;i++) {
        population = cross(population);
        mutate(population);
        bestSolution = getBestSolution(bestSolution, population);
    }
    return bestSolution;
}

SmartPointer<vector<SmartPointer<Individual>>> GeneticAlgorithm::generatePopulation(SmartPointer<Problem> problem) {
    SmartPointer<vector<SmartPointer<Individual>>> population (new vector<SmartPointer<Individual>>);
    for (int i = 0 ; i < populationSize ; i++)
    {
        population->push_back(SmartPointer<Individual>(new Individual(problem)));
    }
    return move(population);
}

SmartPointer<vector<SmartPointer<Individual>>> GeneticAlgorithm::cross(SmartPointer<vector<SmartPointer<Individual>>>population) {
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

    return move(newPopulation);
}

void GeneticAlgorithm::mutate(SmartPointer<vector<SmartPointer<Individual>>> population) {
    for (int i = 0 ; i < populationSize ; i++)
    {
        population->at(i)->mutate(mutationProbability);
    }
}

SmartPointer<Individual> GeneticAlgorithm::getBestSolution(SmartPointer<Individual> bestSolution,SmartPointer<vector<SmartPointer<Individual>>> population) {
    for (int i = 0 ; i < population->size() ; i++)
    {
        if (population->at(i)->getFitness() > bestSolution->getFitness())
        {
            bestSolution = population->at(i);
        }
    }

    return SmartPointer<Individual>(new Individual(*bestSolution));
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
