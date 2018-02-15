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

void Network::feedForward(int **inputs, int **outputs, int cases, int numInputs, int outputNum, string file) {
    printf("IN Feed Forward\n");
    displayNetwork();


    double lr = .9;
    list<int> *ins;
    list<int> *tempOuts;

    for (int row = 0; row < cases; row++) {                     // Passes in each row of input
        //printf("CASE: %i\n", row);
        ins = fillInputs(inputs[row], numInputs);
        for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers
            tempOuts = new list<int>;
            tempOuts->push_back(1);                             // Bias

            auto percep = LAYERS[layer].begin();                // Pass input to all nodes in the layer
            while(percep != LAYERS[layer].end()) {
                int eval = percep->eval(ins);
                //printf("EVAL = %i\n", eval);
                tempOuts->push_back(eval);         // Save the outputs for the input to the next row or final output
                percep++;
            }
            delete(ins);
            ins = tempOuts;
        }
        if (!checkOutputs(ins, outputs[row], outputNum)) {
//            printf("\n\nRESET\n");
//            printf("BEFORE\n");
//            displayNetwork();
            adjustLayers(outputs[row],ins, lr, outputNum);
//            printf("AFTER\n");
//            displayNetwork();
//            exit(1);
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
std::list<int> *Network::fillInputs(int *inputs, int numInputs) {
    auto *inList = new list<int>();
    inList->push_back(1);
    for (int col = 0; col < numInputs; col++) {
        inList->push_back(inputs[col]);
    }
    return inList;
}

bool Network::checkOutputs(std::list<int> *generatedOutputs, int *correctOutputs, int numOutputs) {
    auto it = generatedOutputs->begin();
    it++;                                           // Skip the bias
    //printf("OUTPUT NUM: %i\n", numOutputs);
    for (int ndx = 0; ndx < numOutputs; ndx++) {
        //printf("CHECKING: %i   %i\n", (*it), correctOutputs[ndx]);
        if ((*it++) != correctOutputs[ndx]) {
            return false;
        }
    }
    return true;
}


void Network::adjustLayers(int *output, std::list<int> *generatedOutputs, double learningRate, int numOutput) {
    for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers

        auto percep = LAYERS[layer].begin();                // Go through each of the nodes in each layer
        while(percep != LAYERS[layer].end()) {
            //printf("ADJUSTING\n");
            percep->adjust(learningRate, numOutput, output, generatedOutputs);
            percep++;
        }

    }
}




