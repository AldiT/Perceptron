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

void Output_Layer::randomize_weights(){
    int i, j, k;
    
    const unsigned first_time = 1;
    const unsigned not_first_time = 0;
    float discard;
    
    discard = randomweight(first_time);
    
    for(i = 0; i < num_inputs; i++){
        k = i*num_outputs;
        for(j = 0; j < num_outputs; j++){
            weights[k+j] = randomweight(not_first_time);
        }
    }
}

void Output_Layer::update_weights(const float beta){
    int i, j, k;
    
    //how are we going to update weights:
    // weight_change = beta*output_error*input
    
    for(i = 0; i < num_inputs; i++){
        k = i*num_outputs;
        for(j = 0; j < num_outputs; j++){
            weights[k+j] = beta * output_errors[i]*(*(inputs+i));
        }
    }
}

void Output_Layer::list_weights(){
    int i, j, k;
    
    for(i = 0; i < num_inputs; i ++){
        k = i*num_outputs;
        
        for(j = 0; i < num_outputs; j++){
            std::cout << "weight[" << i << "," << j << "]:" << weights[k+j] << std::endl;
        }
    }
}

void Output_Layer::list_errors(){
    int i, j;
    
    std::cout << "[[Back_Errors]]" << std::endl;
    for(i = 0; i < num_inputs; i++){
        std::cout << "backerror[" << i << "]: " << back_errors[i] << std::endl;
    }
    std::cout << "[[Output_Errors]]" << std::endl;
    for(j = 0; j < num_outputs; j++){
        std::cout << "output_error[" << j << "]: " << output_errors[j] << std::endl;
    }
}

void Output_Layer::write_weights(int layer_no, FILE * weights_file_ptr){
    int i, j, k;
    
    //we assume that the file is already opened and ready for writing
    
    //we need to add the layer number to all the data rows
    // layer_no         weights[0,0], weights[0,1]...
    // layer_no         weights[1,0], weights[1,1] ....
    // layer_no         weights[2,0], weights[2,1]...
    
    for(i = 0; i < num_inputs; i++){
        k = i*num_outputs;
        fprintf(weights_file_ptr, "%i ", layer_no);
        for(j = 0; j < num_outputs; j++){
            fprintf(weights_file_ptr, "%f ", weights[k+j]);
        }
        fprintf(weights_file_ptr, "\n");
    }
}

void Output_Layer::read_weights(int layer_no, FILE * weights_file_ptr){
    int i, j, k;
    
    //we assume that the file is already opened and ready for writing
    
    //we need to add the layer number to all the data rows
    // layer_no         weights[0,0], weights[0,1]...
    // layer_no         weights[1,0], weights[1,1] ....
    // layer_no         weights[2,0], weights[2,1]...
    
    while(1){
        fscanf(weights_file_ptr, "%i", &j);
        
        if((j==layer_no) || feof(weights_file_ptr)){
            break;
        }else{
            while(fgetc(weights_file_ptr) != '\n'){
                ;//Get rest of the line
            }
        }
    }
    if(!feof(weights_file_ptr)){
        //lets keep on getting the first line
            
        i = 0;
        for(j = 0; j < num_outputs; j++){
            fscanf(weights_file_ptr, "%f", &weights[j]);
                
        }
        fscanf(weights_file_ptr, "\n");
            
        //now get the other lines
        for(i = 1; i < num_inputs; i++){
            fscanf(weights_file_ptr, "%i", &layer_no);
            k=i*num_outputs;
            for(j = 0; j < num_outputs; j++){
                fscanf(weights_file_ptr, "%f", &weights[k+j]);
            }
        }
            
        fscanf(weights_file_ptr, "\n");
    }else
        std::cout << "End of file reached!\n";
}

void Output_Layer::list_outputs(){
    int j;
    for(j = 0; j < num_outputs; j++){
        std::cout << "output[" << j << "]: " << outputs[j] << std::endl;
    }
}


//--------------------------------------------------------------------------------------------
//                                  MIDDLE_LAYER
//--------------------------------------------------------------------------------------------


Middle_Layer::Middle_Layer(int i, int o): Output_Layer(i, o){}

