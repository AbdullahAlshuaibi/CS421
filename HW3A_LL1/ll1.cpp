
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"stack.h"  // ** can be removed
#include<vector>
#include<string>
using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Abdullah Alshuaibi
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

vector<char> M[3][2];  // the table of rules 
                       // 3 rows for S, A, B
                       // 2 rows for 0, 1
       // Each slot contains a rule's right side
       // which is a vector of characters
stack s; //stack object
//  ------- conversion functions ------------------------


// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char C)
{
  //**  bunch of if then else
  if(C == 'S')
    return 0;
  else if(C == 'A')
    return 1;
  else if(C == 'B')
    return 2;
}

// to convert '0' and '1' to table columns 0 and 1 
int toCol(char c)
{
  // ** bunch of if then else
  if(c == '0')
    return 0;
  else if(c == '1')
    return 1;
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r)
{
  // ** bunch of if then else
  if(r == 0)
    return 'S';
  else if(r == 1)
    return 'A';
  else if(r == 2)
    return 'B';
}


// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V) 
{
  // ** display V horizontally e.g. 0 A 0
 
  // show the content of v separated by blanks (e.g. "0 A 0")
 
      for(int i = 0; i<V.size(); i++)
        {
          cout<<V[i]<<" ";
	}
     

}

// to read in the rules into M, make sure ; is not stored
void readrules()
{ 
  ifstream fin ("rules", ios::in);
  
  // For each line of "rules" (e.g. S  0 A 0 ;) 
  // The first char of a line determines the row of M
  // The second char of a line determine the column of M  
  // Note that each entry of M (the second char up to ;)
  // will be a vector representing 
  // the right hand side of a rule (rhs)
  int i,j;
  char c;
  while(fin)
    {
      fin >> c; // read row
      i = toRow(c); //get row index 
      fin >> c; //read column
      j = toCol(c); //get column index
      while(c != ';') 
	{
	  M[i][j].push_back(c); 
	  fin >> c;
	}
    }

  // ** Display the table nicely  
  //    use toNonterm to show row labels (S, A, B)
  //    use displayVector for each content 
  for(int i=0; i<3; i++)
    {
      c = toNonterm(i);
      cout<<c<<": ";
      for(int j=0; j<2; j++)
	{
	  cout<<"         ";
	  displayVector(M[i][j]);
	}
      cout<<endl;
    }
  
}

//  pushes V contents to the stack 
void addtostack(vector<char> V)
{  cout << "Adding rhs of a rule to the stack." << endl;
  // **  be careful of the order
   // because 1 0 0 means 1 will be at the top of the stack
  for(int i = V.size()-1; i >= 0; i--)
    {
      s.push(V[i]);
    }
}

int main()
{ 
  readrules();  // M is filled and displayed 
  char pop; // top of stack
  string ss;
  cout << "Enter a string made of 0's and/or 1's: ";
  cin >> ss;

  // ** push 'S' onto the stack to start

  s.push('s');
  cout << "Stack:"<<endl;
  // ** display the stack vertically from top to bottom 
  s.displayAll();

  int r = toRow('S');
  if(ss[0] == '0' || ss[0] == '1')
    {
    s.pop(pop);
    addtostack(M[r][toCol(ss[0])]);
    }

  else
    {
      cout<<">>Error - no rule. Reject!"<<endl;
      return 0;
    }

  cout << "Stack:"<<endl;
  // ** display the stack vertically from top to bottom
  s.displayAll();

  int i = 0;  // index for ss

  while (ss[i] != '\0')  // for each char of ss
    {
     // Based on ss[i] and 
     //    the top of stack, update the stack: 
     // ** note that empty stack will cause immediate failure  
     // ** note that top of stack terminal and ss[i] mismatching
     //    will cause immediate failure 
     // ** note that no entry in M for the top of stack (non-terminal)
     //    and ss[i] will cause immediate
     //    failure  (use toRow and toCol to look up M)
     // ** otherwise, addtoStack the M entry based on ss[i] and the top of stack
      
      s.pop(pop);
      
      cout<<"current char is: "<<ss[i]<<endl;
      
      if(pop == 'A'||pop == 'B')
	addtostack(M[toRow(pop)][toCol(ss[i+1])]);

      else if(ss[i] == pop)
	{
	  cout << "MATCHED!!" << endl;
	  i++;
	} 
      
      else
	{
	  cout << ">>MISMATCH Error REJECT!" << endl;
	  return 0;
	}

      //display the whole stack
      cout << endl << "Stack" << endl;
      s.displayAll();

    } // end of string

      
  // ** Here, check for success for failure based on stack empty or not
  if(s.isEmpty() && ss[i] == '\0')
    {
      cout << ">> ACCEPT!" << endl;
    }
  else if(s.isEmpty() && ss[i] != '\0')
    {
      cout << ">> ERROR Stack is Empty REJECT!" << endl;
    }
}// end of main
