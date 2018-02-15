//
// Created by Craven on 2/4/2018.
//

#include <cstdlib>
#include <iostream>
#include "Perceptron.h"
#include "time.h"
using namespace std;

Perceptron::Perceptron(int inputs) {
    //TODO: regen if really close to zero
    for (int count = 0; count < inputs + 1; count++) {
        double weight = ((double) rand()/RAND_MAX) * 2 - 1;
        if (weight < 0 && weight > -1.0e-5) {
            count--;
            continue;
        } else if (weight > 0 && weight < 1.0e-5) {
            count--;
            continue;
        }
        weights.push_back(weight);
    }
}

void Perceptron::displayWeights() {
    list<double>::iterator it = weights.begin();
    while (it != weights.end()) {
        cout << (*it++) << " ";
    }
    cout << endl;
}

int Perceptron::eval(list<int> *in) {
    auto w = weights.begin();
    auto input = in->begin();
    double sum = 0;

    while (w != weights.end()) {
        sum += (*w++) * (*input++);
    }
    if (sum > 0) {
        return 1;
    } else {
        return 0;
    }
}

void Perceptron::adjust(double learningRate, int numOutput, int *output, list<int> *generatedOutput) {
    auto weightIt = weights.begin();
    list<int>::iterator outputIt;

    while (weightIt != weights.end()) {
        outputIt = generatedOutput->begin();
        outputIt++;
        for (int ndx = 0; ndx < numOutput; ndx++) {
            //printf("lr = %f, cout = %i, genOut = %i, weight = %f\n", learningRate, output[ndx], *outputIt, *weightIt);
            //printf("ADDING: %f\n",learningRate * (double) (output[ndx] - (*outputIt)) * (*weightIt));
            (*weightIt) +=  learningRate * (double) (output[ndx] - (*outputIt++)) * (*weightIt);
        }
        //printf("\n\nNODE AFTER CHANGE: %f\n\n", *weightIt);
        weightIt++;
    }
}

