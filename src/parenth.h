#ifndef __PARENTH__H__
#define __PARENTH__H__

#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>
#include "connectorBase.h"
#include "command.h"
#include "test.h"
#include "executor.h"
#include "traverse.h"
#include <vector>
#include <string>

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

void parenthTraverse(tokenizer::iterator &it, tokenizer &tok) 
{
    
    bool status = true;
    int count = 0;
    vector<string>tmp2(1);
    string current;
    ++it;
    
    count = 1;
    while(it != tok.end() && status)
    {
        tmp2.at(0) = *it;
        current = tmp2.at(0);
        if(current == "(")
        {
            count++; 
        }
        if(current == ")")
        {
            count--;
            if(count == 0)
            {
                status = false;
            }
        }
        ++it;
    }
    status = true;
    while(it != tok.end() && status)
    {
        tmp2.at(0) = *it;
        current = tmp2.at(0);
  
        if(current == "|" || current == ";" ||  current == ")" || current == "&")
        {
            status = false;
            break;
        }
        ++it;
    }
}

#endif