Middle_Layer::~Middle_Layer(){
    delete weights;
    delete output_errors;
    delete outputs;
    delete back_errors;
}

void Middle_Layer::calc_error(){
    int i, j, k;
    float accumulator = 0;
    
    for(i = 0; i < num_inputs; i++){
        k = i*num_outputs;
        for(j = 0; j < num_outputs; j++){
            back_errors[i] = weights[k+j] * (*(output_errors+j));
            accumulator += back_errors[i];
        }
        back_errors[i] = accumulator;
        accumulator = 0;
        //now we need to multiply by the derivative of sigmoid function
        //which is just input(1-input)
        back_errors[i] *= (*(inputs+i) * (1- *(inputs+i)));
    }
}

Network::Network(){
    position = 0L;
}

Network::~Network(){
    int i, j, k;
 
    i = layer_ptr[0]->num_outputs;//inputs
    j = layer_ptr[number_of_layers-1]->num_outputs;//outputs
    
    k = MAX_VECTORS;
    delete[] buffer;
}

void Network::set_training(const unsigned int & value){
    training = value;
}

unsigned Network::get_training_value(){
    return training;
}

void Network::get_layer_info(){
    int i;
    
    //----------------------------------------
    //        Get layer sized for the network
    //----------------------------------------
    
    using namespace std;
    
    cout << " Please enter in the number of layers for your network.\n";
    cout << " You can have a minimum 3 and a maximum of 5.\n";
    cout << " Three consists of one hidden layer and five consists of 3 hidden layers.\n\n";
    
    cin >> number_of_layers;
    
    cout << " Enter the layer sized separated by spaces.\n";
    cout << " For a network with 3 neurons in the input layer, \n";
    cout << " 2 neurons in the hidden layer and 4 neurons in the \n";
    cout << " output layer you would enter: 3 2 4.\n";
    cout << " You can have up to 3 hidden layers , for five maximum entries.\n\n";
    
    for(i = 0; i < number_of_layers; i++){
        cin >> layer_size[i];
    }
    
    //----------------------------------------------------------
    // size of layers:
    //  input_layer     layer_size[0]
    //  output_layer    layer_size[number_of_layers-1]
    //  middle_layer    layer_size[1]
    //                  optional: layer_size[number_of_layers-3]
    //                  optional: layer_size[number_of_layers-2]
    //----------------------------------------------------------
}

void Network::set_up_network(){
    int i, j, k;
    
    //---------------------------------
    //      Contruct the layers
    //---------------------------------
    layer_ptr[0] = new Input_Layer(0, layer_size[0]);
    
    for(i = 0; i < (number_of_layers-1); i++){
        layer_ptr[i+1] = new Middle_Layer(layer_size[i], layer_size[i+1]);
    }
    
    layer_ptr[number_of_layers-1] = new Output_Layer(layer_size[number_of_layers-2], layer_size[number_of_layers-1]);
    
    for(i = 0; i < number_of_layers-1; i++){
        if(layer_ptr[i] == 0){
            std::cout << "Not enough memory.\n";
            std::cout << "Use another architecture!\n";
            exit(1);
        }
    }
        
    //--------------------------------------------
    //          Connect the layers
    //--------------------------------------------
    //set the inputs of each layer to the output of the previous layer except the input layer
        
    for(i = 1; i < number_of_layers; i++){
        layer_ptr[i]->inputs = layer_ptr[i-1]->outputs;
    }
        
    //for backpropagation , set output_errors to next layer
    //back errors for all layers except the output layer and input layer
        
    for(i = 1; i < (number_of_layers-1); i++){
        ((Output_Layer*) layer_ptr[i])->output_errors = ((Output_Layer*)layer_ptr[i+1])->back_errors;
    }
        
    //define the IObuffer that caches data from the data file
    
    i = layer_ptr[0]->num_outputs; //inputs
    j = layer_ptr[number_of_layers-1]->num_outputs; //outputs
    k = MAX_VECTORS;
    
    buffer = new float[(i+j)*k];
    if(buffer == 0)
        std::cout << "Insuficient memory for the buffer.\n";
}

