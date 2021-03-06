/*
 * Zachary Thomas
 * 2/6/2018
 * Perceptron network to evaluate binary expressions
 */
#include <iostream>
#include <fstream>
#include "Network.h"
#include <string.h>

#define CASES 4
#define NUM_IN 2
#define NUM_OUT 1

#define NUM_LAYERS 1
using namespace std;



int** readInputs(string fileName, int cases, int numInputs);
int** readOutput(string fileName, int cases, int numOutputs);

int main(int argc, char *argv[]) {
    string file;
    if (argc == 2) {                                                    // Get the name of the file containing the correct outputs
        file = argv[1];
    } else {
        cerr << "ERROR: Invalid number of command line arguments." << endl;
        return 1;
    }

    srand(time(NULL));
    string f = "";

    int NUM_NODES[] = {1};
    Network *net = new Network(NUM_LAYERS, NUM_NODES, NUM_IN);          // Create the network
    int **inputs = readInputs("LogicInput.txt", CASES, NUM_IN);         // Read in the input
    int **outputs;

    if (file == "and") {                                                // Get the outputs from the desired file
        cout << "and:" << endl;
        outputs = readOutput("andOutput.txt", CASES, NUM_OUT);
    } else if (file == "or") {
        cout << "or:" << endl;
        outputs = readOutput("orOutput.txt", CASES, NUM_OUT);
    } else if (file == "xor") {
        cout << "xor:" << endl;
        outputs = readOutput("xorOutput.txt", CASES, NUM_OUT);
        int XORNODES[] = {2,1};
        delete(net);
        net = new Network(2, XORNODES, NUM_IN);                         // Xor has different size network
        net->displayNetwork();
    } else {
        cout << "No match" <<endl;
        return 1;
    }

    net->feedForward(inputs, outputs, CASES, NUM_IN, NUM_OUT, f);       // Run the input through the network.
    net->displayNetwork();

}

/**
 * Reads the input from a file and saves it to a 2d array.
 *
 * @param fileName      File to be read from
 * @param cases         Number of lines in the file
 * @param numInputs     Number of inputs in each line
 * @return              2d array of the input
 */
int** readInputs(string fileName, int cases, int numInputs) {
    auto **inputs =  new int*[cases];        // Creates the rows of the table
    for (int i = 0; i < cases; i++) {       // Creates space for the inputs in each row
        inputs[i] = new int[numInputs];
    }

    ifstream fileInputs;                    // Open the file
    fileInputs.open(fileName, ios::in);

    for (int row = 0; row < cases; row++) {     // Fill input table
        for (int col = 0; col < numInputs; col++) {
            fileInputs >> inputs[row][col];
        }
    }

    return inputs;
}

/**
 * Reads the desired outputs from a file and saves it.
 *
 * @param fileName File containing the outputs
 * @param cases     The number of lines of output
 *
 * @return array contianing the input
 */
int** readOutput(string fileName, int cases, int numOutput) {
    int **output = new int*[cases];
    for (int i = 0; i < cases; i++) {       // Creates space for the inputs in each row
        output[i] = new int[numOutput];
    }
    ifstream fileOutputs;
    fileOutputs.open(fileName, ios::in);
    for (int row = 0; row < cases; row++) {
        for (int col = 0; col < numOutput; col++) {
            fileOutputs >> output[row][col];
        }
    }

    return output;
}
