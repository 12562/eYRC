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
    //No about turning here
    return 0;
}

int pick()
{
    //code
    aboutTurn();
    path.append("p");
    return 0;
}

int Sorting::pickS(int lrFlag)
{
    //code to adjust position
   // rotate()
    pick();
    c=getValue(lrFlag);
    setValue(lrFlag,-1);
    //code to adjust position
}


int Terminal::pickT(int lrFlag)
{
    pick();
    c=getValue(lrFlag);
    setValue(lrFlag,-1);
}

int drop()
{
    //code
    path.append("d");
    return 0;
}

int Sorting::dropS(int lrFlag)
{
    //code to adjust position
    drop();
    setValue(lrFlag,c);
    c=-1;
    //code to adjust position
}

int Terminal::dropT(int lrFlag)
{
    drop();
    setValue(lrFlag,c);
    c=-1;
}

int Terminal::inT(int lrFlag)
{
    if(lrFlag==left)
    {
        TL();
    }
    else
        TR();
}
int Terminal::outT(int lrFlag)
{
    if(lrFlag==left)
    {
        LT();
    }
    else
        RT();
}

int buzzOn()
{   return 0;
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

int updateCurrPos(int value)
{
    currentPos.value=value;
    if(value<8)
    {
        currentPos.type=terminal;
        currentPos.index=value/2;
    }
    else
    {
        currentPos.type=sZone;
        currentPos.index=(value-8)/2;
    }
    currentPos.lrFlag=value%2;
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
int checkExistance(int t1 ,int t2)
{
    int angle;

    rotate(angle);
    T[t1].setValue(right,checkExistance());
    rotate(angle);
    T[t1].setValue(left,checkExistance());

    rotate(angle);
    T[t2].setValue(right,checkExistance());
    rotate(angle);
    T[t2].setValue(left,checkExistance());
    rotate(angle);
}

int optimisedRead13()
{
    int e1=-1,e3=-1;
    e1=T[0].empty();
    e3=T[2].empty();
    
    if((e1+e3)==4)
    {
        return -1;
    }
    if(e1!=both)
    {
        CT1(); // To be modified for C1 and C2
        switch(e1)
        {
            case left:
                //left deposition zone of T1 is empty
                TR();
                T[0].read(right);
                if(T[0].getValue(right)!=C[0])
                {
                    if(e3!=both)// Atleast one cargo at T3 is present so reading is required
                    {
                        T[0].pickT(right);
                        RT();
                    }
                    else
                    {
                        updateCurrPos(1);
                        return 0;
                    }
                }
                break;
            case right:
                //right deposition zone of T1 is empty
                TL();
                T[0].read(left);
                if(T[0].getValue(left)!=C[0])
                {
                    if(e3!=both)// cargo at T3 is present
                    {
                        T[0].pickT(left);
                        LT();
                    }//end of if
                    else
                    {
                        updateCurrPos(1);
                        return 0;
                    }
                }
                break;
            default:
                //No deposition of T1 is empty
                TL();
                T[0].read(left);
                LR();
                T[0].read(right);
                if(e3!=both) // More Reading has to be done
                {
                    if(T[0].getValue(right)==C[2])
                    {
                        T[0].pickT(right);
                        RT();
                    }
                    else if(T[0].getValue(left)==C[2])
                    {
                        aboutTurn();
                        RL();
                        T[0].pickT(left);
                        LT();
                    }
                    else if(T[0].getValue(right)!=C[0])
                    {
                        T[0].pickT(right);
                        RT();
                    }
                    else if(T[0].getValue(left)!=C[0])
                    {
                        aboutTurn();
                        RL();
                        T[0].pickT(left);
                        LT();
                    }
                    else
                    {
                        aboutTurn();
                        RT();
                    }
                }
                else
                {
                    updateCurrPos(1);
                    return 0;
                }
                break;
        }
        if(c!=-1)
        {
            if(c==C[2] && e3!=-1)
            {
                T1T3();
                if(e3==left)
                {
                    T[2].dropT(left);
                    aboutTurn();
                    LR();
                    T[2].read(right);
                    updateCurrPos(3);
                }
                else
                {
                    T[2].dropT(right);
                    RL();
                    T[2].read(left);
                    updateCurrPos(2);
                }
            }
            else
            {
                T1S1();
                S[0].dropS(left);
                S1T3();
                if(e3==right)
                {
                    TL();
                    T[2].read(left);
                    updateCurrPos(2);
                }
                else if(e3==left)
                {
                    TR();
                    T[2].read(right);
                    updateCurrPos(3);
                }
                else
                {
                    TL();
                    T[2].read(left);
                    aboutTurn();
                    LR();
                    T[2].read(right);
                    updateCurrPos(3);
                }
            }
        }
        else // T1 is sorted Go read blocks at T3
        {
            T1T3();
            if(e3==right)
            {
                TL();
                T[2].read(left);
                updateCurrPos(2);
            }
            else if(e3==left)
            {
                TR();
                T[2].read(right);
                updateCurrPos(3);
            }
            else
            {
                TL();
                T[2].read(left);
                aboutTurn();
                LR();
                T[2].read(right);
                updateCurrPos(3);
            }
        }
    }
    else if(e3!=both) // T1 is empty Atleast 1 block present at T3
    {
        CT3();
        if(e3==right)
        {
            TL();
            T[2].read(left);
            updateCurrPos(2);
        }
        else if(e3==left)
        {
            TR();
            T[2].read(right);
            updateCurrPos(3);
        }
        else
        {
            TL();
            T[2].read(left);
            aboutTurn();
            LR();
            T[2].read(right);
            updateCurrPos(3);
        }
    }
    return 0;
} // optimisedRead13 ends here

int nearSorted(int h1)
{
    int h2=h1+2;
    h2%=4;
    if(T[h1].hasBlock(h2))
        return -1;
    if(T[h2].hasBlock(h1))
        return -2;
    int s=h1%2;
    int l=S[s].getValue(left),r=S[s].getValue(right);
    if(l==C[h1] || l==C[h2] || r==C[h2] || r==C[h2])
        return -3;

    return 0;
}

int h1ToC()
{
    int s=currentPos.index;
    int lrFlag=currentPos.lrFlag;
    int a=T[s].getValue(lrFlag);
    int b=T[s].getValue(1-lrFlag);
    if(a!=-1 && a!=C[s])
    {
        T[s].pickT(lrFlag);
        T[s].outT(lrFlag);
    }
    else if(b!=-1 && b!=C[s])
    {
        LR();
        T[s].pickT(1-lrFlag);
        T[s].outT(1-lrFlag);
    }
    else
        T[s].outT(lrFlag);
    if(c!=-1)
    {
        if(s==0)
        {
            T1C();
        }
        else
        {
            T3C();
        }
    }
    else
    {
        int opp=T[s].oppT;
        int c=T[opp].hasBlock(C[opp]);
        int e=T[opp].empty();
        if((c+e)!=2)
        {
            T[s].outT(lrFlag);
            T1T3(); // T1T3 is equivalent to T3T1(), so same effect

            a=T[opp].getValue(lrFlag);
            
            if(a!=-1 && a!=C[opp])
            {
                T[opp].inT(lrFlag);
                T[opp].pickT(lrFlag);
                T[opp].outT(lrFlag);
            }
            else
            {
                T[opp].inT(1-lrFlag);
                T[opp].pickT(1-lrFlag);
                T[opp].outT(1-lrFlag);
            }

            if(opp==0)
            {
                T1C();
            }
            else
            {
                T3C();
            }
        }
        else
        {
            int e=S[0].empty();
            if(e!=2)
            {
                if(currentPos.index==0)
                {
                    T1S1();
                }
                else
                    T3S1();
                if(e==right)
                {
                    S[0].pickS(left);
                }
                else
                {
                    S[0].pickS(right);
                }
                S1C();
            }
            else
            {
                if(s==0)
                {
                    T1C();
                }
                else
                    T3C();
            }
        }
        
    }
}

int optimisedRead24()
{
    int t1,t2;
    if(c!=-1)
    {
        if(c==C[1])
        {
            t1=1;
        }
        else
        {
            t1=3;
        }
        t2=(t1+2)%4;
        CS2();
        S[1].dropS(left);
        S2C1();
        if(t1==1)
            checkExistance(t1,t2); //modifed later position the bot facing to either T2 T4 or S2
        else
            checkExistance(t2,t1);
        int e1,e2;
        e1=T[t1].empty();
        e2=T[t2].empty();
        if(e1==both)
        {
            C1S2();
            updateCurrPos(10);
            if(e2==both)
            return 0;
        }
        switch(e1)
        {
            case none:
                TL();
                T[t1].read(left);
                LR();
                T[t1].read(right);
                if(e2==both)
                return 0;

                if(T[t1].getValue(right)==C[t2])
                {
                    T[t1].pickT(right);
                    RT();
                }
                else if(T[t1].getValue(left)==C[t2])
                {
                    RL();
                    T[t1].pickT(left);
                    LT();
                }
                else if(T[t1].getValue(right)!=C[t1])
                {
                    T[t1].pickT(right);
                    RT();
                }
                else if(T[t1].getValue(left)!=C[t1])
                {
                    RL();
                    T[t1].pickT(left);
                    LT();
                }
                else
                {
                    RT();
                }
                break;
            default:
                C1S2();
                S[1].pickS(left);
                move(10,2*t1);
                if(e1==left)
                {
                    TL();
                    T[t1].dropT(left);
                    LR();
                    T[t1].read(right);
                    if(T[t1].getValue(right)!=C[t1])
                    {
                        T[t1].pickT(right);
                    }
                    RT();
                }
                else
                {
                    TR();
                    T[t1].dropT(right);
                    if(e1!=both)
                    {
                        LR();
                        T[t1].read(left);
                        if(T[t1].getValue(left)!=C[t1])
                        {
                            T[t1].pickT(left);
                        }
                        LT();
                    }
                    else
                        RT();
                }
                break;
        }
        if(c!=-1)
        {
            if(e2!=none)
            {
                if(c==C[t2])
                {
                    move(2*t1,2*t2);
                    if(e2==left)
                    {
                        TL();
                        T[t2].dropT(left);
                        LR();
                        T[t2].read(right);
                    }
                    else
                    {
                        TR();
                        T[t2].dropT(right);
                        if(e2!=both)
                        {
                            LR();
                            T[t2].read(left);
                        }
                    }
                    return 0;
                }
                else
                {
                    move(2*t1,10);
                    S[1].dropS(right);
                    S[1].pickS(left);
                    move(10,2*t1);
                    int lrFlag=T[t1].empty();
                    if(lrFlag==left)
                    {
                        TL();
                        T[t1].dropT(left);
                        LT();
                    }
                    else
                    {
                        TR();
                        T[t1].dropT(right);
                        RT();
                    }
                    if(e2!=both)
                    {
                        move(2*t1,2*t2);
                        if(e2==left)
                        {
                            TL();
                            T[t2].read(left);
                        }
                        else
                        {
                            TR();
                            T[t2].read(right);
                        }
                    }
                    return 0;
                }
            }
            else
            {
                move(2*t1,10);
                int lrFlag=S[1].empty();
                if(lrFlag==left)
                {
                    S[1].dropS(left);
                }
                else
                    S[1].dropS(right);
                S[1].pickS(left);
                move(10,2*t1);
                lrFlag=T[t1].empty();
                if(lrFlag==left)
                {
                    TL();
                    T[t1].dropT(left);
                    LT();
                }
                else
                {
                    TR();
                    T[t1].dropT(right);
                    RT();
                }
                move(2*t1,2*t2);
                TL();
                T[t2].read(left);
                LR();
                T[t2].read(right);
                return 0;
            }
        }
    }
    else
    {
        t1=1;t2=3;
        checkExistance(t1,t2); //modifed later position the bot facing to either T2 T4 or S2
        int e1,e2;
        e1=T[t1].empty();
        e2=T[t2].empty();
        if(e1==both)
        {
            if(e2==both)
            return 1; // to be checked a later
            CT4();
        }
        else
            CT2();
        switch(e1)
        {
            case none:
                TL();
                T[t1].read(left);
                LR();
                T[t1].read(right);
                if(e2==both)
                {
                    updateCurrPos(2*t1+right);
                    return 0;
                }
                

                if(T[t1].getValue(right)==C[t2])
                {
                    T[t1].pickT(right);
                    RT();
                }
                else if(T[t1].getValue(left)==C[t2])
                {
                    RL();
                    T[t1].pickT(left);
                    LT();
                }
                else if(T[t1].getValue(right)!=C[t1])
                {
                    T[t1].pickT(right);
                    RT();
                }
                else if(T[t1].getValue(left)!=C[t1])
                {
                    RL();
                    T[t1].pickT(left);
                    LT();
                }
                else
                {
                    RT();
                }
                break;
            case left:
                TL();
                T[t1].read(left);
                if(e2==both)
                {
                    updateCurrPos(2*t1+left);
                    return 0;
                }
                if(T[t1].getValue(left)!=C[t1])
                {
                    T[t1].pickT(left);
                }
                LT();
                break;
            case right:
                TR();
                T[t1].read(right);
                if(e2==both)
                {
                    updateCurrPos(2*t1+right);
                    return 0;
                }
                if(T[t1].getValue(right)!=C[t1])
                {
                    T[t1].pickT(right);
                }
                RT();
                break;
        }
        if(c!=-1)
        {
            if(e2!=none)
            {
                if(c==C[t2])
                {
                    move(2*t1,2*t2);
                    if(e2==left)
                    {
                        TL();
                        T[t2].dropT(left);
                        LR();
                        T[t2].read(right);
                        updateCurrPos(2*t2+right);
                    }
                    else
                    {
                        TR();
                        T[t2].dropT(right);
                        if(e2!=both)
                        {
                            LR();
                            T[t2].read(left);
                            updateCurrPos(2*t2+left);
                        }
                    }
                    return 0;
                }
                else
                {
                    move(2*t1,10);
                    int lrFlag=S[1].empty();
                    if(lrFlag==left)
                    {
                        S[1].dropS(left);
                    }
                    else
                        S[1].dropS(right);
                    if(e2!=both)
                    {
                        move(10,2*t2);
                        if(e2==left)
                        {
                            TL();
                            T[t2].read(left);
                            updateCurrPos(2*t2+left);
                        }
                        else
                        {
                            TR();
                            T[t2].read(right);
                            updateCurrPos(2*t2+right);
                        }
                    }
                    return 0;
                }
            }
            else
            {
                move(2*t1,10);
                int lrFlag=S[1].empty();
                if(lrFlag==left)
                {
                    S[1].dropS(left);
                }
                else
                    S[1].dropS(right);
                move(10,2*t2);
                TL();
                T[t2].read(left);
                LR();
                T[t2].read(right);
                updateCurrPos(2*t2+right);
                return 0;
            }
        }
        if(e1!=none)
        {
            move(2*t1,2*t2);
        }
        switch(e2)
        {
            case none:
                TL();
                T[t2].read(left);
                LR();
                T[t2].read(right);
                updateCurrPos(2*t2+right);
                break;
            case left:
                TR();
                T[t2].read(right);
                updateCurrPos(2*t2+right);
                break;
            case right:
                TL();
                T[t2].read(left);
                updateCurrPos(2*t2+left);
                break;
        }
    }
}  // optimisedRead24() ends here

int solveNear()
{
    if(nearSorted(currentPos.index)==0) // end condition
        return 0;

    int moved=0;
    if(currentPos.type==sZone)
    {
        int s=currentPos.index;
        int t=S[s].nearT;
        int lrFlag=currentPos.lrFlag;
        for(int i=0;i<2 && moved==0;i++)
        {
            if(S[s].hasBlock(C[t])!=none)
            {
                if(T[t].empty()==none)
                {
                    move(currentPos.value,2*t);
                    if(T[t].getValue(left)!=C[t])
                    {
                        TL();
                        updateCurrPos(terminal,t,left);
                    }
                    else
                    {
                        TR();
                        updateCurrPos(terminal,t,right);
                    }
                    moved=1;
                }
                else
                {
                    if(S[s].getValue(left)==C[t])
                    {
                        S[s].pickS(left);
                    }
                    else
                    {
                        S[s].pickS(right);
                    }
                    move(currentPos.value,2*t);
                    if(T[t].empty()==left)
                    {
                        TL();
                        T[t].dropT(left);
                        updateCurrPos(terminal,t,left);
                    }
                    else
                    {
                        TR();
                        T[t].dropT(right);
                        updateCurrPos(terminal,t,right);
                    }
                    moved=1;
                }
            }

            t=t+2;
            t%=4;
        }
        if(moved==0)
        {
            int opp=T[t].oppT;
            if(T[t].hasBlock(C[opp])!=none && T[opp].empty()==none)
            {
                move(currentPos.value,2*opp);
                int swap=t;
                t=opp;
                opp=swap;
            }
            else if(T[opp].hasBlock(C[t])!=none && T[t].empty()==none)
            {
                move(currentPos.value,2*t);
            }
            else if(T[t].hasBlock(C[opp])!=none)
            {
                move(currentPos.value,2*t);
            }
            else if(T[opp].hasBlock(C[t])!=none)
            {
                move(currentPos.value,2*opp);
                int swap=t;
                t=opp;
                opp=swap;
            }
            else
                return 0;

            if(T[t].getValue(left)==C[opp])
            {
                TL();
                updateCurrPos(terminal,t,left);
            }
            else
            {
                TR();
                updateCurrPos(terminal,t,right);
            }
            moved=1;
        }
        solveNear();
    }
    else
    {
        int s=currentPos.index;
        int lrFlag=currentPos.lrFlag;
        int opp=T[s].oppT;
        int sz=T[s].nearS;
        if(T[s].hasBlock(C[opp])!=none)
        {
            if(T[opp].empty()==none)
            {
                if(T[opp].hasBlock(C[s])!=none)
                {
                    if(T[s].getValue(lrFlag)==C[opp])
                    {
                        T[s].pickT(lrFlag);
                        T[s].outT(lrFlag);
                    }
                    else
                    {
                        LR();
                        T[s].pickT(1-lrFlag);
                        T[s].outT(1-lrFlag);
                    }
                    move(currentPos.value,2*sz);
                    if(S[sz].empty()==left)
                    {
                        S[sz].dropS(left);
                        updateCurrPos(sZone,sz,left);
                    }
                    else
                    {
                        S[sz].dropS(right);
                        updateCurrPos(sZone,sz,right);
                    }
                    moved=1;
                    solveNear();
                }
                else
                {
                    T[s].outT(lrFlag);
                    move(currentPos.value,2*opp);
                    if(T[opp].getValue(left)==C[s])
                    {
                        TL();
                        updateCurrPos(terminal,opp,left);
                    }
                    else
                    {
                        TR();
                        updateCurrPos(terminal,opp,right);
                    }
                    moved=1;
                    solveNear();
                }
            }
            else
            {
                if(T[s].getValue(lrFlag)==C[opp])
                {
                    T[s].pickT(lrFlag);
                    T[s].outT(lrFlag);
                }
                else
                {
                    LR();
                    T[s].pickT(1-lrFlag);
                    T[s].outT(1-lrFlag);
                }
                move(currentPos.value,2*opp);
                if(T[opp].empty()==left)
                {
                    LT();
                    T[opp].dropT(left);
                    moved=1;
                    updateCurrPos(terminal,opp,left);
                }
                else if(T[opp].empty()>=right) // right or both empty
                {
                    RT();
                    T[opp].dropT(right);
                    moved=1;
                    updateCurrPos(terminal,opp,right);
                }
                moved=1;
                solveNear();
            }
        }
        else if(T[opp].hasBlock(C[s])!=none || S[sz].hasBlock(C[s])!=none)
        {
            if(T[s].getValue(lrFlag)!=C[s] && T[s].getValue(lrFlag)!=none)
            {
                T[s].pickT(lrFlag);
                T[s].outT(lrFlag);
            }
            else if(T[s].getValue(1-lrFlag)!=C[s] && T[s].getValue(1-lrFlag)!=none)
            {
                LR();
                T[s].pickT(1-lrFlag);
                T[s].outT(1-lrFlag);
            }
            
            int t=8+2*sz;
            move(currentPos.value,t);

            if(S[sz].empty()==left)
            {
                S[sz].dropS(left);
                updateCurrPos(sZone,sz,left);
            }
            else
            {
                S[sz].dropS(right);
                updateCurrPos(sZone,sz,right);
            }
            moved=1;
        }
        else if(S[sz].hasBlock(C[opp])!=none)
        {
            T[s].outT(lrFlag);
            if(T[opp].empty()==none)
            {
                move(currentPos.value,2*opp);
                if(T[opp].getValue(right)!=C[opp])
                {
                    TR();
                    updateCurrPos(terminal,opp,right);
                }
            }
            else
            {
                move(currentPos.value,2*sz);
                if(S[sz].getValue(left)==C[opp])
                    updateCurrPos(sZone,sz,left);
                else
                    updateCurrPos(sZone,sz,right);
            }
            moved=1;
        }
    }
} // solveNear() ends here

int getTerminal(int color)
{
    for(int i=0;i<4;i++)
    {
        if(color==C[i])
            return i;
    }
}
int findNearestUnsorted()
{
    int s=currentPos.index;
    int l,r,t;
    if(currentPos.type==sZone) // may be not necessary
    {
        //checking near terminals
        t=S[s].nearT;
        for(int i=0;i<2;i++)
        {
            l=T[t].getValue(left);
            if(l!=C[t] && l!=-1)
                return 2*t+left;
            r=T[t].getValue(right);
            if(r!=C[t] && r!=-1)
                return 2*t+right;
            t=t+2;
            t%=4;
        }
        //checking far terminals
        t=S[s].farT;
        for(int i=0;i<2;i++)
        {
            l=T[t].getValue(left);
            if(l!=C[t] && l!=-1)
                return 2*t+left;
            r=T[t].getValue(right);
            if(r!=C[t] && r!=-1)
                return 2*t+right;
            t=t+2;
            t%=4;
        }
        //checking opp sorting zone
        t=1-s;
        l=S[t].getValue(left);
        if(l!=-1)
            return 8+2*t+left;
        r=T[t].getValue(right);
        if(r!=-1)
            return 8+2*t+right;
    }
    else
    {
        //checking opp terminal
        int t=T[s].oppT;
        l=T[t].getValue(left);
        if(l!=C[t] && l!=-1)
            return 2*t+left;
        r=T[t].getValue(right);
        if(r!=C[t] && r!=-1)
            return 2*t+right;

        // checking near Sorting zone
        t=T[s].nearS;
        l=S[t].getValue(left);
        if(l!=-1)
            return 8+2*t+left;
        r=T[t].getValue(right);
        if(r!=-1)
            return 8+2*t+right;

        // checking far terminals
        t=T[s].farT;
        for(int i=0;i<2;i++)
        {
            l=T[t].getValue(left);
            if(l!=C[t] && l!=-1)
                return 2*t+left;
            r=T[t].getValue(right);
            if(r!=C[t] && r!=-1)
                return 2*t+right;
            t=t+2;
            t%=4;
        }

        // checking far Sorting Zone
        t=T[s].nearS;
        l=S[t].getValue(left);
        if(l!=-1)
            return 8+2*t+left;
        r=T[t].getValue(right);
        if(r!=-1)
            return 8+2*t+right;
    }
    return -1; // arena is sorted
}

int solve()
{
    int s,t,moved=0;
    if(currentPos.type==sZone)
    {
        s=currentPos.index;
        if(S[t].empty()==left)
        {
            t=getTerminal(S[t].getValue(right));
        }
        else
        {
            t=getTerminal(S[t].getValue(left));
        }
        if(t!=-1)
        {
            move(currentPos.value,2*t);
            if(T[t].empty()==left)
            {
                TL();
                T[t].dropT(left);
                updateCurrPos(terminal,t,left);
            }
            else
            {
                TR();
                T[t].dropT(right);
                updateCurrPos(terminal,t,right);
            }
            moved=1;
        }
        else
        {
            t=findNearestUnsorted();
            if(t!=-1)
            {
                move(currentPos.value,t);
                if(t<8)
                {
                    if(t%2==left)
                        TL();
                    else
                        TR();
                }
                moved=1;
                updateCurrPos(t);
            }
        }
    }
    else
    {
        s=currentPos.index;
        int lrFlag=currentPos.lrFlag;
        if(T[s].getValue(lrFlag)!=C[s] && T[s].getValue(lrFlag)!=none)
        {
            T[s].pickT(lrFlag);
            T[s].outT(lrFlag);
        }
        else if(T[s].getValue(1-lrFlag)!=C[s] && T[s].getValue(1-lrFlag)!=none)
        {
            T[s].pickT(1-lrFlag);
            T[s].outT(1-lrFlag);
        }
        if(c!=-1)
        {
            t=getTerminal(c);
            move(currentPos.value,2*t);
            if(T[t].empty()==left)
            {
                TL();
                T[t].dropT(left);
                updateCurrPos(terminal,t,left);
            }
            else
            {
                TR();
                T[t].dropT(right);
                updateCurrPos(terminal,t,right);
            }
            moved=1;
        }
        else
        {
            t=findNearestUnsorted();
            if(t!=-1)
            {
                move(currentPos.value,t);
                if(t<8)
                {
                    if(t%2==left)
                        TL();
                    else
                        TR();
                }
                moved=1;
                updateCurrPos(t);
            }
        }
    }
    if(moved==1)
        solve();
}

int cargoSort()
{
    optimisedRead13();
    solveNear();
    h1ToC();
    optimisedRead24();
    solveNear();
    solve();
    buzz(50000);
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    init();
    readInd();
    cargoSort();
    return 0;
}

