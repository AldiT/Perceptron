//
//  Hop.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 25/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#include "Hop.hpp"
#include <iostream>

neuron::neuron(int *j){
    int i;
    for(i=0; i<4; i++){
        weightv[i] = *(j+i);
    }
}


int neuron::act(int m, int * x){
    int i;
    int a = 0;
    
    for(i=0; i < m; i++){
        a += weightv[i]*x[i];
    }
    
    return a;
}

int network::threshhld(int k){
    if(k>0)
        return (1);
    else
        return (0);
}

network::network(int a[4], int b[4], int c[4], int d[4]){
    nrn[0] = neuron(a);
    nrn[1] = neuron(b);
    nrn[2] = neuron(c);
    nrn[3] = neuron(d);
}

void network::activation(int *patrn){
    int i, j;
    
    for(i = 0; i < 4; i++){
        for(j=0 ; j < 4; j++){
            std::cout << "\n nrn[" << i << "].weightv[" << j << "] is " << nrn[i].weightv[j];
        }
        
        nrn[i].activation = nrn[i].act(4, patrn);
        std::cout << "\nactivation is " << nrn[i].activation;
        output[i] = threshhld(nrn[i].activation);
        std::cout << "\noutput value is " << output[i] << "\n";
    }
}
































