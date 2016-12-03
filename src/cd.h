#ifndef __CD__H__
#define __CD__H__

#include <iostream>
#include <string>
#include <vector> 
#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>

bool check_cd(Command &cd_cmd) 
{
    
    if (cd_cmd.pull_command() == "cd") 
    {
        int num;
        string next_dir = cd_cmd.pull_dir();

        if (next_dir == "") {
            
            num = chdir(getenv("HOME"));
            if (num < 0) 
            {
                perror("cd");
                return false;
            }
            setenv("OLDPWD",getenv("PWD"), 1);
            setenv("PWD",getenv("HOME"), 1);
        }
        
        else if (next_dir == "-") 
        {
            char * dir;
            dir = (char*)malloc(sizeof(char) * strlen(getenv("PWD")));
            strcpy(dir,getenv("PWD"));
            num = chdir(getenv("OLDPWD"));
            
            if (num < 0) 
            {
                perror("cd");
                return false;
            }
            
            setenv("PWD",getenv("OLDPWD"), 1);
            setenv("OLDPWD", dir, 1);
            
        } 
        else 
        {
            num = chdir(next_dir.c_str());
            
            if (num < 0) 
            {
                perror("cd");
                return false;
            }
            setenv("OLDPWD",getenv("PWD"), 1);
            char tmp[4096];
            setenv("PWD", (getcwd(tmp, 4096) ? string(tmp) : string("")).c_str(), 1);
        }
        if (num < 0) 
        {
            perror("cd");
            return false;
        }
        return true;
    }
    return false;
}

#endif
