//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_KNAPSACKPROBLEM_H
#define MINIPROJEKT_KNAPSACKPROBLEM_H


#include "Problem.h"
#include "SmartPointer.h"
#include "Outcome.h"
#include <vector>
#include <fstream>

class KnapsackProblem : public Problem {

public:

    explicit KnapsackProblem();
    explicit KnapsackProblem(bool valid, int size, int knapsackCapacity, const SmartPointer<vector<double>> &productsWeights,
                    const SmartPointer<vector<double>> &productsValues);
    double getFitness(vector<int> *genotype) override;
    ProblemFileOpeningOutcome readFromFile(string const&fileName) override;
private:
    double knapsackCapacity;
    SmartPointer<vector<double>> productsWeights;
    SmartPointer<vector<double>> productsValues;
    bool readSizeAndCapacity(ifstream& file);
    bool readWeightsAndValues(ifstream& file);
    bool checkParameters();
    bool isVectorValid(SmartPointer<vector<double>> suspectedVector);
};


#endif //MINIPROJEKT_KNAPSACKPROBLEM_H
