//
//  fuzzfier.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 20/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#include "fuzzfier.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

void category::setName(char * n){
    strcpy(name, n);
}

char* category::getName(){
    return name;
}

void category::setVal(float & low, float & mid, float & high){
    lowval = low;
    midval = mid;
    highval = high;
}

float category::getLowval(){return lowval;}

float category::getMidval(){return midval;}

float category::getHighval(){return highval;}

//This function returns the membership of an input
float category::getShare(const float & input){
    float output;
    float midlow, highmid;
    
    midlow = midval-lowval;
    highmid = highval-midval;
    
    if(input < lowval || input > highval){
        output = 0;
    }else{
        if(input > midval){
            output = (highval-input)/highmid;
        }else if(input == midval)
            output = 1.0f;
        else
            output = (input- lowval)/midlow;
    }
    
    return output;
}

int randomnum(int maxval){
    srand((unsigned)time(NULL));
    return rand()%maxval;
}
























