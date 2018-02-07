//
// Created by Zach on 2/2/2018.
//
#include <iostream>
#include <fstream>
#include "Network.h"
using namespace std;

int** readInputs(string fileName, int cases, int numInputs);
int* readOutput(string fileName, int cases);

int main() {
    srand(time(NULL));
    int numNodes[1] = {1};
    Network net = Network(2, numNodes, 2);
    //net.displayNetwork();

    int **inputs = readInputs("LogicInput.txt", 4, 2);
    int *outputs = readOutput("andOutput.txt", 4);
}


int** readInputs(string fileName, int cases, int numInputs) {
    int **inputs =  new int*[cases];
    for (int i = 0; i < cases; i++) {
        inputs[i] = new int[numInputs];
    }

    ifstream fileInputs;
    fileInputs.open(fileName, ios::in);

    for (int row = 0; row < cases; row++) {
        for (int col = 0; col < numInputs; col++) {
            fileInputs >> inputs[row][col];
        }
    }

    return inputs;
}

int *readOutput(string fileName, int cases) {
    int *output = new int[cases];
    ifstream fileOutputs;
    fileOutputs.open(fileName, ios::in);
    for (int row = 0; row < cases; row++) {
        fileOutputs >> output[row];
    }

    for (int row = 0; row < cases; row++) {
        cout << output[row] << endl;
    }

    return nullptr;
}
