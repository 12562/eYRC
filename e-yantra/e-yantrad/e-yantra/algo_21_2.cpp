/*******************************************************

Algorithm assumes 2 box placing in the sorting zones.
If can't be implemented then changes will be required.
Ain't Nobody got time fo' that.
                                   - Deepanshu Bhatia

********************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <unistd.h>
using namespace std;

class base
{
      protected:
            int l,r;
      public:
             int getValue(int lrflag);
             int setValue(int lrflag,int val);

}
int base::getValue(int lrflag)
{
    if(lrflag==0)
    return l;
    return r;
}

int base::setValue(int lrflag,int val)
{
    if(lrflag==0)
        l=val;
    else
        r=val;
}

class Sorting: public base
{
      public:
             int pick(int lrflag);
             int drop(int lrflag);
}S[2];

class Terminal: public base
{
      int nearT,farT,nearS;
      public:
             int readColorT(int lrflag);
             int pick(int lrflag);
             int drop(int lrflag);
}T[4];

struct Position
{
       int type,index,lrflag,value;
}currentPos;

int C[4]; // Correct color for T1 , T2 , T3 and T4
/*
 0      -  Black
 1      -  Red
 2      -  Green
 3      -  Blue
*/


int dist=0,c=-1;
string path;



int goStraight()
{
    //until obstruction or diversion or rotations
    //code
    path.append("S");
    return 0;
}
int turnLeft()
{
    //code
    path.append("L");
    return 0;
}
int turnRight()
{
    //code
    path.append("R");
    return 0;
}

int aboutTurn()
{
    turnLeft();
    turnLeft();
    //or a separate code for it with double delay
    return 0;
}

int goLeft()
{
    turnLeft();
    goStraight();
    return 0;
}

int goRight()
{
    turnRight();
    goStraight();
    return 0;
}

int SS()
{
    goStraight();
    goStraight();
    return 0;
}
int SLS()
{
    goStraight();
    goLeft();
    return 0;
}
int SRS()
{
    goStraight();
    goRight();
    return 0;
}

int T1C()
{
    SLS();
    return 0;
}
int T2C()
{
    SRS();
    return 0;
}
int T3C()
{
    SRS();
    return 0;
}
int T4C()
{
    SLS();
    return 0;
}

int CT1()
{
    //bot facing towards t1 and t3 side
    SRS();
    return 0;
}
int CT2()
{
    //bot facing towards t2 and t4 side
    SLS();
    return 0;
}
int CT3()
{
    //bot facing towards t1 and t3 side
    SLS();
    return 0;
}
int CT4()
{
    //bot facing towards t2 and t4 side
    SRS();
    return 0;
}

int T1T2()
{
    T1C();
    CT2();
    return 0;
}
int T1T3()
{
    SS();
    return 0;
}
int T1T4()
{
    T1C();
    CT4();
    return 0;
}
int T2T1()
{
    T2C();
    CT1();
    return 0;
}
int T2T3()
{
    T2C();
    CT3();
    return 0;
}
int T2T4()
{
    SS();
    return 0;
}
int T3T1()
{
    SS();
    return 0;
}
int T3T2()
{
    T3C();
    CT2();
    return 0;
}
int T3T4()
{
    T3C();
    CT4();
    return 0;
}
int T4T1()
{
    T4C();
    CT1();
    return 0;
}
int T4T2()
{
    SS();
    return 0;    
}
int T4T3()
{
    T4C();
    CT3();
    return 0;
}

//sorting zones
int T1S1()
{
    SRS();
    return 0;
}
int T1S2()
{
    SLS();
    SS();
    return 0;
}
int S1T1()
{
    SLS();
    return 0;
}
int S2T1()
{
    SS();
    SRS();
    return 0;
}

int T2S1()
{
    SRS();
    SS();
    return 0;
}
int T2S2()
{
    SLS();
    return 0;
}
int S1T2()
{
    SS();
    SLS();
    return 0;
}
int S2T2()
{
    SRS();
    return 0;
}

