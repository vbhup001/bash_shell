#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <iostream>
#include <string>
#include <vector> 
#include "command.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

bool executor(Command &exe_cmd)
{
     bool finish = true;
     char * arg_array [2048];
     pid_t pid = fork();
     arg_array[0] = exe_cmd.returncmd();
     unsigned i;
     
     for(i = 0; i < exe_cmd.pull_instr()->size(); i++)
     {
          arg_array[i + 1] = (char*)exe_cmd.pull_instr() -> at(i).c_str();
     }
     
     arg_array[i + 1] = '\0';
     
     int j;

     if (pid < 0) 
     { 
          perror("ERROR: forking child failed");
          finish = false;
          return finish;
          exit(-1);
     }
     
     else if (pid == 0) 
     {         
          if ((execvp(arg_array[0], arg_array)) < 0) 
          {     
               perror("ERROR: exec failed");
               finish = false;
               
               exit(1);
          }
     }
     
     else 
     {
          if(waitpid(pid, &j, 0) == -1)
          {
             perror("Waiting process failed");
             finish = false;
             return finish;
          }
          return j == 0;
         
     }
     return finish;
}

#endif