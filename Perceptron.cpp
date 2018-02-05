//
// Created by Craven on 2/4/2018.
//

#include <cstdlib>
#include <iostream>
#include "Perceptron.h"
#include "time.h"
using namespace std;

Perceptron::Perceptron(int inputs) {
    srand(time(NULL));
    for (int count = 0; count < inputs; count++) {
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
