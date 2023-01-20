//
// Created by 48791 on 19.01.2023.
//
#include "KnapsackProblem.h"
#include "Outcome.h"

KnapsackProblem::KnapsackProblem() :
        productsValues(SmartPointer<vector<double>>(new vector<double>())),
        productsWeights(SmartPointer<vector<double>>(new vector<double>()))
{
    valid = false;
    size = -1;
    knapsackCapacity = -1;
}

KnapsackProblem::KnapsackProblem(bool valid, int size, int knapsackCapacity, const SmartPointer<vector<double>> &productsWeights,
                                 const SmartPointer<vector<double>> &productsValues) : knapsackCapacity(knapsackCapacity),
                                                                                       productsWeights(productsWeights),
                                                                                       productsValues(productsValues) {
    setValid(valid);
    setSize(size);
}

double KnapsackProblem::getFitness(vector<int> *genotype) {
    double fitness = 0, weight = 0;
    for (int productIndex = 0 ; productIndex < genotype->size() ; productIndex++)
    {
        if (genotype->at(productIndex) == 1)
        {
            weight += productsWeights->at(productIndex);
            fitness += productsValues->at(productIndex);
        }
    }
    if (weight > knapsackCapacity) fitness = 0;
    return fitness;
}

ProblemFileOpeningOutcome KnapsackProblem::readFromFile(string const&fileName){
    ifstream problemInstanceFile(fileName);

    if (!problemInstanceFile.is_open())
        return ProblemFileOpeningOutcome::ERROR_FILE_NOT_FOUND;

    if (!readSizeAndCapacity(problemInstanceFile))
        return ProblemFileOpeningOutcome::ERROR_FILE_INCORRECT_FORMAT;

    if (!readWeightsAndValues(problemInstanceFile))
        return ProblemFileOpeningOutcome::ERROR_FILE_INCORRECT_FORMAT;

    problemInstanceFile.close();

    if (!checkParameters())
        return ProblemFileOpeningOutcome::ERROR_INCORRECT_DATA;

    valid = true;
    return ProblemFileOpeningOutcome::SUCCESS;
}

bool KnapsackProblem::readSizeAndCapacity(ifstream &file) {
    file >> size >> knapsackCapacity;
    return (bool)file;
}

bool KnapsackProblem::readWeightsAndValues(ifstream &file) {
    double newValue, newWeight;
    for (int i = 0 ; i < size ; i++)
    {
        if (!file) return false;
        file >> newValue >> newWeight;
        productsValues->push_back(newValue);
        productsWeights->push_back(newWeight);
    }
    return true;
}

bool KnapsackProblem::checkParameters() {
    if (size <= 0 || knapsackCapacity <= 0
    || !isVectorValid(productsValues) || !isVectorValid(productsWeights)) return false;
    valid = true;
    return true;
}

bool KnapsackProblem::isVectorValid(SmartPointer<vector<double>> suspectedVector) {
    for (int i = 0 ; i < size ; i++)
    {
        if (suspectedVector->at(i)<0) return false;
    }
    return true;
}

