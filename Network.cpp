/*
 * Zachary Thomas
 * 2/6/2018
 * Perceptron network to evaluate binary expressions
 */

#include "Network.h"
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;


/**
 * Creates a network of perceptrons of the input specifications. Each perceptron will have random weights.
 *
 * @param numLayers     The number of layers of perceptrons
 * @param numNodes      Array containing the number of nodes in each layer
 * @param numInputs     Number of inputs going into the first layer
 */
Network::Network(int numLayers, int numNodes[], int numInputs) {
    NUM_LAYERS = numLayers;
    NUM_NODES = numNodes;
    NUM_INPUTS = numInputs;
    LAYERS = new Perceptron*[numLayers];
    for (int layerCount = 0; layerCount < numLayers; layerCount++) {                // Creates each layer
        LAYERS[layerCount] = new Perceptron(numNodes[layerCount]);

        for (int nodeCount = 0; nodeCount < numNodes[layerCount]; nodeCount++) {    // Creates each node in the layer
            if (layerCount == 0) {
                LAYERS[layerCount][nodeCount] = Perceptron(numInputs + 1);               // Number of inputs in first layer
                                                                                    // Depends on number of inputs
            } else {
                LAYERS[layerCount][nodeCount] = Perceptron(numNodes[layerCount - 1] + 1); // Rest of rows depend on the previous
            }
        }
    }
}

/**
 * Cleans pointers in network.
 */
Network::~Network() {
    delete[] LAYERS;
}

/**
 * Displays the weights in the network for debugging purposes.
 */
void Network::displayNetwork() {
    for (int layerNdx = 0; layerNdx < NUM_LAYERS; layerNdx++) {
        cout << "Layer " << layerNdx << ":" <<  endl;
        for (int nodeNdx = 0; nodeNdx < NUM_NODES[layerNdx]; nodeNdx++) {
            cout << "\tNode " << nodeNdx << " : ";
            LAYERS[layerNdx][nodeNdx].displayWeights();
            cout << endl;
        }
    }
}

/**
 * Feeds the input through the network. Adjusting the weights of each node until the correct output is achieved.
 *
 * @param inputs    Array containing all the test cases
 * @param outputs   Array containing output to all of those test cases
 * @param cases     Number of test cases
 * @param numInputs Number of input per test case
 * @param outputNum Number of outputs generated by the network
 * @param file      Filename to save the weights to
 */
void Network::feedForward(int **inputs, int **outputs, int cases, int numInputs, int outputNum, string file) {
    DEBUG_PRINT("Entering feed")
    //DEBUG_EVAL(displayNetwork();)

    double lr = .1;
    int *inputsToLayer;
    int *tempOuts;
    int eval;
    int **totalOutput;

    for (int row = 0; row < cases; row++) {                     // Passes in each row of input
        totalOutput = new int*[NUM_LAYERS];
        inputsToLayer = fillInputs(inputs[row], numInputs);

        for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Feeds the input and results through all of the layers
            totalOutput[layer] = new int[NUM_NODES[layer] + 1];
            tempOuts = new int[NUM_NODES[layer] + 1];
            tempOuts[0] = 1;                                    // Bias
            totalOutput[layer][0] = 1;

            for (int perceptronNdx = 0; perceptronNdx < NUM_NODES[layer]; perceptronNdx++) {    // Go through all perceptrons in layer
                eval = LAYERS[layer][perceptronNdx].eval(inputsToLayer);                        // Pass input to all nodes in the layer
                totalOutput[layer][perceptronNdx + 1] = eval;
                tempOuts[perceptronNdx + 1] = eval;
            }

            delete(inputsToLayer);
            inputsToLayer = tempOuts;
        }
        if (!checkOutputs(inputsToLayer, outputs[row], outputNum)) {      // If the output is wrong adjust weights and start over
            DEBUG_PRINT("Adjusting");
            cout << "Adjusting" << endl;
            backProp(outputs[row], totalOutput, outputNum, lr, inputs[row]);
            displayNetwork();
            //adjustLayers(outputs[row],inputsToLayer, lr, outputNum, inputs[row]);
            //displayNetwork();
            //sleep(2);
            //lr *= .9;
            row = -1;
        }

        delete(inputsToLayer);
        for (int ndx = 0; ndx < NUM_LAYERS; ndx++) {
            delete(totalOutput[ndx]);
        }
        delete(totalOutput);
    }
}

