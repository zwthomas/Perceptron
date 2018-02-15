//
// Created by Craven on 2/4/2018.
//

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H
#include <list>

#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG_PRINT(message) {\
    cout << message << endl;   \
}
#else
#define DEBUG_PRINT(message) {}
#endif

class Perceptron {
public:
    explicit Perceptron(int inputs);
    void displayWeights();
    double eval(std::list<double> *in);
    void adjust(double learningRate, int numOutput, double *output, std::list<double> *generatedOutput);
protected:

private:
    std::list<double> weights;
};

#endif //PERCEPTRON_PERCEPTRON_H
