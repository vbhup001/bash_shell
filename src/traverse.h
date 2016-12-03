#ifndef __TRAVERSE__H__
#define __TRAVERSE__H__

#include <vector>
#include <string>
#include "cd.h"
#include "connectorBase.h"
#include "command.h"
#include "executor.h"
#include "parenth.h"
#include "test.h"
#include <boost/tokenizer.hpp>
#include <boost/range/iterator_range.hpp>

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

bool traverse(tokenizer::iterator &it, tokenizer &tok) 
{
   
    bool update = false;
    bool parenth = false;
    bool ifP = false;
    
    string vers = "";
    string vers2 = "";
    
    while(it != tok.end()) 
    {
        string instr = "instr did not update";
        vector<string> instrs;
        
        string check;
        string tmp;
        vector<string> tmp2(1);
        
        bool IsInstr = false;
        
        tmp2.at(0) = *it;
        tmp = tmp2.at(0);
        
        if(tmp ==  "exit") 
        {
            return false;
        }
        
        if(tmp == ")") 
        {
            return update;
        }
        
        if(tmp == "(")
        {
            it++;
            update = traverse(it, tok);
            parenth = true;
        }
        
        if (parenth != true) 
        {
            if(tmp == "|") 
            {
                vers = "o";
                it++;
                tmp2.at(0) = *it;
                instr = tmp2.at(0);
                
                if(update == true && instr == "(") 
                {
                   parenthTraverse(it, tok);
                   ifP = true;
                }
                
                if(update == false && instr == "(")
                {
                    update = traverse(it, tok);
                    ifP = true;
                }
            }
            
            else if(tmp == "&") 
            {
                
                vers = "a";
                it++;
                tmp2.at(0) = *it;
                instr = tmp2.at(0);
                
                if(update == false && instr == "(") 
                {
                   parenthTraverse(it, tok);
                   ifP = true;
                }
                
                if(update == true && instr == "(") 
                {
                    update = traverse(it, tok);
                    ifP = true;
                }
            }
            
            else if (tmp == ";") 
            {
                vers = "s";
                instr = tmp;
                if(instr == "(")
                {
                    update = traverse(it, tok);
                    ifP = true;
                }
            }
            
            else 
            {
                vers = "s";
                instr = tmp;
                if(instr == "(")
                {
                    update = traverse(it, tok);
                    ifP = true;
                }
            }
            
            if (ifP == false) 
            {
                if (it != tok.end()) 
                {
                    it++;
                    if (it != tok.end())
                    {
                        tmp2.at(0) = *it;
                        tmp = tmp2.at(0);
                    }
                    else 
                    {
                        IsInstr = true;
                    }
                }
                
                if (tmp == "|" || tmp == "&" || tmp == ";") 
                {
                    IsInstr = true;
                }
                
                while (IsInstr == false) 
                {
                    if (tmp ==  "#") 
                    {
                        bool cmt = true;
                        string check;
                        
                        while(cmt) 
                        {
                            it++;
                            
                            if(it == tok.end()) 
                            {
                                    IsInstr = true;
                                    cmt = false;
                            }
                            else 
                            {
                                tmp2.at(0) = *it;
                                check = tmp2.at(0);
                                
                                if(check == "|")
                                {
                                    IsInstr = true;
                                    cmt = false;
                                }
                                if(check == "&")
                                {
                                    IsInstr = true;
                                    cmt = false;
                                }
                                if(check == ";")
                                {
                                    IsInstr = true;
                                    cmt = false;
                                }
                            }
                        } 
                    }
                    
                    else 
                    {
                        tmp2.at(0) = *it;
                        check = tmp2.at(0);
                        
                        if(check == "-" && instr != "cd")
                        {
                            cout << instr << endl;
                            ++it;
                            if(it != tok.end())
                            {
                                string str; 
                                tmp2.at(0) = *it;
                                str = tmp2.at(0);
                                check = check + str;
                            }
                        }
                        
                        if (check != "(" && check != ")" && check != "\"") 
                        {
                            instrs.push_back(check);
                        }
                        
                        it++;
                        if(it == tok.end()) 
                        {
                            IsInstr = true;
                        }
                        
                        else 
                        {
                            tmp2.at(0) = *it;
                            tmp = tmp2.at(0);
                            if (tmp == "|") 
                            {
                                IsInstr = true;
                            }
                            
                            if (tmp == "&") 
                            {
                                IsInstr = true;
                            }
                            
                            if (tmp == ";") 
                            {
                                IsInstr = true;
                                vers2 = "s";
                            }
                        }
                    }
                }
                
                Command check_input(instr, instrs);
                if (instr == "test" || instr == "[")
                {
                    update = check_test(check_input);
                    if (update) 
                    {
                        cout << "(True)" << endl;
                    }
                    else 
                    {
                        cout << "(False)" << endl;
                    }
                }
                
                if (instr == "exit") 
                {
                    return false;
                }
                if (instr == "cd")
                {
                    update = check_cd(check_input);
                    vers = vers2;
                }
                else if (vers == "s")
                {
                    update = executor(check_input);
                    vers = vers2;
                }
                else if (vers == "o")
                {
                    if (!update)
                    {
                        update = executor(check_input);
                        vers = vers2;
                    }
                    
                }
                else if (vers == "a")
                {
                    if (update)
                    {
                        update = executor(check_input);
                        vers = vers2;
                    }
                }
                if (it != tok.end())
                {
                    it++;
                }
                
            }
        }
    }
    return true;
}

bool preTraverse(string in_line)
{
    bool update = false;
    if(in_line ==  "exit")
    {
            
            //cout << "returned false";
            return false;
    }
    
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    
    tokenizer tok(in_line);
    
    tokenizer::iterator it = tok.begin();
    
    update = traverse(it, tok);
    
    return update;
}

#endif