void Network::backProp(int *output, int **allOutputs, int numOutput, double learningRate, int *input) {
    double **allDeltas = new double*[NUM_LAYERS];
    allDeltas[NUM_LAYERS - 1] = createDeltas(output, allOutputs[NUM_LAYERS - 1], numOutput);

    for (int layerNdx = NUM_LAYERS - 2; layerNdx >= 0; layerNdx++) {
        for (int nodeNdx = 0; nodeNdx < NUM_NODES[layerNdx]; nodeNdx++) {
            double out = allOutputs[layerNdx][nodeNdx];
            allDeltas[layerNdx][nodeNdx] =  out * (1 - out) * calcSum(allDeltas, layerNdx, nodeNdx);
        }
    }

    for (int layerNdx = 0; layerNdx < NUM_LAYERS; layerNdx++) {
        for (int nodeNdx = 0; nodeNdx < NUM_NODES[layerNdx]; nodeNdx++) {
            adjustWeights(allDeltas, input, allOutputs, layerNdx, nodeNdx, learningRate);
        }
    }
}

void Network::adjustWeights(double **allDeltas, int *input, int **allOutputs, int layerNdx, int nodeNdx, double learningRate) {
    double change;
    for (int weightNdx = 0; weightNdx < LAYERS[layerNdx][nodeNdx].numWeight(); weightNdx++) {
        int x;
        if (layerNdx == 0) {
            if (weightNdx == 0) {
                x = 1;
            } else {
                x = input[weightNdx - 1];
            }
        } else {
            x = allOutputs[layerNdx - 1][weightNdx];
        }
        change = LAYERS[layerNdx][nodeNdx].getWeight(weightNdx) + learningRate * allDeltas[layerNdx][nodeNdx] * x;
        LAYERS[layerNdx][nodeNdx].setWeight(weightNdx, change);
    }
}

double Network::calcSum(double **allDeltas, int layerNdx, int nodeNdx) {
    double sum = 0;
    for (int perceptronNdx = 0; perceptronNdx < NUM_NODES[layerNdx + 1]; perceptronNdx++) {
        sum += LAYERS[perceptronNdx]->getWeight(nodeNdx) * allDeltas[layerNdx][perceptronNdx];
    }
    return sum;
}

double* Network::createDeltas(int *output, int *generatedOutputs, int numOutput) {
    double *deltas = new double[numOutput];


    for (int ndx = 0; ndx < numOutput; ndx++) {
       deltas[ndx] = generatedOutputs[ndx+ 1] * (1 - generatedOutputs[ndx + 1]) * (output[ndx] - generatedOutputs[ndx + 1]);
    }
    return deltas;
}

/**
 * Takes this inputs in the array and puts them in a list.
 *
 * @param inputs    Array containing inputs
 * @param row       Row in the array we are looking at
 * @param numInputs Number of inputs in that row
 * @return  the inputs for that row in a list
 */
int *Network::fillInputs(int *inputs, int numInputs) {
    int *temp = new int[numInputs + 1];
    temp[0] = 1;                                    // Bias
    memcpy(temp + 1,inputs, sizeof(int) * numInputs);
    return temp;
}

/**
 * Checks to see if the generated output matches correct output.
 *
 * @param generatedOutputs  list of generated output
 * @param correctOutputs    array of correct output
 * @param numOutputs        Number of outputs
 * @return  true if outputs match
 */
bool Network::checkOutputs(int *generatedOutputs, int *correctOutputs, int numOutputs) {

    for (int ndx = 0; ndx < numOutputs; ndx++) {
        if (generatedOutputs[ndx + 1] != correctOutputs[ndx]) {       // Skip the bias
            return false;
        }
    }
    return true;
}


///**
// * Adjusts the weights of all the nodes in the network.
// *
// * @param output                correct output
// * @param generatedOutputs      generated output
// * @param learningRate          Multiplier to the change in the weight
// * @param numOutput             number of output
// */
//void Network::adjustLayers(int *output, std::list<int> *generatedOutputs, double learningRate, int numOutput, int *input) {
//    for (int layer = 0; layer < NUM_LAYERS; layer++) {      // Goes through all Layers
//
//        auto percep = LAYERS[layer].begin();                // Goes through each of the nodes in each layer
//        while(percep != LAYERS[layer].end()) {
//            percep->adjust(learningRate, numOutput, output, generatedOutputs, input);
//            percep++;
//        }
//
//    }
//}

/**
 * For testing purposes. Allows to set the weights of individual nodes.
 *
 * @param col   Layer the node is in
 * @param row   What node in the layer
 * @param w     Array of weight to change to
 */
void Network::setWeight(int col, int row, double *w) {
    if (col >= NUM_LAYERS) {                        // Make sure the layer exists
        return;
    }
    if (row >= NUM_NODES[col]) {
        return;
    }

    LAYERS[col][row].setWeights(w);
}




