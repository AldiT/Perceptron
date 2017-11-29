//
//  Layer.hpp
//  Perceptron
//
//  Created by Aldi Topalli on 29/11/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#ifndef Layer_hpp
#define Layer_hpp

#include <stdio.h>

#define MAX_LAYERS 5
#define MAX_VECTORS 100

class Network;

class Layer
{
protected:
    int num_inputs;
    int num_outputs;
    float *outputs; //pointer to array of outputs
    float *inputs; //pointer to array of inputs, outputs of another layer
    
    friend Network;
    
public:
    virtual void calc_out() = 0;
    
    
};

class Input_Layer : public Layer
{
    
private:
    
public:
    Input_Layer(int, int);
    ~Input_Layer();
    virtual void calc_out();
    
};

class Middle_Layer;

class Output_Layer : public Layer
{
    
protected:
    float *weights;
    float *output_errors; //array of errors at output
    float *back_errors; //array of errors back-propagated
    float * expected_values; //to inputs
    
    friend Network;
    
    
public:
    
    Output_Layer(int, int);
    ~Output_Layer();
    virtual void calc_out();
    void calc_error(float&);
    void randomize_weights();
    void update_weights(const float);
    void write_weights(int, FILE *);
    void read_weights(int, FILE*);
    void list_errors();
    void list_outputs();
    void list_weights();
    
};

class Middle_Layer : public Output_Layer
{
private:
    
public:
    Middle_Layer(int , int);
    ~Middle_Layer();
    void calc_error();
    
    
};

class Network
{
private:
    
    Layer *layer_ptr[MAX_LAYERS];
    int number_of_layers;
    int layer_size[MAX_LAYERS];
    float *buffer;
    fpos_t position;
    unsigned training;
    
public:
    
    Network();
    ~Network();
    
    void set_training(const unsigned &);
    unsigned get_training_value();
    void get_layer_info();
    void set_up_network();
    void randomize_weights();
    void update_weights(const float);
    void write_weights(FILE*);
    void read_weights(FILE*);
    void list_weights();
    void write_outputs(FILE*);
    void list_outputs();
    void list_errors();
    void forward_prop();
    void backward_prop(float &);
    int fill_IObuffer(FILE*);
    void set_up_pattern(int);
    
    
    

};



#endif /* Layer_hpp */




































