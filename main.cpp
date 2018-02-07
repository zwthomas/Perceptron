//
// Created by Zach on 2/2/2018.
//
#include <iostream>
#include "Network.h"
using namespace std;

int main() {
    srand(time(NULL));
    cout << "Hello, world" << endl;
    int numNodes[1] = {1};
    Network net = Network(2, numNodes, 2);
    net.displayNetwork();
}

