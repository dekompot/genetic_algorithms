//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_KNAPSACKPROBLEM_H
#define MINIPROJEKT_KNAPSACKPROBLEM_H


#include "Problem.h"
#include "MySmartPointer.h"
#include <vector>
#include <fstream>
#include <sstream>

class KnapsackProblem : public Problem {

public:
    bool valid;

    KnapsackProblem(double knapsackCapacity, MySmartPointer<vector<double>> productsWeights,
                    MySmartPointer<vector<double>> productsValues)
                    : knapsackCapacity(knapsackCapacity),productsWeights(productsWeights),
                    productsValues(productsValues){
        if (knapsackCapacity <= 0 || isVectorValid(productsWeights)
        || isVectorValid(productsValues)) valid = false;
        else valid = true;}

    double getFitness(MySmartPointer<vector<bool>> genotype) override {
        double fitness = 0;
        if (isAllowed(genotype))
        {
            for (int productIndex = 0 ; productIndex < genotype->size() ; productIndex++)
                if (genotype->at(productIndex))
                    fitness+=productsValues->at(productIndex);
        }
        return fitness;
    }

    KnapsackProblem static checkAndReadFile(string productInformationFile, string knapsackCapacityFile){
        double knapsackCapacity;
        vector<double> *productsWeights;
        vector<double> *productsValues;
        ifstream problemInstanceFile;
        problemInstanceFile.open(productInformationFile);
        if (problemInstanceFile.is_open())
        {
            string line;
            while (getline(problemInstanceFile, line))
            {
                istringstream iss(line);
                double value, weight;
                if (!(iss >> value >> weight)) { break; }
                productsValues->push_back(value);
                productsWeights->push_back(weight);
            }
        }
        problemInstanceFile.open(knapsackCapacityFile);
        if (problemInstanceFile.is_open())
        {
            string line;
            while (getline(problemInstanceFile, line))
            {
                istringstream iss(line);
                double capacity;
                if (!(iss >> capacity)) { break; }
                knapsackCapacity = capacity;
            }
        }
        return KnapsackProblem(knapsackCapacity,
                               MySmartPointer<vector<double>>(productsWeights),
                               MySmartPointer<vector<double>>(productsValues));
    }

private:
    int knapsackCapacity;
    MySmartPointer<vector<double>> productsWeights;
    MySmartPointer<vector<double>> productsValues;

    bool isAllowed (MySmartPointer<vector<bool>> genotype)
    {
        double sum = 0;
        for (int productIndex = 0 ; productIndex < genotype->size() ; productIndex++)
        {
            if (genotype->at(productIndex)) {
                sum+=productsWeights->at(productIndex);
                if (sum > knapsackCapacity) return false;
            }
        }
        return true;
    }

    bool isVectorValid(MySmartPointer<vector<double>> suspectedVector)
    {
        if (suspectedVector->empty()) return true;
        for (int i = 0 ; i < suspectedVector->size() ; i++)
        {
            if (suspectedVector->at(i) < 0) return true;
        }
        return false;
    }
};


#endif //MINIPROJEKT_KNAPSACKPROBLEM_H
