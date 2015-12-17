//
//  Parser.hpp
//  test
//
//  Created by Jan Seredynski on 02/12/15.
//  Copyright © 2015 Jan Seredynski. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp
#include <string>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include "ParserStringProxy.hpp"



#define  WHITE_SPACES_AMOUNT 3
#define NUMBER_OF_CHARS_TO_DISPLAY_IN_ERROR_FIRST_CHARS 15

enum class ParsingFlag { OK=0, INVALID_INPUT, END_OF_FILE };

class Parser
{
    template<bool> struct _TPrimaryAdapter {};
    template<bool> struct _TVectorAdapter {};
    template<bool> struct _TStringProxyAdapter {};
    template<bool> struct _TParsableAdapter {};
    
public:
    
    ~Parser(){}
    Parser(const char* source)
    :source_(source)
    ,overall_parsed_charts(0)
    ,flag_(ParsingFlag::OK)
    ,isFirstIteration_(true)
    
    {
        skip_white_spaces();
        skip_start_new_scope();
        //std::cout<<source_;
    }
    

    
    
    template <typename T>
    T parse(const char *key_name)
    {
        go_to_key(key_name);
        return fun<T>(_TPrimaryAdapter<std::is_pod<T>::value ||
                                std::is_same<std::string, T>::value>());
    }

    template <typename T>
    T parse()
    {
        return fun<T>(_TPrimaryAdapter<std::is_pod<T>::value ||
                      std::is_same<std::string, T>::value>());
    }
    
    
    template<typename T> T fun(_TPrimaryAdapter<true>)
    {
        return parse_primary<T>();
    }
    template<typename T> T fun(_TPrimaryAdapter<false>)
    {
        return fun<T>(_TParsableAdapter<std::is_base_of<Parser, T>::value>());
    }
    template<typename T> T fun(_TParsableAdapter<true>)
    {
        return parse_object<T>();
    }
    template<typename T> T fun( _TParsableAdapter<false>)
    {
        
        return fun<T>(_TStringProxyAdapter<std::is_base_of<ParseStringProxy, T>::value>());
//        return fun<T>(_TStringProxyAdapter<std::is_base_of<std::vector<typename T::value_type>, T>::value>());
    }
    //
    
    template<typename T> T fun(_TStringProxyAdapter<true>)
    {
        return parse_primary<std::string>();
    }
    template<typename T> T fun(_TStringProxyAdapter<false>)
    {
//        return fun<T>(_TParsableAdapter<std::is_base_of<Parser, T>::value>());
        return fun<T>(_TVectorAdapter<std::is_same<std::vector<typename T::value_type>, T>::value>());
    }
    
    //
    template<typename T> T fun(_TVectorAdapter<true>)
    {
        return parse_vector<T>();
    }
    template<typename T> T fun( _TVectorAdapter<false>)
    {
        return parse_primary<std::string>();
        throw_error_for_symbol();
        //return T();
    }

public:
    const char* source() const
    {
        return source_;
    }
    
    
    

    template<typename T>
    T parse_primary()
    {
        
    }

    template <typename T>
    T parse_vector()
    {
        typedef  typename T::value_type value_type;
        std::vector<typename T::value_type> vector;
        skip_a_mark('[');
        
        while(*source_ != '\0')
        {
            skip_white_spaces();
            if( is_a_mark_next(']')) break;
            skip_white_spaces();

            vector.push_back(   value_type(parse<value_type>()) );
            skip_white_spaces();
            if(!is_a_mark_next(',')) break;
            skip_a_mark(',');
            skip_white_spaces();
        }
        skip_white_spaces();
        skip_a_mark(']');        
        return vector;
    }

    template <typename T>
    T parse_object()
    {
        
        skip_a_mark('{');
        isFirstIteration_ = true;
        T object(*this);
        source_  = object.source();
        isFirstIteration_ = false;
        skip_white_spaces();
        skip_a_mark('}');
        return object;
    }
    


    
private:
    
    void skip_white_spaces();
    
    
    void go_to_key(const char *key_name);

    
    std::string parse_number();
    
    
    void skip_colon()
    {
        if (*source_==':') move_to_next_char();
        else throw_error_for_symbol(':');
    }
    void skip_coma()
    {
        if (*source_==',') move_to_next_char();
        else throw_error_for_symbol(',');
    }
    void skip_start_new_scope()
    {
        if (*source_=='{') move_to_next_char();
        else throw_error_for_symbol('{');
    }
    
    void skip_end_scope()
    {
        if (*source_=='}') move_to_next_char();
        else throw_error_for_symbol('}');
    }
    
    void skip_quatation_mark()
    {
        if (*source_=='\"') move_to_next_char();
        else throw_error_for_symbol('\"');
    }
    
    inline void skip_a_mark(char mark)
    {
        if (*source_==mark) move_to_next_char();
        else throw_error_for_symbol(mark);
    }
    
    inline bool is_a_mark_next(char mark)
    {
        return (*source_==mark);
    }
    
    bool is_quotation_mark_next()
    {
        return (*source_=='\"');
    }
    
    void move_to_next_char();
    
    void throw_error_for_symbol(char symbol = ' ');
    void throw_error_unsupported_object();
    
    std::string int_to_string(int a)
    {
        return std::to_string(a);
    }
    
    ParsingFlag flag_;
    const char* source_;
    bool isFirstIteration_;
    unsigned int overall_parsed_charts;
    
};


template <>
int Parser::parse_primary<int>();

template <>
float Parser::parse_primary<float>();

template <>
double Parser::parse_primary<double>();

//template <>
//unsigned int Parser::parse_primary<unsigned int>();

template <>
bool Parser::parse_primary<bool>();

template <>
std::string Parser::parse_primary<std::string>();






#endif /* Parser_hpp */




