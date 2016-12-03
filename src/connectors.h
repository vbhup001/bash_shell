#ifndef __CONNECTORS__H__
#define __CONNECTORS__H__

#include "connectorBase.h"

class And : public connectorBase 
{
    
    string symbol = "&&"; 
    
    public: 
        virtual void connecting() {}

};

class Or : public connectorBase 
{
    
    string symbol = "||";
    
    public: 
        virtual string connecting() 
        {
            return symbol;
        }

};

class Semi : public connectorBase 
{
    
    string symbol = ";"; 
    
    public: 
        virtual void connecting() {}

};

#endif