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
    int eval(int *in);
    void adjust(double learningRate, int output, int correctOutput, int *in);
protected:

private:
    std::list<double> weights;
};

#endif //PERCEPTRON_PERCEPTRON_H
