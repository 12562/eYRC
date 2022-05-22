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
    path.append("pU");
    return 0;
}

int Sorting::pickS(int lrFlag)
{
    //code to adjust position
    pick();
    c=T[0].getValue(lrFlag);
    T[0].setValue(lrFlag,-1);
    //code to adjust position
    aboutTurn();
}


int Terminal::pickT(int lrFlag)
{
    pick();
    c=T[0].getValue(lrFlag);
    T[0].setValue(lrFlag,-1);
    aboutTurn();
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
    c=T[0].getValue(lrFlag);
    T[0].setValue(lrFlag,-1);
    //code to adjust position
}

int Terminal::dropT(int lrflag)
{
    drop();
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
                aboutTurn();
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
                    aboutTurn();
                    RL();
                    T[2].read(left);
                    updateCurrPos(2);
                }
            }
            else
            {
                T1S1();
                S[0].dropS(left);
                aboutTurn();
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
        return -1;
    
    int l=S[h1].getValue(left),r=S[h1].getValue(right);
    if(l==C[h1] || l==C[h2] || r==C[h2] || r=C[h2])
        return -1;

    return 0;
}

int h1ToC()
{
    int s=currentPos.index;
    int a=T[s].getValue(lrFlag);
    itn b=T[s].getValue(1-lrFlag);
    if(a!=-1 && a!=C[s])
    {
        T[s].pickT();
        T[s].outT(lrFlag);
    }
    else if(b!=-1 && b!=C[s])
    {
        LR();
        T[s].pickT();
        T[s].outT(1-lrFlag);
    }
    else
        outT(lrFlag);
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
        if((c+e))!=2)
        {
            T[s].outT(lrFlag);
            T1T3(); // T1T3 are equivalent to each other so same effect

            a=T[opp].getValue(lrFlag);
            
            if(a!=-1 && a!=C[s])
            {
                T[opp].inT(lrFlag);
                T[opp].pickT();
                T[opp].outT(lrFlag);
            }
            else
            {
                T[opp].inT(1-lrFlag);
                T[opp].pickT();
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
                S0C();
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
    if(c!=-1)
    {
        int a=c;
        CS2();
        S[1].dropS(left);
        S2C1();
        checkExistanceAll(); //modifed later position the bot facing to either T2 T4 or S2
        int e1,e2;
        e1=T[1].empty();
        e2=T[3].empty();
        if((e1+e2)==4)
        {
            C1S2();
            S[1].pickS(left);
            if(a==C[1])
            {
                S2T2();
                T[1].dropT(left);
            }
            else
            {  
                S2T4();
                T[3].dropT(left);
            }
            return 0;            
        }
        if(a==C[1])
        {
            switch(e1)
            {
                case -1:
                    C1T2();
                    TL();
                    T[1].read(left);
                    LR();
                    T[1].read(right);
                    break;
                default:
                    C1S2();
                    pickS(left);
                    S2T2();
                    if(e1==left)
                    {
                        TL();
                        T[1].dropT(left);
                        LR();
                        T[1].read(right);
                        if(T[1].getValue(right)!=C[1])
                        {
                            T[1].pickT(right);
                        }
                        RT();
                    }
                    else
                    {
                        TR();
                        T[1].dropT(right);
                        if(e1!=both)
                        {
                            LR();
                            T[1].read(left);
                            if(T[1].getValue(left)!=C[1])
                            {
                                T[1].pickT(left);
                            }
                            LT();
                        }
                        else
                            RT();
                    }
                    //code
                    break;
            }
            
        }
        else
            C1T4();

    }
}

int solveNear()
{
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
                        updateCurrPos(terminal,t,left);
                        solve();
                    }
                    else
                    {
                        TR();
                        T[t].dropT(right);
                        moved=1;
                        updateCurrPos(terminal,t,right);
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
        int opp=T[s].oppT;
        int lrFlag=currentPos.lrFlag;
        if(T[s].getValue(lrFlag)==C[opp])
        {
            T[s].pickT(lrFlag);
            T[s].outT(lrFlag);
        }
        else if(T[s].getValue(1-lrFlag)==C[opp])
        {
            LR();
            T[s].pickT(1-lrFlag);
            T[s].outT(1-lrFlag);
        }
        if(c!=-1)
        {
            move(currentPos.value,2*opp);
            if(T[opp].empty()==left)
            {
                LT();
                T[opp].dropT(left);
                moved=1;
                updateCurrPos(terminal,opp,left);
            }
            else if(T[opp]>=right) // right or both empty
            {
                RT();
                T[opp].dropT(right);
                moved=1;
                updateCurrPos(terminal,opp,right);
            }
            solveNear();
        }
        else
        {
            if(nearSorted()==0)
            {
                return 0;
            }

        }
    }
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

