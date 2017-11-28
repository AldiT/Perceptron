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
#include <pthread.h>

void *_print_message_function(void *ptr);

int main(int argc, char ** argv){
    pthread_t thread1, thread2;
    
    char *message1 = "Thread1";
    char *message2 = "Thread2";
    int iret1, iret2;
    
    
    iret1 = pthread_create(&thread1, NULL, _print_message_function, (void*) message1);
    iret2 = pthread_create(&thread2, NULL, _print_message_function, (void*) message2);
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Thread1 returns: %d\n", iret1);
    printf("Thread2 returns: %d\n", iret2);
    
    exit(0);
    
    /*
    int patrn1[] = {1, 0, 1, 0}, i;
    int wt1[] = {0, -5, 4, 4};
    int wt2[] = {-5, 0, 4, 4};
    int wt3[] = {4, 4, 0, -5};
    int wt4[] = {4, 4, -5, 0};
    
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
    
    */
    
    return 0;
}

void *_print_message_function(void *ptr){
    char * message = (char*) ptr;
    
    printf("The message: %s\n", message);
    return 0;
}




































