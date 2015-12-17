//
//  Dog.hpp
//  test
//
//  Created by Jan Seredynski on 08/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef Dog_hpp
#define Dog_hpp

#include <stdio.h>
#include <string>



class Dog
{
    
public:
    Dog(int age, std::string name)
    :age_(age)
    ,name_(name)
    {
        
    }
    
    int age_;
    std::string name_;
    
    
    Dog()
    {
        age_=99;
        name_="qqq";
    }
};



#endif /* Dog_hpp */
