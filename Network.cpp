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

//Network::~Network() {
//    delete(LAYERS);
//}

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
    int val;
    double lr = 1;
    list<int> *ins;
    list<int> *tempOuts;

    for (int row = 0; row < cases; row++) {                     // Passes in each row of input
        ins = fillInputs(inputs, row, numInputs);
        for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers
            tempOuts = new list<int>;
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
            ///
            // need to adjust
            ///
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
std::list<int> *Network::fillInputs(int **inputs, int row, int numInputs) {
    list<int> *inList = new list<int>();
    inList->push_back(1);
    for (int col = 0; col < numInputs; col++) {
        inList->push_back(inputs[row][col]);
    }
    return inList;
}

bool Network::checkOutputs(std::list<int> *generatedOutputs, int **correctOutputs, int caseNum, int numOutputs) {
    auto it = generatedOutputs->begin();
    it++;                                           // Skip the bias

    for (int ndx = 0; ndx < numOutputs; ndx++) {
        if ((*it++) != correctOutputs[caseNum][ndx]) {
            return false;
        }
    }
    return true;
}




