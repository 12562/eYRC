#ifndef TERMINAL_H
#define TERMINAL_H
#include "base.h"

class Terminal: public base
{
      public:
             int oppT,farT,nearS,farS;
             
             int read(int lrflag);
             int pickT(int lrflag);
             int dropT(int lrflag);
             int inT(int lrflag);
             int outT(int lrflag);
}T[4];

#endif
