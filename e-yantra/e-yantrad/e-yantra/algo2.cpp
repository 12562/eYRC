#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
using namespace std;

int T[4][2];
int I[4],available[4][4]={0};
int path[4][4]= { {0,160,60,160},
                  {160,0,160,60},
                  {60,160,0,160},
                  {160,60,160,0}};
int totald=0,pl,pr,tobesorted[4]={1,1,1,1};
char P[10000]={0};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int i,j,a,b;
    pl=pr=40;
    //Reading Indicators
    for(i=0;i<4;i++)
        scanf("%d",&I[i]);
    totald=25+4*20+30+4*20+60;//reading indicatos and reaching the center
    
    //reading T1
    scanf("%d%d",&a,&b);
    T[0][0]=a;
    T[0][1]=b;
    totald+=55+30+4*20;
    
    for(j=0;j<2;j++)
    {
        for(k=0;k<4;i++)
        {
            if(T[0][j]==I[k])
            available[k][0]++;
        }
    }
    if(available[0][0]==2)
        tobesorted[0]=0;
    
    scanf("%d%d",&a,&b);
    T[2].first=a;
    T[2].second=b;
    totald+=30+30+4*20;
    
    for(j=0;j<2;j++)
    {
        for(k=0;k<4;i++)
        {
            if(T[2][j]==I[k])
            available[k][2]++;
        }
    }
    if(available[2][2]==2)
        tobesorted[2]=0;
    
    //if T1 boxes is here
    while(available[2][1]!=0)
    {
        
    }
    return 0;
}
