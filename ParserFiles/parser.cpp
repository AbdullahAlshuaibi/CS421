#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: SYNTAX ERROR (match fails)
// Done by: Abdullah Alshuaibi
void syntaxerror1(  )
{
  cout<<"SYNTAX ERROR: expected "<< <<" but found "<< <<endl;
}
// Type of error: SYNTAX ERROR (switch default)
// Done by: Abdullah Alshuaibi
void syntaxerror2(  ) 
{
  cout<<"SYNTAX ERROR: unexpected "<< <<" found in "<< <<endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: THe purpose of this function is to check the next token             
//          and return the token type
// Done by: Eduardo Lopez Aguirre 
token_type next_token()
{
  if(!token_available)
    {
      scanner(saved_token, saved_lexeme);
      if(saved_token == ERROR)
        {
          cout << "\nLexical Error: " << saved_lexeme << endl;
        }
      token_available == true;
    }
  return saved_token;
}

// Purpose: The purpose of this function is to determine whether the next token
//          matched the grammer rule returning true if it does and fale if it does not
// Done by: Eduardo Lopez Aguirre 
boolean match(tokentype expected) 
{
  if(next_token() == expected)
    {
      token_available = false;
      return true;
    }
  else
    {
      syntaxerror1(expected);
      scanner(saved_token, saved_lexeme);
      match(saved_token);
    }
}




// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **
// Done by: **


//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  **
int main()
{
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
