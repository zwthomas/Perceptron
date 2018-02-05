//
// Created by Craven on 2/4/2018.
//

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H
#include <list>
class Perceptron {
public:
    explicit Perceptron(int inputs);
    void displayWeights();
protected:

private:
    std::list<double> weights;
};

#endif //PERCEPTRON_PERCEPTRON_H
