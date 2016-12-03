#ifndef __COMMAND_H__
#define __COMMAND_H__

#include<iostream>
#include<cstring>
#include<string>
#include<vector>


using namespace std;


class Command
{
    protected:
        string dem;
        vector<string> instrs2;
        
    public:
        Command(string instr, vector<string> parameters)
        :  dem(instr), instrs2(parameters) {}
        
        char *returncmd()
        {
            char * cmd_point = new char[dem.length() + 1];
            strcpy(cmd_point, dem.c_str());
            return cmd_point;
        }
        
        vector<string>* pull_instr()
        {
            return &instrs2;  
        }
    
        string pull_command() 
        {
            return dem;
        }
    
        string pull_args() 
        {
            string args;
            
            if (instrs2.size() >= 1) 
            {
                args = instrs2.at(0);
            }
            return args;
        }
    
        string pull_path() 
        {
            string empty = "";
            
            for (unsigned int x = 1; x < instrs2.size(); x++) 
            {
                empty = empty + instrs2.at(x);
            }
            return empty;
        }
    
        string pull_dir() 
        {
            string empty = "";
            
            if (instrs2.size() == 0) 
            {
                return empty;
            }
            
            for (unsigned int x = 0; x < instrs2.size(); x++) 
            {
                empty = empty + instrs2.at(x);
            }
            return empty;
        }
    
};

#endif

