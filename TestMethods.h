#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include "Problem.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "Outcome.h"
#include "OneMaxProblem.h"

#ifndef MINIPROJEKT_SOLVER_H
#define MINIPROJEKT_SOLVER_H


static void solveProblem(SmartPointer<Problem> problem, int iterations, int populationSize, double mutationProbability, double crossingProbability)
{
    random_device randomDevice;
    GeneticAlgorithm myAlgorithm(populationSize, mutationProbability,
                                 crossingProbability, std::move(problem), SmartPointer<mt19937>(new mt19937 (randomDevice())));
    int optimalSolutionOccurences = 0;
    for (int i = 0 ; i < iterations ; i++)
    {
        myAlgorithm.run();
        SmartPointer<Individual> individual = myAlgorithm.getBestSolution();
        if(individual->getGenotype().at(0)==0&&individual->getGenotype().at(1)==0&&
           individual->getGenotype().at(2)==1&&individual->getGenotype().at(3)==1)
            optimalSolutionOccurences++;
    }
    cout << optimalSolutionOccurences << " out of " << iterations << " times soultion was optimal." << endl;
}

static void firstTest()
{
    SmartPointer<vector<double>> values (new vector<double>());
    values->push_back(5);
    values->push_back(1);
    values->push_back(4);
    values->push_back(3);
    SmartPointer<vector<double>> weights (new vector<double>);
    weights->push_back(4);
    weights->push_back(1);
    weights->push_back(3);
    weights->push_back(2);
    SmartPointer<Problem> problemmo(new KnapsackProblem(true,4,5,weights,values));
    solveProblem(problemmo,100,4,0.1,0.5);
}
static int oneMax(int size)
{
    SmartPointer<Problem> problem(new OneMaxProblem(size));
    random_device randomDevice;
    GeneticAlgorithm myAlgorithm(100, 0.2, 0.5, problem, SmartPointer<mt19937>(new mt19937 (randomDevice())));
    myAlgorithm.run();
    SmartPointer<Individual> individual = myAlgorithm.getBestSolution();
    int counter = 0;
    for (int i = 0 ; i < individual->getGenotype().size() ; i++)
    {
        if (individual->getGenotype().at(i) == 1) counter++;
    }
    return counter;
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
    loadAndTestKnapsack(R"(C:\Users\48791\CLionProjects\MiniProjekt\Files\instances\incorrectFile)",
                        100,8,0.1,0.5);
    loadAndTestKnapsack(R"(C:\Users\48791\CLionProjects\MiniProjekt\Files\instances\incorrectKnapsack)",
                        100,8,0.1,0.5);
    loadAndTestKnapsack(R"(C:\Users\48791\CLionProjects\MiniProjekt\Files\instances\dupa)",
                        100,8,0.1,0.5);
    loadAndTestKnapsack(R"(C:\Users\48791\CLionProjects\MiniProjekt\Files\instances\correctKnapsack)",
                        100,8,0.1,0.3);
}


#endif //MINIPROJEKT_SOLVER_H
