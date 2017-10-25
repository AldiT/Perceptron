//
//  main.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 21/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#include "fuzzfier.hpp"

#include "Hop.hpp"
#include <iostream>


int main(){
    int patrn1[] = {1, 0, 1, 0}, i;
    int wt1[] = {0, -3, 3, -3};
    int wt2[] = {-3, 0, -3, 3};
    int wt3[] = {3, -3, 0, -3};
    int wt4[] = {-3, 3, -3, 0};
    
    std::cout << "THIS PROGRAM IS TO TEST THE HOPFIELD NETWORK WITH A SINGLE LAYER\n"
                << "OF 4 INTERCONNECTED NEURONS. THE NETWORK SHOULD RECALL THE \n"
                << "PATTERNS 1010 AND 0101 CORRECTLY.\n";
    
    //create the network
    //neuron contructor is called the number of parameters passed (4 times)
    network net(wt1, wt2, wt3, wt4);
    
    //give a pattern
    net.activation(patrn1);
    
    //is pattern recalled?
    
    for(i = 0; i < 4; i++){
        if(net.output[i] == patrn1[i]){
            std::cout << "\n pattern = " << patrn1[i]<< " output " << net.output[i]
            << " component matches\n";
        }else{
            std::cout << "\n pattern = " << patrn1[i]
            << " output = " << net.output[i] << " discrepancy occurred\n";
        }
    }
    
    std::cout << "\n\n";
    
    int patrn2[] = {0, 1, 0, 1};
    net.activation(patrn2);
    
    for(i = 0; i < 4; i++){
        if(net.output[i] == patrn2[i]){
            std::cout << "\n pattern = " << patrn2[i]<< " output " << net.output[i]
            << " component matches\n";
        }else{
            std::cout << "\n pattern = " << patrn2[i]
            << " output = " << net.output[i] << " discrepancy occurred\n";
        }
    }
    
    
    
    return 0;
}





































