#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <unistd.h>
#include "classes.h"
using namespace std;
typedef int (*funcPtr)();
#define terminal 0
#define sZone 1
int C[4]; // Correct color for T1 , T2 , T3 and T4
/*
 0      -  Black
 1      -  Red
 2      -  Green
 3      -  Blue
*/
string path;
string M[12]={"T1","T1","T2","T2","T3","T3","T4","T4","S1","S1","S2","S2"};
map<string, funcPtr> funcM;
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

int goBack()
{
    //code
    path.append("B");
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

int S1C()
{
    SS();
    return 0;
}

int CS1()
{
    SS();
    return 0;
}
int S2C()
{
    SS();
    return 0;
}
int CS2()
{
    SS();
    return 0;
}

int S2C1()
{
    goBack();
    return 0;
}

int C1S2()
{
    goStraight();
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

