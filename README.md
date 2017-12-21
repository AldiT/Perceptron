# Perceptron
Neural Network using implementation for Hopfield and Backpropagation Network.

# How 
There are two modes network currently works on. 1 for training mode is used to arrange weights of the network getting input from the files mentioned below.
0 for user mode which is used to read input from test.txt, reads weights from weights.txt and prints output in output.txt

# Watch out
The paths to text files used are absolute paths of my machine please be careful to change this paths to the right location of these files in your computer.

# Contents
(ignore the Hopfield classes because they are not currently used in main)
Sigmoid Function (and it's derivate form)
Math
C++ 
# training.txt
should contain data for training the backpropagation network(which is the one called and used in main) in the form input vector (some arbitrary space) expected output vector (be careful to have the same size of input/output vector as the respective number of neurons in the respective layer e.g if input vector is [2 , 3] you should have 2 input neurons in the input layers)
# weights.txt
will contain the weights written after executing in training mode(populated after training mode)
# outputs.txt 
is the file that should contain the output after executing in user mode
# test.txt
contains input vector(same as training.txt but without expected output)
