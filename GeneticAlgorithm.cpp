//
// Created by 48791 on 18.01.2023.
//

#include <random>
#include "GeneticAlgorithm.h"

SmartPointer<Individual> GeneticAlgorithm::solve(SmartPointer<Problem> problem)
{
    vector<SmartPointer<Individual>> population = generatePopulation(problem);
    Individual bestSolution(problem);
    for (int i = 0 ; i < 100 ;i++) {
        cross(&population);
        mutate(&population);
        bestSolution = getBestSolution(bestSolution, &population);
        if (bestSolution.getFitness() == 7)
            cout << "!";
        else cout <<"0";

    }
    return &bestSolution;
}

vector<SmartPointer<Individual>> GeneticAlgorithm::generatePopulation(SmartPointer<Problem> problem) {
    vector<SmartPointer<Individual>> population;
    for (int i = 0 ; i < populationSize ; i++)
    {
        population.push_back(SmartPointer<Individual>(new Individual(problem)));
    }
    return move(population);
}

void GeneticAlgorithm::cross(vector<SmartPointer<Individual>> *population) {
    vector<SmartPointer<Individual>> newPopulation;
    vector<SmartPointer<Individual>> children;
    SmartPointer<Individual> firstChosenIndividual(population->at(0));
    SmartPointer<Individual> secondChosenIndividual(population->at(0));
    SmartPointer<Individual> thirdChosenIndividual(population->at(0));
    SmartPointer<Individual> fourthChosenIndividual(population->at(0));

    while(newPopulation.size() < populationSize)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> individualsDistribution(0, populationSize-1);

        firstChosenIndividual = population->at(individualsDistribution(gen));
        secondChosenIndividual = population->at(individualsDistribution(gen));
        thirdChosenIndividual = population->at(individualsDistribution(gen));
        fourthChosenIndividual = population->at(individualsDistribution(gen));
        if (firstChosenIndividual->getFitness() < thirdChosenIndividual->getFitness())
            firstChosenIndividual = thirdChosenIndividual;
        if (secondChosenIndividual->getFitness() < fourthChosenIndividual->getFitness())
            secondChosenIndividual = fourthChosenIndividual;

        children = firstChosenIndividual->cross(secondChosenIndividual,crossingProbability);
        newPopulation.push_back(children.at(0));
        newPopulation.push_back(children.at(1));
    }
}

void GeneticAlgorithm::mutate(vector<SmartPointer<Individual>> *population) {
    for (int i = 0 ; i < populationSize ; i++)
    {
        population->at(i)->mutate(mutationProbability);
    }
}

Individual GeneticAlgorithm::getBestSolution(Individual currBestSolution, vector<SmartPointer<Individual>> *population) {
    for (int i = 0 ; i < population->size() ; i++)
    {
        if (population->at(i)->getFitness() > currBestSolution.getFitness())
        {
            currBestSolution = *population->at(i);
        }
    }
    if (currBestSolution.getFitness() == 7) cout << ">";
    return currBestSolution;
}
