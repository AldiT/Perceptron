//
//  main.cpp
//  Perceptron
//
//  Created by Aldi Topalli on 21/10/2017.
//  Copyright © 2017 CodeArt. All rights reserved.
//

#include "fuzzfier.hpp"


int main(){
    //Just testing this shit
    int i = 0, j=0, numcat = 0, randnum;
    
    float l, m, h, inval=1.0;
    char input[30] = "               ";
    category * ptr[10];
    float relprob[10];
    float total=0, runtotal=0;
    
    
    while (1) {
        std::cout << "Please type in category name, e.g Cool\n";
        std::cout << "Enter one word without spaces.\n";
        std::cout << "When you are done type \"done\":\n\n";
        
        ptr[i] = new category();
        std::cin >> input;
        
        if(input[0] == 'd' && input[1] == 'o' && input[2]=='n' && input[3]=='e')
            break;
        
        ptr[i]->setName(input);
        
        std::cout << "Type lowval, midval, highval.\n";
        std::cout << "For each category divided by spaces.\n";
        std::cout << "e.g 1.0 2.0 3.0\n\n";
        std::cin >> l >> m >> h;
        
        ptr[i]->setVal(l, m, h);
        
        i++;
        if(i>10)break;
    }
    
    numcat = i; //kategorite
    
    //Categories are set, Now data to fuzzify
    
    std::cout << "\n\n";
    std::cout << "==================================================";
    std::cout << "===========Fuzzifier is ready for data============\n";
    std::cout << "==================================================\n\n";
    
    
    while(1){
        std::cout << "Input data value type 0 to terminate.\n";
        
        std::cin >>inval;
        
        if(inval=0)
            break;
        
        total = 0;
        
        for(j = 0; j < numcat; j++){
            relprob[j] = 100*ptr[i]->getShare(inval);
            total += relprob[j];
        }
        
        if(total ==0){
            std::cout << "Data out of range.\n";
            exit(1);
        }
        
        randnum = randomnum((int)total);
        j=0;
        runtotal=relprob[0];
        
        while ((runtotal<randnum) && (j < numcat)) {
            j++;
            runtotal+=relprob[j];
        }
        
        std::cout << "\nOutput fuzzy category is ==> " <<
        ptr[j]->getName() << "<== \n";
        std::cout <<"category\t"<<"membership\n";
        std::cout << "−−−−−−−−−−−−−−−\n";
        for (j=0;j<numcat;j++)
        {
            std::cout << ptr[j]->getName() << "\t\t" <<
            (relprob[j]/total) <<"\n";
        }
        
        
    }
    std::cout << "\n\nAll done. Have a fuzzy day !\n";
    
    return 0;
}





































