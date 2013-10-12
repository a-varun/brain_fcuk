#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <ctype.h>
#include <bitset>
#include <stdio.h>
#include <assert.h>
#include <string.h>
 
using namespace std;
 
#define REP(i, n) for(int i=0; i<(n); i++)
#define FOR(i, a, b) for(int i=(a); i<(b); i++)
#define IFOR(i, a, b) for(int i=(a); i>=(b); i--)
#define FORD(i, a, b, c) for(int i=(a); i<(b); i+=(c))
 
#define SS ({int x;scanf("%d", &x);x;})
#define SI(x) ((int)x.size())
#define TCases int ite;cin>>ite;while(ite--)
#define PB(x) push_back(x)
#define MP(a,b) make_pair(a, b)
#define SORT(a) sort(a.begin(),a.end())
#define ITER(it,a) for(typeof(a.begin()) it = a.begin(); it!=a.end(); it++)
#define ALL(a) a.begin(),a.end()
#define V vector
#define S string
#define FST first
#define SEC second
#define flag(i) cout<<"Here"<<i<<endl
#define FL(i) cout<<"In "<<i<<endl;
typedef V<int> VI;
typedef V<S> VS;
typedef long long LL;
typedef pair<int, int> PII;

int p;

//The node of the DLL

struct node
{
	char data;
	node *next;
	node *prev;
	node()
	{
		data=0;
		next=NULL;
		prev=NULL;
	}
};

//********************************************************************
//************************BF INTERPRETER******************************
//********************************************************************
class bf
{
	node *head;
	public:
		bf()
		{
			head=new node;
		}
		int dodot();
		void docomma();
		void donext();
		void doprev();
		void dosubtract();
		void doadd();
		void dooper(char a);
		int validate(string s);
		int doloop(string s, int i);
		void exception(int val);
		void compile(string s);
		bool isopr(char a);
		string get_input();
		
};

//This function will get the code as input from the user

string bf::get_input()
{

	string a,s;
	getline(cin,a);
	while(a!="")
	{
		for(int i=0;a[i];i++)
		{
			if(isopr(a[i]))
			{
				s+=a[i];
				continue;
			}
			if(a[i]=='/'&&a[i+1]=='/')
			{
				break;
			}
		}
		getline(cin,a);
	}
	return s;
}

//This function will check if the character is a 
//valid BF operator or not.

bool bf::isopr(char a)
{
	switch(a)
	{
		case '+':
		case '-':
		case '>':
		case '<':
		case '[':
		case ']':
		case '.':
		case ',':
			return true;
		default:
			return false; 
	}
}


//This function tokenizes the BF code and interprets it.

void bf::compile(string s)
{
	int val;
	if(validate(s))
	{
		exception(1);
	}
	REP(i,s.length())
	{
		if(s[i]=='[')
		{
			i=doloop(s,i+1);
		}
		else
		{
			dooper(s[i]);
		}
	}
	return;
}

//This throws error in case of any problems in the code.

void bf::exception(int val)
{
	if(val==7)
		cout<<"*******Infinite loop error*********"<<endl<<endl;
	else if(val==8)
		cout<<"*******Memory out of scope*********"<<endl<<endl;
	else if(val==9)
		cout<<"*******Stack overflow*********"<<endl<<endl;
	else if(val==1)
		cout<<"*******Syntax Error*********"<<endl<<endl;
	exit(1);
	return;
}

//This function checks for loops in the code. It will end if the final character is 0
//This will work for nested loops too. It will call itself, in case of a nested loop.

int bf::doloop(string s, int i)
{
	int count=0;
	while(1)
	{
		count++;
		int p=i,val;
		while(s[p]!=']')
		{
			if(s[p]=='[')
			{
				p=doloop(s,p+1)+1;
			}
			else
			{
				dooper(s[p]);
			}
			p++;
		}
		if(head->data==0)
		{
			return p;
		}
	}

}

//Validates a string and returns 1 if it is not a correct code.
//It only checks if all the loops are correct

int bf::validate(string s)
{
	int sum=0;
	REP(i,s.length())
	{
		if(s[i]=='[') sum++;
		else if(s[i]==']') sum--;
		if(sum<0) return 1;
	}
	if(sum!=0) 
		return 1;
	else 
		return 0;
}


//This function calls the appropriate function depending on the character passed 

void bf::dooper(char a)
{
	switch (a)
	{
		case '.': dodot();break;
		case ',': docomma();break;
		case '>': donext();break;
		case '<': doprev();break;
		case '+': doadd();break;
		case '-': dosubtract(); break;
	}
	return;
}

//does the '.' operation
//i.e. prints the input to the screen

