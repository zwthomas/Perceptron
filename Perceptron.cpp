/*
 * Zachary Thomas
 * 2/6/2018
 * Perceptron network to evaluate binary expressions
 */

#include <cstdlib>
#include <iostream>
#include "Perceptron.h"
#include <math.h>
using namespace std;

/**
 * Constructor for the perceptron. Randomly generates the weights for all its inputs.
 *
 * @param inputs   the number of inputs into the node
 */
Perceptron::Perceptron(int inputs) {
    weights = new double[inputs];
    for (int count = 0; count < inputs; count++) {
        double weight = ((double) rand()/RAND_MAX) * 2 - 1;
        if (weight < 0 && weight > -1.0e-5) {                   // Regenerate if close to zero
            count--;
            continue;
        } else if (weight > 0 && weight < 1.0e-5) {
            count--;
            continue;
        }
        weights[count] = weight;
    }
    numWeights = inputs;
}

/**
 * Displays the weights in the perceptron for debugging purposes.
 */
void Perceptron::displayWeights() {
    for (int ndx = 0; ndx < numWeights; ndx++) {
        cout << weights[ndx] << " ";
    }
    cout << endl;
}

/**
 * Evaluates the given inputs at the node.
 *
 * @param in    list of input values
 * @return      1 or -1
 */
double Perceptron::eval(double *inputs) {
    double sum = 0;
    for (int ndx = 0; ndx < numWeights; ndx++) {
        sum += weights[ndx] * inputs[ndx];
        cout << "sum " << sum << " weights "<< weights[ndx] << " input "<< inputs[ndx] << endl;
    }
    cout << "sum " << sum << endl;
    cout <<"exp " << exp(-1 *  sum) << endl;

    return 1 / (1 + exp(-1 *  sum));
}
double Perceptron::getWeight(int weightNdx) {
    return weights[weightNdx];
}

int Perceptron::numWeight() {
    return numWeights;
}

void Perceptron::setWeight(int weightNdx, double w) {
    weights[weightNdx] = w;
}

///**
// * Adjusts the weights in the perceptron by lr(correctOut - genOut)weight
// *
// * @param learningRate          Multiplier to the change in the weight
// * @param numOutput             Number of outputs generated
// * @param output                Correct output
// * @param generatedOutput       Gen output
// */
//void Perceptron::adjust(double learningRate, int numOutput, int *output, list<int> *generatedOutput, int *input) {
//    DEBUG_PRINT("ENTERED ADJUST \nLR: " << learningRate << " NUMOUT: " << numOutput)
//    auto weightIt = weights.begin();
//    list<int>::iterator outputIt;
//    int ndx = 0;
//    int in;
//    while (weightIt != weights.end()) {             // For each of the weights
//        outputIt = generatedOutput->begin();
//        outputIt++;
//
//        if (ndx == 0) {
//            in = 1;
//        } else {
//            in = input[ndx - 1];
//        }
//        ndx++;
//
//        for (int ndx = 0; ndx < numOutput; ndx++) { // Adjust for each of the outputs
//            DEBUG_PRINT("LR: " << learningRate << " CORRECTOUT: " << output[ndx] <<  " GENOUT: " << (*outputIt) << " input: " << in)
//            (*weightIt) +=  learningRate * (double) (output[ndx] - (*outputIt++)) * (in);
//            if (*weightIt > 1) {
//                *weightIt = 1;
//            } else if (*weightIt < 0 && *weightIt < -1) {
//                *weightIt = -1;
//            }
//        }
//        weightIt++;
//    }
//}
//
/**
 * For testing purposes allow the weights of a perceptron to be set.
 *
 * @param w         Array of the weights
 */
void Perceptron::setWeights(double *w) {
   for (int ndx = 0; ndx < numWeights; ndx++) {
       weights[ndx] = w[ndx];
   }
}







