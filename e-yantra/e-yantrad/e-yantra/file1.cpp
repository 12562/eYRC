#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

class Sorting
{
      protected:
            int l,r;
      public:
             int getValue(int lrflag);
             int setValue(int lrflag,int val);
};

int Sorting::getValue(int lrflag)
{
    if(lrflag==0)
    return l;
    return r;
}

int Sorting::setValue(int lrflag,int val)
{
    if(lrflag==0)
        l=val;
    else
        r=val;
}

class Terminal: public Sorting
{
      public:
      int read(int lrflag);
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    Terminal T;
    scanf("%d",&t);
    T.setValue(0,t);
    printf("%d",T.getValue(0));
    scanf("%d",&t);
    while(t--)
    {
              
    }
    return 0;
}