int T3S1()
{
    SLS();
    return 0;
}
int T3S2()
{
    SRS();
    SS();
    return 0;
}
int S1T3()
{
    SRS();
    return 0;
}
int S2T3()
{
    SS();
    SLS();
    return 0;
}

int T4S1()
{
    SLS();
    SS();
    return 0;
}
int T4S2()
{
    SRS();
    return 0;
}
int S1T4()
{
    SS();
    SRS();
    return 0;
}
int S2T4()
{
    SLS();
    return 0;
}

int S1S2()
{
    SS();
    SS();
    return 0;
}

int S2S1()
{
    SS();
    SS();
    return 0;
}

int TL()
{
    goLeft();
    return 0;
}
int TR()
{
    goRight();
    return 0;
}
int LT()
{
    goStraight();
    turnRight();
    return 0;
}
int RT()
{
    goStraight();
    turnLeft();
    return 0;
}

int LR()
{
    SS();
    return 0;
}

int RL()
{
    SS();
    return 0;
}

int readColor()
{
    int color=-1;
    path.append("r");
    //Color reading code goes here
    return color;
}

int readColorInd(int j)
{
    C[j]=readColor();
    return 0;
}

int Terminal::read(int lrflag)
{
    if(lrflag==0)
        l=readColor();
    else
        r=readColor();
    return 0;
}

int pick()
{
    //code
    aboutTurn();
    path.append("pU");
    return 0;
}
int drop()
{
    //code
    aboutTurn();
    path.append("dU");
    return 0;
}

int buzzOn()
{
    return 0;
}
int buzzOff()
{
    return 0;
}
int buzz(int delay)
{
    buzzOn();
    //sleep(delay);
    buzzOff();
}


int readInd()
{
    goStraight();
    
    //Read Indicator 3
    goLeft();
    readColorInd(2);
    aboutTurn();
    SS();
    
    //Read Indicator 4
    readColorInd(3);
    aboutTurn();
    goStraight();
    goRight();
    
    //Read Indicator 1
    goLeft();
    readColorInd(0);
    aboutTurn();
    SS();
    
    //Read Indicator 2
    readColorInd(1);
    aboutTurn();
    goStraight();
    goRight();
    //now in the mid point of the arena
    
    return 0;
}

int nearT(int s)
{
    return s;
}

int farT(int s)
{
    return 1-s;
}
int hasBlockS(int s,int t)
{
    if(S[s][0]==C[t])
        return 1;
    if(S[s][1]==C[t])
        return 2;
    return -1;
}

int emptyS(int t)
{
    if(S[t][0]==-1)
        return 1;
    if(S[t][1]==-1)
        return 2;
    return -1;
}

int emptyT(int t)
{
    if(T[t][0]==-1)
        return 1;
    if(T[t][1]==-1)
        return 2;
    return -1;
}

int move(int s,int t)
{
    string a=M[s]+M[t];
    string b=funcM[a]();
    path=path+a;
    updatePos(t);
}

int hasBlockOppT(int s,int t)
{
    if(T[s][0]==C[t])
        return 1;
    if(T[s][1]==C[t])
        return 2;
    return -1;
}

int solve()
{
    int moved=0;
    if(currentPos.type==sZone)
    {
        int s=currentPos.index;
        int t=nearT(s);
        while(moved==0 && t<4)
        {
            int lrFlag=hasBlock(s,t);
            if(lrFlag!=-1)
            {
                int available=emptyT(t);
                if(available!=-1)
                {
                    pickS(lrflag-1);
                    move(s,t);
                    if(available==1)
                    {
                        TL();
                        dropT();
                        moved=1;
                        updateCurrPos();
                        solve();
                    }
                    else
                    {
                        TR();
                        dropT();
                        moved=1;
                        updateCurrPos();
                        solve();
                    }
                }
            }
            t=t+2;
        }
        if(moved==0)
        {
            
        }
    }
    else
    {
        int s=currentPos.index;
        int t=hasBlockOppT(s,(s+2)%4);
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    
    
    return 0;
}
