#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
using namespace std;

string a="a";

string f1()
{
    return "r";
}
string f2()
{
    return "s";
}
typedef string(*ptr)();
map<string , ptr> M;
int f(string a)
{
         a.append("q");
         a.append(f1());
         cout<<a+a<<endl;
         return 0;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int t;
    M["f1"] = f1;
    M["f2"]=f2;
    string s;
    cin>>s;
    string a;
    a=M[s]();
    cout<<a<<endl;
    scanf("%d",&t);
    return 0;
}
