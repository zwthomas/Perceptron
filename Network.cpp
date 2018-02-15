//
// Created by Craven on 2/6/2018.
//

#include "Network.h"
#include <iostream>
using namespace std;



Network::Network(int numLayers, int numNodes[], int numInputs) {
    NUM_LAYERS = numLayers;
    NUM_NODES = numNodes;
    NUM_INPUTS = numInputs;
    LAYERS = new list<Perceptron>[numLayers];
    for (int layerCount = 0; layerCount < numLayers; layerCount++) {                // Creates each layer
        for (int nodeCount = 0; nodeCount < numNodes[layerCount]; nodeCount++) {    // Creates each node in the layer
            if (layerCount == 0) {
                LAYERS[layerCount].push_back(Perceptron(numInputs));                // Number of inputs in first layer
                                                                                    // Depends on number of inputs
            } else {
                LAYERS[layerCount].push_back(Perceptron(numNodes[layerCount - 1])); // Rest of rows depend on the previous
            }
        }
    }
}

Network::~Network() {
    delete[] LAYERS;
}

void Network::displayNetwork() {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {
        cout << "Layer " << layer + 1<<  endl;
        auto it = LAYERS[layer].begin();
        while(it != LAYERS[layer].end()) {
            cout << "NODE: "<<  endl;
            it++->displayWeights();
        }
    }
}

void Network::feedForward(double **inputs, double **outputs, int cases, int numInputs, int outputNum, string file) {
    displayNetwork();

    double lr = 1;
    list<double> *ins;
    list<double> *tempOuts;

    for (int row = 0; row < cases; row++) {                     // Passes in each row of input
        ins = fillInputs(inputs, row, numInputs);
        for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers
            tempOuts = new list<double>;
            tempOuts->push_back(1);                             // Bias

            auto percep = LAYERS[layer].begin();                // Pass input to all nodes in the layer
            while(percep != LAYERS[layer].end()) {
                tempOuts->push_back(percep->eval(ins));         // Save the outputs for the input to the next row or final output
                percep++;
            }
            delete(ins);
            ins = tempOuts;
        }
        if (!checkOutputs(ins, outputs, row, outputNum)) {
            printf("RESET\n");
            adjustLayers(outputs[row],inputs[row],ins, lr, outputNum);
            lr *= .9;
            row = -1;
        }
    }
}

/**
 * Takes this inputs in the array and puts them in a list.
 *
 * @param inputs    Array containing inputs
 * @param row       Row in the array we are looking at
 * @param numInputs Number of inputs in that row
 * @return  the inputs for that row in a list
 */
std::list<double> *Network::fillInputs(double **inputs, int row, int numInputs) {
    auto *inList = new list<double>();
    inList->push_back(1);
    for (int col = 0; col < numInputs; col++) {
        inList->push_back(inputs[row][col]);
    }
    return inList;
}

bool Network::checkOutputs(std::list<double> *generatedOutputs, double **correctOutputs, int caseNum, int numOutputs) {
    auto it = generatedOutputs->begin();
    it++;                                           // Skip the bias

    for (int ndx = 0; ndx < numOutputs; ndx++) {
        printf("CHECKING: %f   %f\n", (*it), correctOutputs[caseNum][ndx]);
        if ((*it++) != correctOutputs[caseNum][ndx]) {
            return false;
        }
    }
    return true;
}


void Network::adjustLayers(double *output, double *input, std::list<double> *generatedOutputs, double learningRate, int numOutput) {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers

        auto percep = LAYERS[layer].begin();                // Go through each of the nodes in each layer
        while(percep != LAYERS[layer].end()) {
            percep->adjust(learningRate, numOutput, output, generatedOutputs);
            percep++;
        }

    }
}




