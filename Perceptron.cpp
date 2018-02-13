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
        weights.push_back(((double) rand()/RAND_MAX) * 2 - 1);
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
    int sum = 0;

    while (w != weights.end()) {
        sum += (*w++) * (*input++);
    }
    if (sum > 0) {
        return 1;
    } else {
        return 0;
    }
}

void Perceptron::adjust(double learningRate, int output, int correctOutput, int *in) {
    auto it = weights.begin();
    int ndx = -1, val;

    while (it != weights.end()) {
        if (ndx == -1) {
            val = 1;
        } else {
            val = in[ndx];
        }
        ndx++;

        (*it++) += learningRate * (correctOutput - output) * val;
    }
}

