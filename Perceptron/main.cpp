//
//  backprop.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 29/11/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

//Test file for backpropagation network

#include "Backpropagation/Layer.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>

//add the absolute path (the path below is unix like)
#define TRAINING_FILE "/Users/alditopalli/Documents/aldis docs/C/Perceptron/Perceptron/training.txt"
#define WEIGHTS_FILE "/Users/alditopalli/Documents/aldis docs/C/Perceptron/Perceptron/weights.txt"
#define OUTPUT_FILE "/Users/alditopalli/Documents/aldis docs/C/Perceptron/Perceptron/output.txt"
#define TEST_FILE "/Users/alditopalli/Documents/aldis docs/C/Perceptron/Perceptron/test.txt"

int clear_cin_from_white_space(){
    char temp;
    
    while(std::cin >> temp){
        if(temp == '\n')
            continue;
        else{
            std::cin.putback(temp);
            return 0;
        }
    }
    return 0;
}

int main(int argc, char** argv){
    float error_tolerance = 0.1;
    float total_error = 0.0;
    float avg_error_per_cycle = 0.0;
    float error_last_cycle = 0.0;
    float avgerr_per_pattern = 0.0;
    float error_last_pattern = 0.0;
    float learning_parameter = 0.02;
    unsigned temp, startup;
    long int vectors_in_buffer;
    long int max_cycles;
    long int patterns_per_cycle = 0;
    
    long int total_cycles, total_patterns;
    int i;
    
    //network object of backpropagation network
    Network backp;
    
    FILE *training_file_ptr, *test_file_ptr, *data_file_ptr, *output_file_ptr, *weights_file_ptr;
    
    
    //open output file for writing
    if((output_file_ptr = fopen(OUTPUT_FILE, "w")) == NULL){
        std::cout << "Error occured while trying to open the output file.\n";
        std::cout << "Make sure the file is in place and with the right data,\nand then restart the program.\n";
        exit(1);
    }
    
    //enter the training mode: 1=training mode 0=training off
    std::cout << "\n-------------------------------------------------------------\n";
    std::cout << "                  Backpropagation Network, C++\n";
    std::cout << "                          version 1\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "To enter training mode press 1 and then enter, not to enter press 0 and then enter:\n\n";
    std::cout << "Use training to change the weights according to your\n";
    std::cout << "expected outputs.(What you wanna use the network for)\n";
    std::cout << "Your \"training.dat\" file should contain a set of inputs\n";
    std::cout << "and expected outputs for those inputs.The number of inputs\n";
    std::cout << "determines the size of the first layer(Input_Layer), while\n";
    std::cout << "the number of outputs determines the size of your Output_Layer:\n\n";
    
    clear_cin_from_white_space();
    std::cin >> temp;
    
    backp.set_training(temp);
    
    if(backp.get_training_value() == 1){
        std::cout << "Training mode is *ON*. Weights will be saved\n";
        std::cout << "in the file \"weights.dat\" at the end of the \n";
        std::cout << "current set of the input (training) data.\n\n";
    }else{
        std::cout << "Training mode is *OFF* weights will be loaded\n";
        std::cout << "from the \"weights.dat\" file and the current \n";
        std::cout << "(test) data set will be used. For the test data\n";
        std::cout << "set, \"test.dat\" file should contain only inputs\n";
        std::cout << " and no expected outputs.";
    }
    
    if(backp.get_training_value() == 1){
        //----------------------------------------------------------
        //                  Read in values for the error_tolerance
        //                      and the learning_parameter
        //----------------------------------------------------------
        
        std::cout << "Please enter in the error_tolerance\n";
        std::cout << "--- between 0.001 to 100.0, try 0.1 to start\n\n";
        std::cout << "and the learning parameter beta\n";
        std::cout << "--- between 0.01 to 1.0 try 0.5 to start\n";
        std::cout << "separate entries by a space\n";
        std::cout << "example: 0.1 0.5 sets the defaults as mentioned:\n\n";
        clear_cin_from_white_space();
        std::cin >> error_tolerance >> learning_parameter;
        
        //-----------------------------------------------------------
        //      Open training file for reading
        //-----------------------------------------------------------
        if((training_file_ptr = fopen(TRAINING_FILE, "r")) == NULL){
            std::cout << "Problem opening file for reading.";
            perror("Error");
            exit(1);
        }
        data_file_ptr = training_file_ptr; //training on
        
        //Read in the maximum number of cycles
        //each pass through the input data file is a cycle
        std::cout << "Please enter the maximum number of cycles for the simulation.\n";
        std::cout << "A cycle is one pass through the data set.\n";
        std::cout << "Try a value of 10 to start with.\n";
        clear_cin_from_white_space();
        std::cin >> max_cycles;
    }else{
        if((test_file_ptr=fopen(TEST_FILE, "r")) == NULL){
            std::cout << "Problem opening TEST_FILE.\n";
            exit(1);
        }
        
        data_file_ptr = test_file_ptr; //training off
    }
    
    //
    // training: continue looping until the total error is less than
    //            the tolerance specified, or the maximum number of
    //            cycles is exceeded; use both the forward signal propagation
    //            and the backward error propagation phases. If the error
    //            tolerance criteria is satisfied, save the weights in a file.
    // no training: just proceed through the input data set once in the
    
    //            forward signal propagation phase only. Read the starting
    //            weights from a file.
    // in both cases report the outputs on the screen
    // initialize counters
    
    total_cycles=0; // a cycle is once through all the input data
    total_patterns=0; // a pattern is one entry in the input data
    
    // get layer information
    backp.get_layer_info();
    // set up the network connections
    backp.set_up_network();
    // initialize the weights
    
    if (backp.get_training_value()==1){
        // randomize weights for all layers; there is no
        // weight matrix associated with the input layer
        // weight file will be written after processing
        // so open for writing
        if ((weights_file_ptr=fopen(WEIGHTS_FILE,"w"))==NULL){
            std::cout << "problem opening weights file\n";
            exit(1);
        }
        backp.randomize_weights();
    }else{
        // read in the weight matrix defined by a
        // prior run of the backpropagation simulator
        // with training on
        if ((weights_file_ptr=fopen(WEIGHTS_FILE,"r"))==NULL){
            std::cout << "problem opening weights file\n";
            exit(1);
        }
        backp.read_weights(weights_file_ptr);
    }
    
    // main loop
    // if training is on, keep going through the input data
    //             until the error is acceptable or the maximum number of
    //     cycles
    //             is exceeded.
    // if training is off, go through the input data once. report // outputs
    // with inputs to file output.dat
    
    
    startup=1;
    vectors_in_buffer = MAX_VECTORS; // startup condition
    total_error = 0;
    
    while (((backp.get_training_value()==1) && (avgerr_per_pattern > error_tolerance)
            && (total_cycles < max_cycles) && (vectors_in_buffer !=0))
           || ((backp.get_training_value()==0) && (total_cycles < 1))
           || ((backp.get_training_value()==1) && (startup==1))){
        startup=0;
        error_last_cycle=0; // reset for each cycle
        patterns_per_cycle=0;
        // process all the vectors in the datafile
        // going through one buffer at a time
        // pattern by pattern
        
        while(vectors_in_buffer == MAX_VECTORS){
            vectors_in_buffer = backp.fill_IObuffer(data_file_ptr);//fill buffer
            if(vectors_in_buffer < 0){
                std::cout << "Error in reading in vectors, exiting\n";
                std::cout << "check that there are no extra linefeeds\n";
                std::cout << "in your data file, and that the number \n";
                std::cout << "of layers and number of size of layers match\n";
                std::cout << "the parameters provided.\n";
                exit(1);
            }
            
            //process vectors
            for(i = 0; i < vectors_in_buffer; i++){
                //get next pattern
                backp.set_up_pattern(i);
                
                total_patterns++;
                patterns_per_cycle++;
                //forward propagate
                
                backp.forward_prop();
                if(backp.get_training_value() == 0)
                    backp.write_outputs(output_file_ptr);
                //backpropagate if appropriate
                if(backp.get_training_value() == 1){
                    backp.backward_prop(error_last_pattern);
                    error_last_cycle += error_last_pattern*error_last_pattern;
                    backp.update_weights(learning_parameter);
                    // backp.list_weights();
                    // can
                    // see change in weights by
                    // using list_weights before and
                    // after back_propagation
                    
                }
                
            }
            error_last_pattern = 0;
        }
        
        avgerr_per_pattern=((float)sqrt((double)error_last_cycle/patterns_per_cycle));
        total_error += error_last_cycle;
        total_cycles++;
        // most character displays are 26 lines
        // user will see a corner display of the cycle count
        // as it changes
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout << total_cycles << "\t" << avgerr_per_pattern << "\n";
        fseek(data_file_ptr, 0L, SEEK_SET); // reset the file pointer
        // to the beginning of
        // the file
        vectors_in_buffer = MAX_VECTORS; // reset
        
    }// end main loop
    
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "−−−−−−−−−−−−−−−−−−−−−−−−\n";
    
    std::cout << "  done:   results: in file output.dat\n";
    std::cout << "          training: the last vector only\n";
    std::cout << "          not training: full cycle \n\n";
    
    if(backp.get_training_value() == 1){
        backp.write_weights(weights_file_ptr);
        backp.write_outputs(output_file_ptr);
        avg_error_per_cycle = (float)sqrt((double)total_error/total_cycles);
        
        error_last_cycle = (float)sqrt((double)error_last_cycle);
        
        std::cout << "  weights saved in weights.dat\n\n";
        std::cout << "---->avarage error per cycle = " << avg_error_per_cycle << "<---\n";
        std::cout << "---->error last cycle = " << error_last_cycle << "<----\n";
        std::cout << "error last cycle per pattern = " << avgerr_per_pattern << "<----\n";
        
    }
    
    std::cout << "---->total cycles = " << total_cycles << "<----\n";
    std::cout << "---->total patterns = " << total_patterns << "<-----\n";
    std::cout << "---------------------------------------------------------\n\n";
    
    //close all streams
    fclose(data_file_ptr);
    fclose(weights_file_ptr);
    fclose(output_file_ptr);
    
    return 0;
}






































