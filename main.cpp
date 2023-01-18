#include <iostream>
#include <vector>
#include <random>
#include "Problem.h"
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"

using namespace std;

int main() {
    srand( (unsigned)time( NULL ) );
    vector<double> *val = new vector<double>();
    SmartPointer<vector<double>> values (val);
    values->push_back(5);
    values->push_back(1);
    values->push_back(4);
    values->push_back(3);
    vector<double> *wei = new vector<double>;
    SmartPointer<vector<double>> weights (wei);
    weights->push_back(4);
    weights->push_back(1);
    weights->push_back(3);
    weights->push_back(2);
    KnapsackProblem *myProblem = new KnapsackProblem(true,4,5,weights,values);
    SmartPointer<Problem> problemmo(myProblem);
    GeneticAlgorithm myAlgorithm(100,0.4,0.1);
    for (int j = 0 ; j < 100 ; j++)
    {
        Individual individual = myAlgorithm.solve(problemmo);
        for (int i = 0 ; i < individual.getGenotype().size() ; i++)
        {
            cout << individual.getGenotype().at(i);
        }
        cout <<endl;
    }

    return 0;
}
