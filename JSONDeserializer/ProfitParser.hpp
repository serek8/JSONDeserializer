//
//  ProfitParser.hpp
//  test
//
//  Created by Jan Seredynski on 02/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef ProfitParser_hpp
#define ProfitParser_hpp

#include <stdio.h>
#include <memory>
#include "Profits.hpp"
#include "Parser.hpp"
#include "DogParser.hpp"


class ProfitParser:private Parser, public Profits
{

    
public:
    ProfitParser(Parser &parser)
    :Parser(parser)
    ,Profits(parse<typeof(a_)>("a"),
             parse<typeof(b_)>("b"),
             parse<typeof(c_)>("c"),
             parse<typeof(d_)>("d"),
             parse<typeof(my_plug_ins_)>("my-plug-ins"),
             parse<typeof(DogParser)>("dog"),
             parse<typeof(isBool_)>("isBool"))
    {
    }
    

    
};






#endif /* ProfitParser_hpp */
