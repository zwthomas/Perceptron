//
// Created by Craven on 2/6/2018.
//

#ifndef PERCEPTRON_NETWORK_H
#define PERCEPTRON_NETWORK_H

#include "Perceptron.h"
#include <list>
#include <string>

class Network {
public:
    Network(int numLayers, int numNodes[], int numInputs);
    ~Network();
    void displayNetwork();
    void feedForward(double **inputs, double **outputs, int cases, int numInputs, int outputNum, std::string file);

protected:

private:
    std::list<Perceptron> *LAYERS;
    int NUM_LAYERS;
    int *NUM_NODES;
    int NUM_INPUTS;
    std::list<double>* fillInputs(double **inputs, int row, int numInputs);
    bool checkOutputs(std::list<double> *generatedOutputs, double **correctOutputs, int caseNum, int numOutputs);
    void adjustLayers(double *output, double *input, std::list<double> *generatedOutputs, double learningRate, int numOutput);

};


#endif //PERCEPTRON_NETWORK_H
