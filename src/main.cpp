#include <iostream>
#include <string>
#include <vector>
#include "traverse.h"
#include "executor.h"
#include "command.h"

using namespace std;

int main(int argc, char** argv) 
{
    do
    {
        cout << getenv("PWD") << " $ ";
        string line;
        getline(cin, line);
        if (!preTraverse(line)) 
        {
            break;
        }
    }while(1);
    
    return 0;
}



