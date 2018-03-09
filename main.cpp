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
    if (argc == 2) {
        file = argv[1];
    } else {
        cerr << "ERROR: Invalid number of command line arguments." << endl;
        return 1;
    }

    srand(time(NULL));
    string f = "";
    int NUM_NODES[] = {1};
    Network *net = new Network(NUM_LAYERS, NUM_NODES, NUM_IN);
    net->displayNetwork();
    int **inputs = readInputs("LogicInput.txt", CASES, NUM_IN);
    int **outputs;

//    double *a = new double[3] {.3, .7, .1};
//    net->setWeight(0,0,a);
//    net->displayNetwork();

    if (file == "and") {
        cout << "and:" << endl;
        outputs = readOutput("orOutput.txt", CASES, NUM_OUT);
    } else if (file == "or") {
        cout << "or:" << endl;
        outputs = readOutput("orOutput.txt", CASES, NUM_OUT);
    } else if (file == "xor") {
        outputs = readOutput("xorOutput.txt", CASES, NUM_OUT);
        int XORNODES[] = {2,1};
        cout << "xor:" << endl;
        delete(net);
        net = new Network(2, XORNODES, NUM_IN);
        net->displayNetwork();

    } else {
        cout << "No match" <<endl;
        return 1;
    }

////    double test[] = {-.8,.5,.5};
////    net.setWeight(0,0, test);
    net->feedForward(inputs, outputs, CASES, NUM_IN, NUM_OUT, f);
//    net->displayNetwork();

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

//    cout << "\nINPUT" << endl;
//    for (int row = 0; row < cases; row++) {     // Fill input table
//        for (int col = 0; col < numInputs; col++) {
//            cout << inputs[row][col] << " " ;
//        }
//        cout << endl;
//    }
//    cout << endl;

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

//    cout << "\nout" << endl;
//    for (int row = 0; row < cases; row++) {
//        for (int col = 0; col < numOutput; col++) {
//            cout <<  output[row][col] << " ";
//        }
//        cout << endl;
//    }
//    cout << endl;
    return output;
}
