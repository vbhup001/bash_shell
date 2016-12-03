#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <string>
#include <vector> 
#include <cstdlib>
#include "command.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

bool check_test(Command &val) {
    
      struct stat str_s;
      string test_str = val.pull_args();
      string path_str = val.pull_path();
      
      if(stat(path_str.c_str(), &str_s) == 0)
      {
          if (test_str == "-d") 
          {
               if(str_s.st_mode & S_IFDIR)
               {
                   return true;
               }
               return false;
          }
          if (test_str == "-f") 
          {
               if(str_s.st_mode & S_IFREG)
               {
                   return true;
               }
               return false;
          }
          else
          {
              return true;
          }
      }
      else
      {
          return false;
      }
      
}

#endif