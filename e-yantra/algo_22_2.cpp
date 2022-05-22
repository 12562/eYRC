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

#include "functions.cpp"

using namespace std;

int solveNear13();
int solveNear24(int start);


int dist=0,c=-1;

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

int Terminal::read(int lrFlag)
{
    if(lrFlag==left)
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

int Sorting::pickS(int t)
{
}


int Terminal::pickT(int lrFlag,int sameT)
{
    if(sameT==0)
    {
        if(lrFlag==left)
        {
            TL();
            pick();
            LT();
        }
        else
        {
            TR();
            pick();
            RT();
        }
    }
    else
    {
        if(currentPos.lrFlag!=lrFlag)
        {
            aboutTurn();
            SS();
        }
        pick();
        if(lrFlag==left)
            LT();
        else
            RT();
    }
}

int drop()
{
    //code
    path.append("d");
    return 0;
}

int Sorting::dropS(int lrflag)
{
}

int Terminal::dropT(int lrflag)
{
    drop();
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


int move(int s,int t)
{
    
    string a=M[s]+M[t];
    funcM[a]();
    path=path+a;
}


int init()
{
      for(int i=0;i<4;i++)
      {
          T[i].setValue(left,-1);
          T[i].setValue(right,-1);
          T[i].nearS=i%2;
          T[i].oppT=(i+2)%4;
          T[i].farT=(i+1)%4;
      }
      for(int i=0;i<2;i++)
      {
          S[i].setValue(left,-1);
          S[i].setValue(right,-1);
          S[i].nearT=i;
          S[i].farT=1-i;
      }
      
      //Storing Pointers to the functions to call
      funcM["T1T2"]=T1T2;
      funcM["T1T3"]=T1T3;
      funcM["T1T4"]=T1T4;
      funcM["T1S1"]=T1S1;
      funcM["T1S2"]=T1S2;

      funcM["T2T1"]=T2T1;
      funcM["T2T3"]=T2T3;
      funcM["T2T4"]=T2T4;
      funcM["T2S1"]=T2S1;
      funcM["T2S2"]=T2S2;

      funcM["T3T1"]=T3T1;
      funcM["T3T2"]=T3T2;
      funcM["T3T4"]=T3T4;
      funcM["T3S1"]=T3S1;
      funcM["T3S2"]=T3S2;

      funcM["T4T1"]=T4T1;
      funcM["T4T2"]=T4T2;
      funcM["T4T3"]=T4T3;
      funcM["T4S1"]=T4S1;
      funcM["T4S2"]=T4S2;

      funcM["S1T1"]=S1T1;
      funcM["S1T2"]=S1T2;
      funcM["S1T3"]=S1T3;
      funcM["S1T4"]=S1T4;
      funcM["S1S2"]=S1S2;

      funcM["S2T1"]=S2T1;
      funcM["S2T2"]=S2T2;
      funcM["S2T3"]=S2T3;
      funcM["S2T4"]=S2T4;
      funcM["S2S1"]=S2S1;

      return 0;
}

int updateCurrPos(int type,int index,int lrFlag)
{
    currentPos.type=type;
    currentPos.index=index;
    currentPos.lrFlag=lrFlag;
    currentPos.value=8*type+2*index+lrFlag;
    return 0;
}

int sorted()
{
    for(int i=0;i<4;i++)
    {
       int l=T[i].getValue(left),r=T[i].getValue(right);
       if(l!=C[i] && l!=-1)
           return -1;
       if(r!=C[i] && r!=-1)
           return -1;
    }
    for(int i=0;i<2;i++)
    {
       int l=S[i].getValue(left),r=S[i].getValue(right);
       if(l!=-1)
           return -1;
       if(r!=-1)
           return -1;
    }
    return 0;
}

int checkExistance()
{
    int present;
    //code return 0 if present and -1 if absent;
    return present;
}
int rotate(int angle)
{
}
int checkExistanceAll()
{
    int angle;

    rotate(angle);
    T[0].setValue(right,checkExistance());
    rotate(angle);
    T[0].setValue(left,checkExistance());

    rotate(angle);
    T[2].setValue(right,checkExistance());
    rotate(angle);
    T[2].setValue(left,checkExistance());
    
    rotate(angle);
    T[3].setValue(right,checkExistance());
    rotate(angle);
    T[3].setValue(left,checkExistance());
    
    rotate(angle);
    T[1].setValue(right,checkExistance());
    rotate(angle);
    T[1].setValue(left,checkExistance());

    rotate(angle);
}

int solveNear13()
{
    int e1,e2;
    e1=T[0].getValue(left)+T[0].getValue(right);
    e2=T[2].getValue(left)+T[2].getValue(right);
    
    if(e1+e2==-4)
    {
        solveNear24(0);
    }
}
int solveNear24(int start)
{
}

int solve()
{
    if(sorted()==0)
    {
        buzz(50000);
        exit(1);
    }
    int moved=0;
    if(currentPos.type==sZone)
    {
        int s=currentPos.index;
        int t=S[s].nearT;
        for(int i=0;i<2 && moved==0;i++)
        {
            int lrFlag=S[s].hasBlock(C[t]);
            if(lrFlag!=-1)
            {
                int available=T[t].empty();
                if(available!=-1)
                {
                    S[s].pickS(lrFlag-1);
                    move(currentPos.value,2*t+available-1);
                    if(available==left)
                    {
                        TL();
                        T[t].dropT(left);
                        moved=1;
                        updateCurrPos(terminal,t,0);
                        solve();
                    }
                    else
                    {
                        TR();
                        T[t].dropT(right);
                        moved=1;
                        updateCurrPos(terminal,t,1);
                        solve();
                    }
                }
            }
            t=(t+2)%4;
        }
        if(moved==0)
        {
            
        }
    }
    else
    {
        int s=currentPos.index;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    init();
    readInd();
    return 0;
}
