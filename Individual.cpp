//
// Created by 48791 on 18.01.2023.
//
#include "Individual.h"

Individual::Individual(SmartPointer<Problem> newProblem, SmartPointer<mt19937> generator) : problem(std::move(newProblem)),
                                                                                            generator(generator)
{
    size = problem->getSize();
    uniform_int_distribution<> binaryDistribution(0, 1);
    for (int i = 0 ; i < size ; i++)
    {
        genotype.push_back(binaryDistribution(*generator));
    }
}

Individual::Individual(const Individual &otherIndividual) : problem(otherIndividual.problem), generator(otherIndividual.generator)
{
    size = otherIndividual.size;
    genotype = otherIndividual.genotype;
}

Individual::Individual(SmartPointer<Problem> newProblem,vector<int> newGenotype,SmartPointer<mt19937> generator) : problem(SmartPointer<Problem>(newProblem)),
                                                                                                                   generator(generator)
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
        uniform_int_distribution<> genesDistribution(0, size-1);
        int crossPoint = genesDistribution(*generator);
        for (int i = 0 ; i < crossPoint ; i++) {
            firstGenotype.at(i) = otherIndividual->genotype.at(i);
            secondGenotype.at(i) = genotype.at(i);
        }
    }
    children.push_back(SmartPointer<Individual>(new Individual(problem,firstGenotype,generator)));
    children.push_back(SmartPointer<Individual>(new Individual(problem,secondGenotype,generator)));
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
