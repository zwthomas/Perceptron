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
    for (int layerCount = 0; layerCount < numLayers; layerCount++) {
        for (int nodeCount = 0; nodeCount < numNodes[layerCount]; nodeCount++) {
            if (layerCount == 0) {
                LAYERS[layerCount].push_back(Perceptron(numInputs));
            } else {
                LAYERS[layerCount].push_back(Perceptron(numNodes[layerCount - 1]));
            }
        }
    }
}

Network::~Network() {
    delete(LAYERS);
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

void Network::feedForward(int **inputs, int *outputs, int cases, int numInputs, string file) {
    DEBUG_PRINT("TESTING")
    return;
    cout << "Here 1" << endl;
    int val;
    double lr = 1;
    for (int row = 0; row < cases; row++) {
        cout << "\nROW: " << row << endl;
        for (int layer = 0; layer < NUM_LAYERS; layer++) {
            cout << "Layer: " << layer << endl;

            auto it = LAYERS[layer].begin();
            it->displayWeights();
            val = it->eval(inputs[row]);
            cout << "VAL: " << val << endl;

            if (val != outputs[row]) {
                cout << "Invalid output: " << val << " " << outputs[row] << endl;
                it->adjust(lr, val, outputs[row],inputs[row]);
                it->displayWeights();
                lr *= .75;
                row = -1;
                break;
            }
        }
    }
    cout << "Here" << endl;
    displayNetwork();
}




