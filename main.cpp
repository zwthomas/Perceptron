//
// Created by Zach on 2/2/2018.
//
#include <iostream>
#include "Perceptron.h"
using namespace std;

int main() {
    cout << "Hello, world" << endl;
    Perceptron p = Perceptron(3);
    p.displayWeights();
}

