//
//  Hop.hpp
//  Perceptron
//
//  Created by Aldi Topalli on 25/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#ifndef Hop_hpp
#define Hop_hpp

#include <stdio.h>
#include <iostream>
#include <math.h>

class neuron{
protected:
    int activation;
    friend class network;
    
public:
    int weightv[4];
    neuron(){}
    neuron(int *j);
    int act(int, int*);
    
};

class network{
public:
    neuron nrn[4];//Hopfield network
    int output[4];
    
    int threshhld(int);
    void activation(int j[4]);
    network(int*, int*, int*, int*);
};




#endif /* Hop_hpp */































