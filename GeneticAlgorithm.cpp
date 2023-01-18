//
// Created by 48791 on 18.01.2023.
//

#include <random>
#include "GeneticAlgorithm.h"

Individual GeneticAlgorithm::solve(SmartPointer<Problem> problem)
{
    vector<SmartPointer<Individual>> population = generatePopulation(problem);
    for (int i = 0 ; i < 100 ;i++)
    {
        population.at(i)->getFitness();
        population = cross(population);
        population = mutate(population);
    }
    return getBestSolution(population);
}

vector<SmartPointer<Individual>> GeneticAlgorithm::generatePopulation(SmartPointer<Problem> problem) {
    vector<SmartPointer<Individual>> population;
    for (int i = 0 ; i < populationSize ; i++)
    {
        population.push_back(SmartPointer<Individual>(new Individual(problem)));
    }
    return move(population);
}

vector<SmartPointer<Individual>> GeneticAlgorithm::cross(vector<SmartPointer<Individual>> population) {
    vector<SmartPointer<Individual>> newPopulation;
    vector<SmartPointer<Individual>> children;
    SmartPointer<Individual> firstChosenIndividual(population.at(0));
    SmartPointer<Individual> secondChosenIndividual(population.at(0));
    SmartPointer<Individual> thirdChosenIndividual(population.at(0));
    SmartPointer<Individual> fourthChosenIndividual(population.at(0));

    while(newPopulation.size() < populationSize)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> individualsDistribution(0, populationSize-1);

        firstChosenIndividual = population.at(individualsDistribution(gen));
        secondChosenIndividual = population.at(individualsDistribution(gen));
        thirdChosenIndividual = population.at(individualsDistribution(gen));
        fourthChosenIndividual = population.at(individualsDistribution(gen));
        if (firstChosenIndividual->getFitness() < thirdChosenIndividual->getFitness())
            firstChosenIndividual = thirdChosenIndividual;
        if (secondChosenIndividual->getFitness() < fourthChosenIndividual->getFitness())
            secondChosenIndividual = fourthChosenIndividual;

        children = firstChosenIndividual->cross(secondChosenIndividual,crossingProbability);
        newPopulation.push_back(children.at(0));
        newPopulation.push_back(children.at(1));
    }
    return move(population);
}

vector<SmartPointer<Individual>> GeneticAlgorithm::mutate(vector<SmartPointer<Individual>> population) {
    for (int i = 0 ; i < populationSize ; i++)
    {
        population.at(i)->mutate(mutationProbability);
    }
    return population;
}

Individual GeneticAlgorithm::getBestSolution(vector<SmartPointer<Individual>> population) {
    Individual individual = *population.at(0);
    for (int i = 0 ; i < population.size() ; i++)
    {
        if (population.at(i)->getFitness() > individual.getFitness())
            individual = *population.at(i);
    }
    return individual;
}
