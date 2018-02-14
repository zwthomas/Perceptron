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
    void feedForward(int **inputs, int **outputs, int cases, int numInputs, int outputNum, std::string file);

protected:

private:
    Network(){};
    std::list<Perceptron> *LAYERS;
    int NUM_LAYERS;
    int *NUM_NODES;
    int NUM_INPUTS;
    std::list<int>* fillInputs(int **inputs, int row, int numInputs);
    bool checkOutputs(std::list<int> *generatedOutputs, int **correctOutputs, int caseNum, int numOutputs);
    void adjustLayers(int *output, int *input, std::list<int> *generatedOutputs, int learningRate, int numOutput);

};


#endif //PERCEPTRON_NETWORK_H
