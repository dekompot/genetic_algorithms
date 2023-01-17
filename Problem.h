//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_PROBLEM_H
#define MINIPROJEKT_PROBLEM_H
#include <vector>
#include <string>
#include "MySmartPointer.h"

using namespace std;


class Problem {
public:
    virtual double getFitness(MySmartPointer<vector<bool>> genotype) = 0;
};


#endif //MINIPROJEKT_PROBLEM_H
