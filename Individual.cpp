//
// Created by 48791 on 18.01.2023.
//
#include "Individual.h"

Individual::Individual(SmartPointer<Problem> newProblem) : problem(SmartPointer<Problem>(newProblem))
{
    size = problem->getSize();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> binaryDistribution(0, 1);
    for (int i = 0 ; i < size ; i++)
    {
        genotype.push_back(binaryDistribution(gen));
    }
}

Individual::Individual(SmartPointer<Problem> newProblem,vector<int> newGenotype) : problem(SmartPointer<Problem>(newProblem))
{
    genotype = newGenotype;
    size = problem->getSize();
}

vector<SmartPointer<Individual>> Individual::cross(SmartPointer<Individual> otherIndividual, double crossingProbability)
{
    vector<int> firstGenotype = vector<int>(genotype);
    vector<int> secondGenotype = vector<int>(otherIndividual->genotype);
    vector<SmartPointer<Individual>> children;
    float randomProbability = (float) rand()/RAND_MAX;
    if (randomProbability < crossingProbability)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> genesDistribution(0, size-1);
        int crossPoint = genesDistribution(gen);
        for (int i = 0 ; i < crossPoint ; i++) {
            firstGenotype.at(i) = otherIndividual->genotype.at(i);
            secondGenotype.at(i) = genotype.at(i);
        }
    }
    children.push_back(SmartPointer<Individual>(new Individual(problem,firstGenotype)));
    children.push_back(SmartPointer<Individual>(new Individual(problem,secondGenotype)));
    return move(children);
}

void Individual::mutate(double mutationProbability)
{
    float randomProbability = 0;
    for (int i = 0 ; i < size ; i++)
    {
        randomProbability = (float) rand()/RAND_MAX;
        if (randomProbability < mutationProbability)
        {
            if (genotype.at(i) == 0) genotype.at(i) = 1;
            else genotype.at(i) = 0;
        }
    }
}

const vector<int> &Individual::getGenotype() const {
    return genotype;
}
