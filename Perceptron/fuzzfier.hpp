//
//  fuzzfier.hpp
//  Perceptron
//
//  Created by Aldi Topalli on 20/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#ifndef fuzzfier_hpp
#define fuzzfier_hpp

#include <iostream>


class category{
private:
    char name[30];
    float lowval, midval, highval;
    
    
public:
    category(){}
    void setName(char *);
    char* getName();
    void setVal(float&, float&, float&);
    float getLowval();
    float getMidval();
    float getHighval();
    
    float getShare(const float&);
    
    
    ~category(){}
    
};

int randomnum(int);

#endif /* fuzzfier_hpp */
