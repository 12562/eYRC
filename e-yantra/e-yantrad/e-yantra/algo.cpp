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

int T[4][2];

int C[4]; // Correct color for T1 , T2 , T3 and T4
/*
 0      -  Black
 1      -  Red
 2      -  Green
 3      -  Blue
*/

int S[2][2]={-1,-1,-1,-1};
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
    path.append("rU");
    aboutTurn();
    //Color reading code goes here
    return color;
}

int readColorInd(int j)
{
    C[j]=readColor();
    return 0;
}

int readColorT(int i,int j)
{
    T[i][j]=readColor();
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


int solveNear13()
{
    int f1=0,f2=0,s1=0,s2=0;
    
    CT1();
    TL();
    readColorT(0,0);
    if(T[0][0]==C[0])
    {
        f1+=1;
        buzz(500);
    }
    else if(T[0][0]==C[2])
    {
         s1+=1;
    }
    LR();
    readColorT(0,1);
    if(T[0][1]==C[0])
    {
        f1+=2;
        buzz(500);
    }
    else if(T[0][1]==C[2])
    {
         s1+=2;
    }
    switch(f1)
    {
             case 3:
                  RT();
                  T1T3();
                  break;
                  
             case 2:
                  RL();
                  pick();
                  c=T[0][0];
                  T[0][0]=-1;
                  LT();
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
                  
             case 1:
                  pick();
                  c=T[0][1];
                  T[0][1]=-1;
                  RT();
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
                  
             case 0:
                  if(s1==1)
                  {
                      RL();
                      pick();
                      c=T[0][0];
                      T[0][0]=-1;
                      LT();
                  }
                  else
                  {
                      pick();
                      c=T[0][1];
                      T[0][1]=-1;
                      RT();
                  }
                  T1S1();
                  drop();
                  S[0][0]=c;
                  c=-1;
                  S1T3();
                  break;
    }
    
    //Reading T3
    TL();
    readColorT(2,0);
    if(T[2][0]==C[2])
    {
        f2+=1;
        buzz(500);
    }
    else if(T[2][0]==C[0])
    {
         s2+=1;
    }
    LR();
    readColorT(2,1);
    if(T[2][1]==C[2])
    {
        f2+=2;
        buzz(500);
    }
    else if(T[2][1]==C[0])
    {
         s1+=2;
    }
    
    switch(f2)
    {
             case 3:
                  RT();
                  if(f1!=3)
                  {
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;
                      S1T2();
                  }
                  else
                      T3T2();
                  break;
                  
             case 2:
                  RL();
                  pick();
                  c=T[2][0];
                  T[2][0]=-1;
                  LT();
                  if(c==C[0])
                  {
                      T3T1();
                      if(f1==2)
                      {
                          TL();
                          drop();
                          T[0][0]=c;
                          c=-1;
                          LT();
                      }
                      else
                      {
                          TR();
                          drop();
                          T[0][1]=c;
                          c=-1;
                          if(f1==1)
                              RT();
                          else
                          {
                              RL();
                              pick();
                              c=T[0][0];
                              T[0][0]=-1;
                              LT();
                          }
                          
                      }
                      
                      if(S[0][0]==C[2])
                      {
                          T1S1();
                          if(c!=-1)
                          {
                              drop();
                              S[0][1]=c;
                              c=-1;
                          }
                          pick();
                          c=S[0][0];
                          S[0][0]=-1;
                          if(s1>=1)
                          {
                              S1T3();
                              TL();
                              drop();
                              T[2][0]=c;
                              c=-1;
                              LT();
                              if(S[0][1]!=-1)
                              {
                                  T3S1();
                                  pick();
                                  c=S[0][1];
                                  S[0][1]=-1;
                                  S1S2();
                                  drop();
                                  S[1][0]=c;
                                  c=-1;
                                  S2T2();
                              }
                              else
                                  T3T2();
                              
                          }
                          else
                          {
                              S1S2();
                              drop();
                              S[1][0]=c;
                              c=-1;
                              S2T2();
                          }
                      }
                      else
                      {
                          T1S2();
                          drop();
                          S[1][0]=c;
                          c=-1;
                          S2T2();
                      }
                  }
                  else if(S[0][0]==C[2])
                  {
                      T3S1();
                      drop();
                      S[0][1]=c;
                      c=-1;
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1T3();
                      TL();
                      drop();
                      T[2][0]=c;
                      c=-1;
                      LT();
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1S2();
                      drop();
                      S[1][0]=c;
                      c=-1;
                      S2T2();
                  }
                  else
                      T3T2();
                  }
                  break;
                  
             case 1:
                  pick();
                  c=T[2][1];
                  T[2][1]=-1;
                  RT();
                  if(c==C[0])
                  {
                      T3T1();
                      if(f1==2)
                      {
                          TL();
                          drop();
                          T[0][0]=c;
                          c=-1;
                          LT();
                      }
                      else
                      {
                          TR();
                          drop();
                          T[0][1]=c;
                          c=-1;
                          if(f1==1)
                              RT();
                          else
                          {
                              RL();
                              pick();
                              c=T[0][0];
                              T[0][0]=-1;
                              LT();
                          }
                          
                      }
                      
                      if(S[0][0]==C[2])
                      {
                          T1S1();
                          if(c!=-1)
                          {
                              drop();
                              S[0][1]=c;
                              c=-1;
                          }
                          pick();
                          c=S[0][0];
                          S[0][0]=-1;
                          if(s1>=1)
                          {
                              S1T3();
                              TR();
                              drop();
                              T[2][1]=c;
                              c=-1;
                              RT();
                              if(S[0][1]!=-1)
                              {
                                  T3S1();
                                  pick();
                                  c=S[0][1];
                                  S[0][1]=-1;
                                  S1S2();
                                  drop();
                                  S[1][0]=c;
                                  c=-1;
                                  S2T2();
                              }
                              else
                                  T3T2();
                              
                          }
                          else
                          {
                              S1S2();
                              drop();
                              S[1][0]=c;
                              c=-1;
                              S2T2();
                          }
                      }
                      else
                      {
                          T1S2();
                          drop();
                          S[1][0]=c;
                          c=-1;
                          S2T2();
                      }
                  }
                  else if(S[0][0]==C[2])
                  {
                      T3S1();
                      drop();
                      S[0][1]=c;
                      c=-1;
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1T3();
                      TR();
                      drop();
                      T[2][1]=c;
                      c=-1;
                      RT();
                      T3S1();
                      pick();
                      c=S[0][0];
                      S[0][0]=-1;                      
                      S1S2();
                      drop();
                      S[1][0]=c;
                      c=-1;
                      S2T2();
                  }
                  else
                      T3T2();
                  }
                  break;
                  
             case 0:
                  if(f1==3)
                  {
                      T3T2();
                  }
                  else if(s2!=0)
                  {
                       if(s2>=2)
                       {
                           pick();
                           c=T[2][1];
                           T[2][1]=-1;
                           RT();
                           T3T1();
                           if(f1==2)
                           {
                               TL();
                               drop();
                               T[0][0]=c;
                               c=-1;
                               LT();
                               if(s1>0)
                               {
                                   T1S1();
                                   pick();
                                   c=S[0][0];
                                   S[0][0]=-1;
                                   S1T3();
                                   TR();
                                   drop();
                                   T[2][1]=c;
                                   c=-1;
                                   if(f2!=1)
                                   {
                                       RL();
                                       pick();
                                       c=T[2][1];
                                       T[2][1]=-1;
                                       LT();
                                       T3S1();
                                       //incomplete
                                   }
                               }
                           }
                       }
                       else
                       {
                       }
                  }
                  break;
    }
    return 0;
}

int solve()
{
    if(currentPos.type==sZone)
    {
        int s=currentPos.index;
        int t=nearT(s);
    }
    else
    {
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    
    return 0;
}
