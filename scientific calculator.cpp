#include<iostream>
#include<string.h>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#define pi 2*acos(0)
using namespace std;
bool isoperand(char x)
{
    if(x>='0'&&x<='9') return true;
    else return false;
}
bool ischar(char x)
{
    if(x>='a'&&x<='z') return true;
    else return false;
}
bool isoperator(char x)
{
    if(x=='+'||x=='-'||x=='*'||x=='/'||x=='^') return true;
    else return false;
}
int order(char x)
{
    switch(x)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    case '(' :
        return 0;
    }

}
bool ishigher(char a,char b)
{
    if(order(a)>=order(b))
    return true;
    else return false;
}
string inf_postf(string infix)
{
    string postfix="";
    string stck="(";
    infix+=")";
    int i;
   for(i=0;i<infix.length();i++)
    {
        if(isoperand(infix[i])||infix[i]=='.'||ischar(infix[i]))
            postfix+=infix[i];
        else if(infix[i]=='(')
                    stck+='(';
        else if(isoperator(infix[i]))
        {
            if(postfix[postfix.length()-1]!=',')
            postfix+=',';
              while(ishigher(stck[stck.length()-1],infix[i]))
              {
                  postfix+=stck[stck.length()-1];
                   if(postfix[postfix.length()-1]!=',')
                  postfix+=',';
                   stck.resize(stck.size()-1);
              }

                if(postfix[postfix.length()-1]!=',')
                 postfix+=',';
                    stck+=infix[i];
        }
         else if(infix[i]==')')
        {
           if(postfix[postfix.length()-1]!=',')
            postfix+=',';
            while(stck[stck.length()-1]!='(')
            {
                 postfix+=stck[stck.length()-1];
                 if(postfix[postfix.length()-1]!=',')
                 postfix+=',';
                 stck.resize(stck.size()-1);
            }stck.resize(stck.size()-1);
        }
    }
    return postfix;
}
double post_eval(string post)
{
  int i,top=0; long double stck[1000],x,s=0,z=0,l=0;
     for(i=0;i<post.length();i++)
     {

         if(isoperand(post[i])&&(!ischar(post[i-1])))
         {
             s=s*10+(post[i]-'0');
         }
         else if(ischar(post[i]))
         {
             if(post[i]=='c')
             { i=i+2; int j=i+1; int d=0;
                 while(isoperand(post[j]))
                 {
                     d=d*10+post[j]-'0';
                     j++; i++;
                     if(post[j]==',') break;
                 }s=cos(d*pi/180);
             }
             if(post[i]=='s')
             { i=i+2; int j=i+1; int d=0;
                 while(isoperand(post[j]))
                 {
                     d=d*10+post[j]-'0';
                     j++; i++;
                     if(post[j]==',') break;
                 }s=sin(d*pi/180);
             }
             if(post[i]=='t')
             { i=i+2; int j=i+1; int d=0;
                 while(isoperand(post[j]))
                 {
                     d=d*10+post[j]-'0';
                     j++; i++;
                     if(post[j]==',') break;
                 }s=tan(d*pi/180);
             }
             if(post[i]=='l')
             { i=i+2; int j=i+1; int d=0;
                 while(isoperand(post[j]))
                 {
                     d=d*10+post[j]-'0';
                     j++; i++;
                     if(post[j]==',') break;
                 }s=log10(d);
             }
         }
         else if(post[i]=='.')
         {int j=i+1; int f=1; z=0;
             while(isoperand(post[j]))
             {
                 z=z+(post[j]-'0')/(pow(10,f));
                 j++; f++; i++;
                 if(post[j]==',') break;
             } s=s+z;
         }
        else if(post[i]==','&&isoperand(post[i-1]))
        {
        top++;   stck[top]=s;  s=0;
        }

         else if(post[i]=='+')
         {
             x=stck[top-1]+stck[top];
             top=top-2;
             top++;
             stck[top]=x;
         }
         else if(post[i]=='-')
         {
             x=stck[top-1]-stck[top];
             top=top-2;
             top++;
             stck[top]=x;
         }
         else if(post[i]=='*')
         {
             x=stck[top-1]*stck[top];
             top=top-2;
             top++;
             stck[top]=x;
         }
         else if(post[i]=='/')
         {
             x=stck[top-1]/stck[top];
             top=top-2;
             top++;
             stck[top]=x;
         }
         else if(post[i]=='^')
         {
             x=pow(stck[top-1],stck[top]);
             top=top-2;
             top++;
             stck[top]=x;
        }
     }
     return stck[top];
}
main()
{
    string inf,post; double val;
    cout<<"Enter Infix To Calculate : ";
    cin>>inf;
    post=inf_postf(inf);
    val=post_eval(post);
    cout<<"\nAns : ";
    cout<<val<<endl;
    return 0;
}

