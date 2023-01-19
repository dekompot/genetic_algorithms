//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_PROBLEM_H
#define MINIPROJEKT_PROBLEM_H
#include <vector>
#include <string>
#include "SmartPointer.h"
#include "ProblemFileOpeningOutcome.h"

using namespace std;


class Problem {
public:
    virtual double getFitness(vector<int> *genotype) = 0;
    virtual ProblemFileOpeningOutcome readFromFile(string const&fileName) = 0;
    bool isValid()  {
        return valid;
    }
    int getSize()  {
        return size;
    }
protected:
    bool valid;
    int size;
public:
    void setValid(bool valid) {
        Problem::valid = valid;
    }

    void setSize(int size) {
        Problem::size = size;
    }
};


#endif //MINIPROJEKT_PROBLEM_H