void Network::randomize_weights(){
    int i;
    for(i = 0; i < number_of_layers; i++){
        ((Output_Layer*)layer_ptr[i])->randomize_weights();
    }
}

void Network::update_weights(const float beta){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        ((Output_Layer*) layer_ptr[i])->update_weights(beta);
    }
}

void Network::write_weights(FILE * weights_file_ptr){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        ((Output_Layer*) layer_ptr[i])->write_weights(i, weights_file_ptr);
    }
}

void Network::read_weights(FILE * weights_file_ptr){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        ((Output_Layer*) layer_ptr[i])->read_weights(i, weights_file_ptr);
    }
}

void Network::list_weights(){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        std::cout << "Layer number: " << i << std::endl;
        ((Output_Layer*)layer_ptr[i])->list_weights();
    }
}

void Network::list_outputs(){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        std::cout << "Layer number: " << i << std::endl;
        ((Output_Layer*) layer_ptr[i])->list_outputs();
    }
}

void Network::write_outputs(FILE * outfile){
    int i, ins, outs;
    ins = layer_ptr[0]->num_outputs;
    outs = layer_ptr[number_of_layers-1]->num_outputs;
    
    float temp;
    
    fprintf(outfile, "for input vector:\n");
    
    for(i = 0; i < ins; i++){
        temp = layer_ptr[0]->outputs[i];
        fprintf(outfile, "%f", temp);
    }
    fprintf(outfile, "\noutput vector is:\n");
    for(i = 0; i < outs; i++){
        temp = layer_ptr[number_of_layers-1]->outputs[i];
        fprintf(outfile, "%f", temp);
    }
    
    if(training == 1){
        fprintf(outfile, "\nexpected output vector is:\n");
        for(i = 0; i < outs; i++){
            temp = ((Output_Layer*) layer_ptr[number_of_layers-1])->expected_values[i];
            fprintf(outfile, "%f", temp);
        }
        
        fprintf(outfile, "\n---------------------\n");
    }
}

void Network::list_errors(){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        std::cout << "Layer number: " << i << std::endl;
        ((Output_Layer*) layer_ptr[i])->list_errors();
    }
}

int Network::fill_IObuffer(FILE * inputfile){
    //this routine fills memory
    //with an array of input, output vectors
    //up to a maximum capacity of
    //MAX_INPUT_VECTORS_IN_ARRAY
    //the return value is the number of read vectors
    int i, k, count, veclength;
    
    int ins, outs;
    ins = layer_ptr[0]->num_outputs;
    outs = layer_ptr[number_of_layers-1]->num_outputs;
    
    if(training == 1)
        veclength = ins+outs;
    else
        veclength = ins;
    count = 0;
    
    while((count < MAX_VECTORS) && (!feof(inputfile))){
        k = count*veclength;
        
        for(i = 0; i < veclength; i++){
            fscanf(inputfile, "%f", &buffer[k+1]);
        }
        fscanf(inputfile, "\n");
        count++;
    }
    
    if(!ferror(inputfile))
        return count;
    else
        return -1;
}

void Network::set_up_pattern(int buffer_index){
    //read one vector into the network
    
    int i, k;
    int ins, outs;
    
    ins = layer_ptr[0]->num_outputs;
    outs = layer_ptr[number_of_layers-1]->num_outputs;
    
    if(training == 1)
        k = buffer_index*(ins+outs);
    else
        k = buffer_index*ins;
    
    for(i = 0; i < ins; i++){
        layer_ptr[0]->outputs[i] = buffer[k+i];
    }
    
    if(training == 1){
        for(i = 0; i < outs; i++){
            ((Output_Layer*) layer_ptr[number_of_layers-1])->expected_values[i] = buffer[k+i+ins];
        }
    }
}

void Network::forward_prop(){
    int i;
    
    for(i = 0; i < number_of_layers; i++){
        layer_ptr[i]->calc_out();
    }
}

void Network::backward_prop(float &toterror){
    int i;
    
    //error for the output layer
    ((Output_Layer*)layer_ptr[number_of_layers-1])->calc_error(toterror);
    
    for(i = number_of_layers-1; i >0; i--){
        ((Middle_Layer*)layer_ptr[i])->calc_error();
    }
}






































































