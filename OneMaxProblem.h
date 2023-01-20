//
// Created by 48791 on 20.01.2023.
//

#ifndef MINIPROJEKT_ONEMAXPROBLEM_H
#define MINIPROJEKT_ONEMAXPROBLEM_H

#include "Problem.h"

class OneMaxProblem : public Problem {
public:
    explicit OneMaxProblem(int newSize)
    {
        size = newSize;
    }
    double getFitness(vector<int> *genotype) override {
        int sum = 0;
        for(int i = 0 ; i < genotype->size() ; i++)
        {
            if (genotype->at(i) == 1) sum++;
        }
        return sum;
    }

    ProblemFileOpeningOutcome readFromFile(const string &fileName) override {
        return ProblemFileOpeningOutcome::ERROR_INCORRECT_DATA;
    }
};
#endif //MINIPROJEKT_ONEMAXPROBLEM_H
