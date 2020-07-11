#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Abdullah Alshuaibi
//--------------------------------------

// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.


// info on each DFA
struct info
{
  string name;  // token name
  int startstate;
  int finalstate;
};

info DFAs[4];     // store up to 4 dfas' start and final

int  TRS[10][4];  // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables()
{  

   ifstream fin ("trs.txt", ios::in);
   ifstream fin2 ("dfas.txt", ios::in);
   // ** Read in the files into TRS and DFAs
   int i =0;
   while(fin2 >> DFAs[i].name) //read DFAs
     {
       fin2 >> DFAs[i].startstate;
       fin2 >> DFAs[i].finalstate;
       i++;
     }

   int s=0;  //state
   while(fin >> TRS[s][0]) //read TRS
     {
       for(int c=1; c<4; c++)
	 {
	   fin >> TRS[s][c];
	 }
       s++;
     } 
   
   
   // ** Return how many DFAs were read
   return i;
}

void displayTables(int numDFAs)
{
   // ** display TRS nicely labeled
  cout<<"        a b c d"<<endl;
  for(int i=0; i<10; i++)
    {
      cout<<"state "<<i<<":";
      for(int j=0; j<4; j++)
	{
	  if(TRS[i][j] == -1)
	    cout<<"  ";
	  else
	    cout<<TRS[i][j]<<" ";
	}
      cout<<endl;
    }
  // ** display DFAs nicely labeled
  for (int i=0; i<numDFAs; i++)
    {
      cout<<DFAs[i].name<<": "<<DFAs[i].startstate<<" is start and ends in "<<DFAs[i].finalstate<<endl;
    }
}

bool accept(info dfa, string word)
{
  // ** Does the dfa accept the word?
  // Start with the start state of the DFA and
  // look up the next state in TRS for each char in word.
  // At the end of the word, make sure you are in the 
  // final state of the DFA.
  // Use a formula to convert chars to TRS col numbers.
  int charpos=0; //column slot
  bool accept; // accept char 
  int currentState = dfa.startstate;
  while( word[charpos] != '\0')
    {
      int col;
      col = (int)word[charpos] - 97;
      cout<<"state: "<<currentState<<" char: "<<word[charpos]<<endl;
      
      if(TRS[currentState][col] != -1) //accepted
	{
	  currentState = TRS[currentState][col];
	  accept = true;
	  
	}
      else  //not accepted
	{
	  accept = false;
	  currentState = TRS[currentState][col];
	}
      cout<<"new state: "<<currentState<<endl;
      if (accept == false)
	return accept;
      
      charpos++;
    }  
  return accept;
}


int main()
{
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;

  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;

  string word;
  while(true)
    { cout << "@@Enter a string: " ;
      cin >> word;
      // ** try the DFAs one by one and see 
      //      if the word is accepted
      //      if so, display the word and the token name
      // ** if no DFA does, generate a lexical error message.
    
      for(int i=0; i<numDFA; i++)
	{
	  cout<<"Trying dfa "<<i<<"--------"<<endl;
	  bool acceptt = accept(DFAs[i],word);
	  if(acceptt)
	    {
	      cout<<"found token "<<DFAs[i].name<<endl;
	      break;
	    }
	  else
	    cout<<"Lexical error!"<<endl;
   
	}
      cout << "do control-C to quit" << endl;
    }

}//the end