int bf::dodot()
{
	cout<<head->data;
	return 0;
}

//does the ',' operation
//i.e. gets the input from the user

void bf::docomma()
{
	head->data=getchar();
	return;
}

//Does the '>' operation.
//Pointer points to the next memory location.

void bf::donext()
{
	if(head->next!=NULL)
	{
		head=head->next;
		return;
	}
	head->next=new node;
	if(head->next==NULL)
	{ 
		exception(9);
	}
	head->next->prev=head;
	head=head->next;
	return;
}

//Does the '<' operation.
//Pointer points to the previous memory element.

void bf::doprev()
{
	if(head->prev==NULL)
	{
		exception(8);
	}
	head=head->prev;
	return;
}

//Does the '-' operation.
//The data value deceases by 1.

void bf::dosubtract()
{
	head->data--;
}

//Does the '+' operation.
//The data value increases by 1.

void bf::doadd()
{
	head->data++;
}


//********************************************************************
//*************************BF CONVERTER*******************************
//********************************************************************

struct link
{   
    int start;
    int data;
    link *next;
    link *prev;
    link(int st,int val,link *a,link *b)
    {
        start=st;
        data=val;
        next=a;
        prev=b;
    }
};
 
class text_to_BF
{
    link *head;
    int a[20];
public:
    text_to_BF()
    {
        head=NULL;
        for(int i=0;i<21;i++)
            a[i]=0;
    }
    void tokenize(string s);
    void brainfAssign(string s);
    void printBrainfc(string s);
    string get_text();
};

//This function will get the input string

string text_to_BF::get_text()
{
    string s,a;
    getline(cin,a);
    while(a!="")
    {
        s+=a;
        s+='\n';
        getline(cin,a);
    }
    return s;
}


//This function will tokenize the text

void text_to_BF::tokenize(string s)
{
    for(int i=0;i<s.length();i++)
    {
        a[(int)s[i]/10]++;
    }
    brainfAssign(s);
}

//This function will initialize the list.

void text_to_BF::brainfAssign(string s)
{
    for(int i=0;i<20;i++)
    {
        if(a[i]==0)continue;
        if(!head)
        {
            head=new link(i*10,i*10,NULL,NULL);
            continue;
        }
        link *t=head;
        while(t->next)
            t=t->next;
        t->next = new link(i*10,i*10,NULL,t);
    }
    printBrainfc(s);
}

//This function will print the BF code for the corresponding text.

void text_to_BF::printBrainfc(string s)   
{
    int size=0;
    link *t=head;
    while(t)
    {
        size++;
        t=t->next;
    }
    for(int i=0;i<10;i++)
        cout<<"+";
    cout<<endl;
    cout<<"["<<endl;
    t=head;
    int i=1;
    while(t)
    {
        cout<<">";
        for(int j=0;j<t->data/10;j++)
        cout<<"+";
        cout<<endl;
        t=t->next;
    }
    for(i=0;i<size;i++)
        cout<<"<";
    cout<<"-]>"<<endl;
    t=head;
    if(t!=NULL)
    {
        for(int i=0;i<s.length();i++)
        {
            while(t && (t->start < ((int)s[i]/10)*10))
            {
                cout<<">";
                t=t->next;
            }
            while(t && (t->start > ((int)s[i]/10)*10))
            {
                cout<<"<";
                t=t->prev;
            }
            if(t->start == ((int)s[i]/10)*10)
            {
                if(t->data < (int)s[i])
                {
                    for(int z=t->data;z<(int)s[i];z++)
                    {
                        cout<<"+";
                    }
                    cout<<"."<<endl;
                    t->data=(int)s[i];
                    continue;
                }
                else if(t->data > (int)s[i])
                {
                    for(int z=t->data;z>(int)s[i];z--)
                    {
                        cout<<"-";
                    }
                    cout<<"."<<endl;
                    t->data=(int)s[i];
                    continue;
                }
                else
                {
                    cout<<".";
                }
            }
        }
    }
}


int main()
{
	int a;
	cout<<endl<<endl<<"1.Text to BF"<<endl<<endl<<"2.BF Compiler"<<endl<<endl;
	cin>>a;
	while(1)
	{
		getchar();
		switch(a)
		{
		    case 1:
		    {
		       text_to_BF a;
		       string s;
		       s=a.get_text();
		       a.tokenize(s);
		       break;
		    }
		    case 2:
		    {
		    	bf a;
		    	string s;
		    	s=a.get_input();
		    	a.compile(s);
		    	break;
		    }
		}
		cout <<endl<<"Press 0 to exit"<<endl;
		cin>>a;
		if(!(a))
			break;
	}
}
