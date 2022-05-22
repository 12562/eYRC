#ifndef BASE_H
#define BASE_H
#define none -1
#define left 0
#define right 1
#define both 2
class base
{
      protected:
            int l,r;
      public:
             int getValue(int lrflag)
             {
                 if(lrflag==left)
                     return l;
                 return r;
             }
             int setValue(int lrflag,int val)
             {
                 if(lrflag==left)
                     l=val;
                 else
                     r=val;
                 return 0;
             }
             int hasBlock(int color)
             {
                 if(l==r && l==color)
                     return both;
                 if(l==color)
                     return left;
                 if(r==color)
                     return right;
                 
                 return -1;
             }
             int empty()
             {
                 if(l==r && l==-1)
                     return both;
                 if(l==-1)
                     return left;
                 if(r==-1)
                     return right;
                 
                 return -1;
             }

};

#endif
