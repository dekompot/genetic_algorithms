//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_INDIVIDUAL_H
#define MINIPROJEKT_INDIVIDUAL_H
#include <vector>
#include "MySmartPointer.h"
#include "Problem.h"

using namespace std;

class Individual {
public:
    double getFitness(Problem problem) {
        problem.getFitness(genotype);
    }
    void cross(Individual otherIndividual, int crossPoint)
    {

    }
private:
    MySmartPointer<vector<bool>> genotype;
    private: int size;
};


#endif //MINIPROJEKT_INDIVIDUAL_H
