//
// Created by 48791 on 13.01.2023.
//

#ifndef MINIPROJEKT_INDIVIDUAL_H
#define MINIPROJEKT_INDIVIDUAL_H
#include <vector>
#include <random>
#include "SmartPointer.h"
#include "Problem.h"

using namespace std;

class Individual {
public:
    explicit Individual(SmartPointer<Problem> newProblem);
    Individual(const Individual &otherIndividual) : problem(otherIndividual.problem)
    {
        size = otherIndividual.size;
        genotype = otherIndividual.genotype;
    }
    double getFitness() {problem->getFitness(&genotype);}
    vector<SmartPointer<Individual>> cross(SmartPointer<Individual> otherIndividual, double crossingProbability);
    void mutate(double mutationProbability);
    const vector<int> &getGenotype() const;

private:
    explicit Individual(SmartPointer<Problem> newProblem,vector<int> genotype);
    vector<int> genotype;
    SmartPointer<Problem> problem;
    int size;
};


#endif //MINIPROJEKT_INDIVIDUAL_H
