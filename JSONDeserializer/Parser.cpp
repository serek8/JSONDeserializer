//
//  Parser.cpp
//  test
//
//  Created by Jan Seredynski on 02/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#include "Parser.hpp"

std::string Parser::parse_number()
{
    std::string number;
    while(*source_=='0' || *source_=='1' || *source_=='2' || *source_=='3' || *source_=='4' ||
          *source_=='5' || *source_=='6' || *source_=='7' || *source_=='8' || *source_=='9' || *source_=='.' || *source_=='-' )
    {
        number.append(source_, 1);
        move_to_next_char();
    }
    return number;
}



template <>
int Parser::parse_primary<int>()
{
    try {
        return std::stoi(parse_number());
    } catch (...) {
        throw_error_for_symbol();
    }
    return 0;
}



template <>
float Parser::parse_primary<float>()
{
    float number;
    try {
        number = std::stof(parse_number());
    } catch (...) {
        throw_error_for_symbol();
    }
    return number;
}

template <>
double Parser::parse_primary<double>()
{
    double number;
    
    try {
        number = std::stod(parse_number());
    } catch (...) {
        throw_error_for_symbol();
    }
    return number;
}


//template <>
//unsigned int Parser::parse_primary<unsigned int>()
//{
//    
//    try {
//        return std::stoul(parse_number());
//    } catch (...) {
//        throw_error_for_symbol();
//    }
//    return 0;
//}


template <>
bool Parser::parse_primary()
{
    bool boolToReturn; // crucial for RVO
    

    if(*source_ == 't')
    {
        move_to_next_char();
        skip_a_mark('r');
        skip_a_mark('u');
        skip_a_mark('e');
        boolToReturn = true;
    }
    else if(*source_ == 'f')
    {
        move_to_next_char();
        skip_a_mark('a');
        skip_a_mark('l');
        skip_a_mark('s');
        skip_a_mark('e');
        boolToReturn = false;
    }
    else
    {
        throw_error_for_symbol(*source_);
    }

    return boolToReturn;
}


template<>
std::string Parser::parse_primary<std::string>()
{
    
    skip_quatation_mark();
    std::string text;
    while(*source_ != '\0')
    {
        if(*source_ == '\"' and *(source_-1) != '\\') break;
        
        text.append(source_, 1);
        move_to_next_char();
    }
    skip_quatation_mark();
    return text;
}


void Parser::go_to_key(const char *key_name)
{
    if(!isFirstIteration_)
    {
        skip_white_spaces();
        skip_coma();
    }
    else isFirstIteration_ = false;
    skip_white_spaces();
    skip_quatation_mark();
    
    
    while (*key_name != '\0' and *source_ != '\0')
    {
        if (*key_name != *source_) throw_error_for_symbol(*source_);
        move_to_next_char();
        ++key_name;
    }
    
    skip_quatation_mark();
    skip_white_spaces();
    skip_colon();
    skip_white_spaces();
    
    
    
}

void Parser::skip_white_spaces()
{
    while(*source_==' ' || *source_=='\t' || *source_=='\n') move_to_next_char();
}
void Parser::throw_error_unsupported_object()
{
    std::string beginning_of_description("\nUnsuported object \nStarting with symbol ");
    throw std::runtime_error(beginning_of_description+
                             "\nAt position: "+std::to_string(overall_parsed_charts)+
                             "\nFollowing string: \""+std::string(source_, NUMBER_OF_CHARS_TO_DISPLAY_IN_ERROR_FIRST_CHARS)+
                             "\"\nEnd Of error");
}

void Parser::throw_error_for_symbol(char symbol )
{
    std::string beginning_of_description("\nInvalid input JSON \nStarting with symbol ");
    throw std::runtime_error(beginning_of_description+symbol+
                             "\nAt position: "+std::to_string(overall_parsed_charts)+
                             "\nFollowing string: \""+std::string(source_, NUMBER_OF_CHARS_TO_DISPLAY_IN_ERROR_FIRST_CHARS)+
                             "\"\nEnd Of error");
}

void Parser::move_to_next_char()
{
    ++overall_parsed_charts;
    ++source_;
}


