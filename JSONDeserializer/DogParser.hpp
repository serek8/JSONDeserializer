//
//  DogParser.hpp
//  test
//
//  Created by Jan Seredynski on 08/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef DogParser_hpp
#define DogParser_hpp

#include <stdio.h>
#include "Dog.hpp"
#include "Parser.hpp"
#include <iostream>



class DogParser:public Parser, public Dog
{
    
    
public:
    DogParser(Parser &parser)
    :Parser(parser)
    ,Dog(parse<typeof(age_)>("age"),
         parse<typeof(name_)>("name"))

    {
    }
    
    DogParser(const DogParser&)
    :Parser(*this)
    {
        std::cout<<"Copied"; // test for copy elion  - WORKS
    }
    
    
    
    
    
};


#endif /* DogParser_hpp */
