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




