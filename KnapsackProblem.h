//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_KNAPSACKPROBLEM_H
#define MINIPROJEKT_KNAPSACKPROBLEM_H


#include "Problem.h"
#include "SmartPointer.h"
#include <vector>
#include <fstream>
#include <sstream>

class KnapsackProblem : public Problem {

public:

    KnapsackProblem() :
        productsValues(SmartPointer<vector<double>>(new vector<double>())),
        productsWeights(SmartPointer<vector<double>>(new vector<double>()))
        {
            valid = false;
            size = -1;
            knapsackCapacity = -1;
        }

    KnapsackProblem(bool valid, int size, int knapsackCapacity, const SmartPointer<vector<double>> &productsWeights,
                    const SmartPointer<vector<double>> &productsValues) : valid(valid), size(size),
                                                                          knapsackCapacity(knapsackCapacity),
                                                                          productsWeights(productsWeights),
                                                                          productsValues(productsValues) {}

    double getFitness(vector<int> *genotype) override {
        double fitness = 0, sum = 0;
        for (int productIndex = 0 ; productIndex < genotype->size() ; productIndex++)
        {
            if (genotype->at(productIndex) == 1)
            {
                sum += productsWeights->at(productIndex);
                fitness += productsValues->at(productIndex);
            }
        }
        if (sum > knapsackCapacity) fitness = 0;
        return fitness;
    }

    /*KnapsackProblem static checkAndReadFile(string productInformationFile, string knapsackCapacityFile){
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
                               SmartPointer<vector<double>>(productsWeights),
                               SmartPointer<vector<double>>(productsValues));
    }*/

    bool isValid() override {
        return valid;
    }

    int getSize() override {
        return size;
    }
private:
    bool valid;
    int size;
    int knapsackCapacity;
    SmartPointer<vector<double>> productsWeights;
    SmartPointer<vector<double>> productsValues;

    /*bool isVectorValid(SmartPointer<vector<double>> suspectedVector)
    {
        if (suspectedVector->empty()) return true;
        for (int i = 0 ; i < suspectedVector->size() ; i++)
        {
            if (suspectedVector->at(i) < 0) return true;
        }
        return false;
    }*/
};


#endif //MINIPROJEKT_KNAPSACKPROBLEM_H
