//
//  Profits.hpp
//  test
//
//  Created by Jan Seredynski on 02/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef Profits_hpp
#define Profits_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Dog.hpp"


class Profits
{
public:
    Profits(int a, float b, int c, std::string d, std::vector<std::string> my_plug_ins_, Dog dog, bool isBool)
    :a_(a), b_(b), c_(c), d_(d), my_plug_ins_(my_plug_ins_), dog_(dog), isBool_(isBool)
    {
    }
    
    const int a(){return a_;}
    
    
protected:
public: // only for test to make it easier to display
    int a_;
    float b_;
    int c_;
    std::string d_;
    std::vector<std::string> my_plug_ins_;
    Dog dog_;
    bool isBool_;
};



#endif /* Profits_hpp */
