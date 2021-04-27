#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
const char NUM[]={'0','1','2','3','4','5','6','7','8','9','.'};
const char OPERATION[]={'+','-','*','/'};
const double PI=3.14159265358979;
const double EE=2.71828182818281;
class Fun //处理系统数学函数的类
{
public:
Fun(string o,int t,double l=0.0,double r=0.0):op(o),type(t),lvalue(l),rvalue(r){}
static string FUN[];
double calc();
private:
int type; //666 0 1 sin90 2 3! 3 3C2
string op; //函数类型
double lvalue; //函数左边的值
double rvalue; //函数右边的值
static int FunNum;
};
int Fun::FunNum=8;
string Fun::FUN[]={"!","sin","cos","tan","log","ln","C","A","^"};
/*
函数说明:
1:log是以10为底的工程对数
2:ln 是以e为底的自然对数
3:C 计算组合数 输入规则 如计算 3取2的组合 输入表达式 3C2
4:A 计算排列数 输入规则 如计算 3取2的排列 输入表达式 3A2
5:! 计算阶乘
6:^ x的y次方 输入 x^y
*/
int factorial(int n) //阶乘函数
{
int i,s=1;
for(i=1;i<=n;i++)
s*=i;
return s;
}
int C(int a,int b)
{
return factorial(a)/(factorial(b)*factorial(a-b));
}
int A(int a,int b)
{
return factorial(a)/factorial(b);
}
double Fun::calc() //计算系统函数的值
{
if(type==0)
return lvalue;
else
{
if(op=="!")
return factorial(lvalue);
if(op=="sin")
return sin(rvalue/180*PI);
if(op=="cos")
return cos(rvalue/180*PI);
if(op=="tan")
return tan(rvalue/180*PI);
if(op=="log")
return log10(rvalue);
if(op=="ln")
return log10(rvalue)/log10(EE);
if(op=="C")
return C(lvalue,rvalue);
if(op=="A")
return A(lvalue,rvalue);
if(op=="^")
return pow(lvalue,rvalue);
else
{
string err="暂时没有函数"+op;
MessageBox(NULL,err.c_str(),"错误",MB_OK);
return 0;
}
}
}
struct Unit //双向链表保存运算单元
{
Unit(int p,char o,string c,double v,int t,Unit * pr=NULL,Unit * n=NULL)
:PRI(p),Operation(o),Code(c),value(v),Type(t),Pre(pr),Next(n){}
int PRI; //优先级
char Operation; //操作符
string Code; //原始代码
double value; //数据
int Type; //类型 操作符0 数据1 函数2
Unit * Pre; //构成双向链表
Unit * Next;
};
class Node //表达式树状结构的节点
{
public:
Node(char o,int p,int e=1,double v=0,Node * ph=NULL,Node * pl=NULL,Node * pr=NULL)
:Operation(o),PRI(p),Expression(e),value(v),Head(ph),Left(pl),Right(pr){}
Node * Head; //节点的根,左树枝,右树枝
Node * Left;
Node * Right;
double GetValue();
char GetOperation() const {return Operation;}
int GetPri() const {return PRI;}
int IsExp() const {return Expression;}
private:
char Operation; //操作符
int PRI; //优先级
int Expression; //记录该节点是否是表达式0 1
double value; //该节点的值
};
double Node::GetValue() //运算该节点的值
{
if(IsExp()) //该节点的值还未算出来
{
double lvalue,rvalue;
lvalue=Left->GetValue();
rvalue=Right->GetValue();
Expression=0;
char op=GetOperation();
switch(op)
{
case '+':
return lvalue+rvalue;
case '-':
return lvalue-rvalue;
case '*':
return lvalue*rvalue;
case '/':
return lvalue/rvalue;
default:
return 0;
}
}
else
return value;
}
bool Isnum(char c)
{
for(int i=0;i<sizeof(NUM);i++)
{
if(c==NUM[i])
return true;
}
return false;
}
bool Isoperation(char c)
{
for(int i=0;i<sizeof(OPERATION);i++)
{
if(c==OPERATION[i])
return true;
}
return false;
}
Unit * Analyse(string exp) //分析表达式并生成链表
{
int pri=0; //当前优先级
int stat=-1; //当前的读入状态 括号 0 数据 1 运算符 2
Unit * head=NULL,* p=NULL;
int i=0,explen;
explen=exp.size();
for(i=0;i<explen;i++)
{
char c=exp.at(i);
if(c=='(')
{
pri+=3;
stat=0;
}
else if(c==')')
{
pri-=3;
stat=0;
}
else if(Isoperation(c)) //操作符不会出现在表达式开头
{
Unit * temp=p;
int add_pri; //自身增加的优先级
if(c=='+' || c=='-')
add_pri=1;
else
add_pri=2;
p->Next=new Unit(pri+add_pri,c," ",0,0);
p=p->Next;
p->Pre=temp;
}
else //其他的当做函数处理
{
string function="";
while(i<explen && (c=exp.at(i),! Isoperation(c)) && c!=')')
{
function+=c;
i++;
}
i--;
if(head==NULL)
{
p=new Unit(pri,' ',function,0,2);
head=p;
}
else
{
Unit * temp=p;
p->Next=new Unit(pri,' ',function,0,2);
p=p->Next;
p->Pre=temp;
}
}
}
return head;
}
Unit * Calc(Unit * head) //计算双向链表基本单元的值
{
Unit * p=head;
while(p!=NULL)
{
if(p->Type!=0) //非操作符
{
string temp=p->Code;
string op;
double lvalue=0,rvalue=0;
int l_point=0,r_point=0;
int i=0,type=0;
char ch;
while(i<temp.size() && (ch=temp.at(i),Isnum(ch)))
{
if(ch=='.')
{
l_point++;
i++;
continue;
}
if(! l_point)
lvalue*=10;
lvalue+=(ch-'0')*pow(10,-l_point);
i++;
if(l_point)
l_point++;
}
while(i<temp.size() && (ch=temp.at(i),! Isnum(ch)))
{
op+=ch;
type=1;
i++;
}
while(i<temp.size() && (ch=temp.at(i),Isnum(ch)))
{
if(ch=='.')
{
r_point++;
i++;
continue;
}
if(! r_point)
rvalue*=10;
rvalue+=(ch-'0')*pow(10,-r_point);
i++;
if(r_point)
r_point++;
}
Fun * f=new Fun(op,type,lvalue,rvalue);
p->value=f->calc();
}
p=p->Next;
}
return head;
}
Node * Tree(Unit * head) //生成表达式树
{
Node * root=NULL,* proot=NULL,* pbranch=NULL;
Unit * p=head;
int now_pri; //当前优先级
bool hadop=false;
while(p!=NULL)
{
if(p->Type==0) //如果是一个操作符
{
hadop=true;
if(root==NULL)
{
proot=new Node(p->Operation,p->PRI,1);
root=proot;
pbranch=root;
now_pri=p->PRI;
proot->Left=new Node(' ',0,0,p->Pre->value);
proot->Right=new Node(' ',0,0,p->Next->value);
}
else
{
if(p->PRI<=now_pri) //优先级低于当前优先级,树根方向 //最初写的 if(p->PRI<now_pri),9/3/3=9,错的
{
proot=new Node(p->Operation,p->PRI,1); //新的树根
proot->Left=root; //根的变换
proot->Right=new Node(' ',0,0,p->Next->value);
root=proot;
pbranch=proot; //右树枝的变换
//pbranch->Right=new Node(' ',0,0,p->Pre->value); //树枝右边取值
}
else
{
Node * temp;
temp=new Node(p->Operation,p->PRI,1);
pbranch->Right=temp;
temp->Head=pbranch;
pbranch=pbranch->Right;
pbranch->Left=new Node(' ',0,0,p->Pre->value);
pbranch->Right=new Node(' ',0,0,p->Next->value);
}
now_pri=p->PRI;
}
}
p=p->Next;
}
if(! hadop)
root=new Node(' ',0,0,head->value);
return root;
}
int main()
{
string exp;
//ifstream infile("test.txt",ios::in);
while(! getline(cin,exp).eof())
{
if(exp=="")
continue;
Unit * h=Analyse(exp);
h=Calc(h);
Node * root=Tree(h);
cout<<exp<<"="<<root->GetValue()<<endl;
}
return 0;
}