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
    void feedForward(int **inputs, int *outputs, int cases, int numInputs, std::string file);

protected:

private:
    std::list<Perceptron> *LAYERS;
    int NUM_LAYERS;
    int *NUM_NODES;
    int NUM_INPUTS;

};


#endif //PERCEPTRON_NETWORK_H
