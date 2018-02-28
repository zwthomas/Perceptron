//
// Created by Craven on 2/4/2018.
//

#ifndef PERCEPTRON_PERCEPTRON_H
#define PERCEPTRON_PERCEPTRON_H
#include <list>

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#define DEBUG_PRINT(message) {\
    cout << message << endl;   \
}
#define DEBUG_EVAL(s) {s}
#else
#define DEBUG_PRINT(message) {}
#define DEBUG_EVAL(s) {s}
#endif

class Perceptron {
public:
    explicit Perceptron(int inputs);
    void displayWeights();
    int eval(std::list<int> *in);
    void adjust(double learningRate, int numOutput, int *output, std::list<int> *generatedOutput, int *input);
    void setWeights(double w[]);
protected:

private:
    std::list<double> weights;
};

#endif //PERCEPTRON_PERCEPTRON_H
