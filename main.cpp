//
// Created by Zach on 2/2/2018.
//
#include <iostream>
#include <fstream>
#include "Network.h"

#define CASES 4
#define NUM_IN 2
#define NUM_OUT 1

#define NUM_LAYERS 1
using namespace std;



int** readInputs(string fileName, int cases, int numInputs);
int** readOutput(string fileName, int cases, int numOutputs);

int main() {
    int NUM_NODES[] = {1};
    srand(time(NULL));
    Network net = Network(NUM_LAYERS, NUM_NODES, NUM_IN);
    //net.displayNetwork();

    int **inputs = readInputs("LogicInput.txt", CASES, NUM_IN);
    int **outputs = readOutput("andOutput.txt", CASES, NUM_OUT);
    string f = "and";
    net.feedForward(inputs, outputs, CASES, NUM_IN, NUM_OUT, f);
    net.displayNetwork();

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
    int **inputs =  new int*[cases];        // Creates the rows of the table
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
