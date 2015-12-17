//
//  User.hpp
//  test
//
//  Created by Jan Seredynski on 02/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef User_hpp
#define User_hpp

#include <stdio.h>

#include "Profits.hpp"
#include <string>
#include <memory>

class User {
    
    
public:
    
//    User()
//    :_profits(new Profits(1, 2, 3, "x", ))
//    {
//       
//    }
    
    std::string username, password;
    std::unique_ptr<Profits> _profits;
    
};



#endif /* User_hpp */
