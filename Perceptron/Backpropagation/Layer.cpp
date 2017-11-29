//
//  Layer.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 29/11/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Layer.hpp"

inline float squash(float input){
    //squashing function , i will use sigmoid
    //you can use anything you want add bias if you want to
    if(input < -50)
        return 0.0;
    else if(input > 50)
        return 1.0;
    else
        return (1/(1+exp(-(double)input)));//return sigmoid value for function between -50:50
}

inline float randomweight(unsigned init){
    /*
     Random number generator will return a number between -1 and 1
     */
    
    int num;
    if(init == 1)
        srand((unsigned) time(NULL));
    
    num = rand()%100;
    return 2*(float(num/100.0))-1;
}


//Link the appropriate functions for fscanf floating point formats

static void force_fpf(){
    
    float x, *y;
    y = &x;
    x = *y;
}

//--------------------------------------------------------------------------------------------
//                                  INPUT_LAYER
//--------------------------------------------------------------------------------------------

Input_Layer::Input_Layer(int i, int o){
    num_inputs = i;
    num_outputs = o;
    outputs = new float[num_outputs];
    if(outputs == 0){
        std::cerr << "Not enough memory, you need to choose a smaller architecture and run again!\n";
        exit(1);
    }
}

Input_Layer::~Input_Layer(){
    delete[] outputs;
}

void Input_Layer::calc_out(){
    //TO DO
}

//--------------------------------------------------------------------------------------------
//                                  OUTPUT_LAYER
//--------------------------------------------------------------------------------------------


Output_Layer::Output_Layer(int i, int o){
    num_inputs = i;
    num_outputs = o;
    weights = new float[num_inputs*num_outputs];
    output_errors = new float[num_outputs];
    back_errors = new float[num_inputs];
    outputs = new float[num_outputs];
    expected_values = new float[num_outputs];
    
    if(weights == 0 || output_errors == 0 || back_errors == 0 ||
       outputs == 0 || expected_values == 0){
        std::cerr << "Not enough memory, choose a smaller architecture and run again!\n";
        exit(1);
    }
}

Output_Layer::~Output_Layer(){
    delete[] weights;
    delete[] output_errors;
    delete[] back_errors;
    delete[] outputs;
    delete[] expected_values;
}

void Output_Layer::calc_out(){
    int i, j, k;
    
    float accumulator = 0.0;
    
    for(j = 0; j < num_outputs; j++){
        for(i = 0 ; i < num_inputs; i++){
            k = i*num_outputs;
            if(weights[k+j]*weights[k+j] > 1000000.0){
                std::cerr << "Weights are getting to big to handle try a smaller\n"
                          << "try a smaller constat. e.g beta = 0.02\n"
                          << "[[ABORTING]]\n";
                exit(1);
            }
            outputs[j]=weights[k+j]*(*(inputs+i));
            accumulator+=outputs[j];
        }
        outputs[j] = squash(accumulator);
        accumulator = 0;
    }
}

void Output_Layer::calc_error(float & error){
    int i, j, k;
    float accumulator = 0.0;
    float total_error = 0.0;
    
    for(j = 0; j < num_outputs; j++){
        output_errors[j] = expected_values[j] - outputs[j];
        total_error += output_errors[j];
    }
    error = total_error;
    
    for(i = 0; i < num_inputs; i++){
        k = i*num_outputs;
        for(j = 0; j < num_outputs; j++){
            back_errors[i] = weights[k+j]*output_errors[j];
            accumulator += back_errors[i];
        }
        
        back_errors[i] = accumulator;
        accumulator = 0;
        //now we need to multiply by the derivative of sigmoid function which is like below
        back_errors[i] *= (*(inputs+i)*(1- *(inputs+i)));
    }
    
}

//TO DO: the rest of the network (Too tired tonight)





























