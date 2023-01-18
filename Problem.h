//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_PROBLEM_H
#define MINIPROJEKT_PROBLEM_H
#include <vector>
#include <string>
#include "SmartPointer.h"

using namespace std;


class Problem {
public:
    virtual double getFitness(vector<int> *genotype) = 0;
    virtual bool isValid()  {
        return valid;
    }

    virtual int getSize()  {
        return size;
    }
private:
    bool valid;
    int size;
};


#endif //MINIPROJEKT_PROBLEM_H
