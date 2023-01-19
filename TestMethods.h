#include <iostream>
#include <vector>
#include <random>
#include "Problem.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "ProblemFileOpeningOutcome.h"
#ifndef MINIPROJEKT_SOLVER_H
#define MINIPROJEKT_SOLVER_H


static void solveProblem(SmartPointer<Problem> problem, int iterations, int populationSize, double mutationProbability, double crossingProbability)
{
    GeneticAlgorithm myAlgorithm(populationSize,mutationProbability,crossingProbability);
    int optimalSolutionOccurences = 0;
    for (int j = 0 ; j < iterations ; j++)
    {
        SmartPointer<Individual> individual = myAlgorithm.solve(problem);
        if(individual->getGenotype().at(0)==0&&individual->getGenotype().at(1)==0&&
           individual->getGenotype().at(2)==1&&individual->getGenotype().at(3)==1)
            optimalSolutionOccurences++;
    }
    cout << optimalSolutionOccurences << " out of " << iterations << " times soultion was optimal." << endl;
}

static void firstTest()
{
    vector<double> *val = new vector<double>();
    SmartPointer<vector<double>> values (val);
    values->push_back(5);
    values->push_back(1);
    values->push_back(4);
    values->push_back(3);
    vector<double> *wei = new vector<double>;
    SmartPointer<vector<double>> weights (wei);
    weights->push_back(4);
    weights->push_back(1);
    weights->push_back(3);
    weights->push_back(2);
    KnapsackProblem *myProblem = new KnapsackProblem(true,4,5,weights,values);
    SmartPointer<Problem> problemmo(myProblem);
    solveProblem(problemmo,1,8,0.1,0.5);
}

static void loadAndTestKnapsack(string const&fileName, int iterations, double populationSize, double mutationProbability, double crossingProbability)
{
    SmartPointer<Problem> myProblem(new KnapsackProblem);
    ProblemFileOpeningOutcome outcome = myProblem->readFromFile(fileName);
    if (outcome == ProblemFileOpeningOutcome::ERROR_FILE_NOT_FOUND)
        cout<<"The file has not been found."<<endl;
    if (outcome == ProblemFileOpeningOutcome::ERROR_FILE_INCORRECT_FORMAT)
        cout<<"The file has been formatted incorrectly."<<endl;
    if (outcome == ProblemFileOpeningOutcome::ERROR_INCORRECT_DATA)
        cout<<"The file has incorrect data that cannot be interpretted as an instance of a problem."<<endl;
    if (outcome == ProblemFileOpeningOutcome::SUCCESS)
    {
        cout <<"Instance of problem has been loaded from file."<<endl;
        solveProblem(myProblem, iterations,populationSize,mutationProbability,crossingProbability);
    }
}

static void testAllFiles()
{
    loadAndTestKnapsack("C:\\Users\\48791\\CLionProjects\\MiniProjekt\\Files\\instances\\incorrectFile",
                        100,8,0.1,0.5);
    loadAndTestKnapsack("C:\\Users\\48791\\CLionProjects\\MiniProjekt\\Files\\instances\\incorrectKnapsack",
                        100,8,0.1,0.5);
    loadAndTestKnapsack("C:\\Users\\48791\\CLionProjects\\MiniProjekt\\Files\\instances\\dupa",
                        100,8,0.1,0.5);
    loadAndTestKnapsack("C:\\Users\\48791\\CLionProjects\\MiniProjekt\\Files\\instances\\correctKnapsack",
                        100,8,0.1,0.5);
}


#endif //MINIPROJEKT_SOLVER_H
