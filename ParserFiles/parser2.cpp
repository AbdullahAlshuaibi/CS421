#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
//#include "scanner.h"
using namespace std;

/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .
       and then append the two files into one:
          cat scanner.cpp parser.cpp > myparser.cpp
*/

// --------- Two DFAs ---------------------------------

// WORD DFA
// Done by: Jorge Sanchez
// RE:((([dwyzj]|[bmkhprgn]y?|ts?|sh?|ch)?[aeiouIE]+n?)+(([dwyzj]|[bmkhprg]y?|ts?|sh?|ch)[aeiouIE]+n?)*)+
bool word (string s)
{

  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0')
    {
      if (state == 0 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			 s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else if ((state == 0|| state == 1) && (s[charpos] == 'd'||s[charpos] == 'w'||
					     s[charpos] == 'z'||s[charpos] == 'y'||s[charpos] == 'j')){
	state = 2;}
      else if ((state == 0) && (s[charpos] == 'b'||s[charpos] == 'm'||
				s[charpos] == 'k'||s[charpos] == 'n'||s[charpos] == 'h'||
				s[charpos] == 'p'||s[charpos] == 'r'||s[charpos] == 'g')){
	state = 3;}
      else if ((state == 0|| state == 1)&& s[charpos] == 't')
	state = 4;
      else if ((state == 0|| state == 1) && s[charpos] == 's')
	state = 5;
      else if ((state == 0|| state == 1) && s[charpos] == 'c')
	state = 6;
      else if ((state == 0|| state == 1)&& s[charpos] == 'n')
	state = 0;
      else if (state == 1 && (s[charpos] == 'a'||s[charpos] == 'e'||
			      s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			      s[charpos] == 'E'||s[charpos] == 'I')){
	state = 1;}
      else if ((state == 1) && (s[charpos] == 'b'||s[charpos] == 'm'||
				s[charpos] == 'k' ||s[charpos] == 'h'|| s[charpos] == 'p'||
				s[charpos] == 'r'||s[charpos] == 'g')){
	state = 3;}
      else if (state == 2 && (s[charpos] == 'a'||s[charpos] == 'e'||
			      s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			      s[charpos] == 'E'||s[charpos] == 'I')){
	state = 1;}
      else if (state == 3 && s[charpos] == 'y')
	state = 2;
      else if (state == 3 && (s[charpos] == 'a'||s[charpos] == 'e'||
			      s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			      s[charpos] == 'E'||s[charpos] == 'I')){
	state = 1;}
      else if (state == 4 && s[charpos] == 's')
	state = 2;
      else if (state == 4 && (s[charpos] == 'a'||s[charpos] == 'e'||
			      s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			      s[charpos] == 'E'||s[charpos] == 'I')){
	state = 1;}
      else if (state == 5 && s[charpos] == 'h')
	state = 2;
      else if (state == 5 && (s[charpos] == 'a'||s[charpos] == 'e'||
			      s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
			      s[charpos] == 'E'||s[charpos] == 'I')){
	state = 1;}
      else if (state == 6 && s[charpos] == 'h')
	state = 2;
      else
	{
	  return(false);
	}
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 0)
    return(true);
  else if (state == 1)
    return(true); // end in a final state
  else
    return(false);
}// end of wordtoken


// PERIOD DFA
// Done by: Jorge Sanchez
bool period (string s)
{
  
  if(s == ".")
    return true;
  else
    return false;

}


// ------ Three  Tables -------------------------------------

// TABLES Done by: Abdullah Alshuaibi

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {WORD1, WORD2, PERIOD, ERROR, VERB, VERBNEG,
                VERBPAST, VERBPASTNEG, IS, WAS, OBJECT,
                SUBJECT, DESTINATION, PRONOUN,
                CONNECTOR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "ERROR", "VERB", "VERBNEG",
                        "VERBPAST","VERBPASTNEG", "IS", "WAS", "OBJECT",
                        "SUBJECT", "DESTINATION", "PRONOUN",
			"CONNECTOR", "EOFM"};

// ** Need the reservedwords table to be set up here.
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string reservedWords[18] = {"masu", "masen", "mashita", "masendeshita", "desu",
                            "deshita", "o", "wa", "ni","watashi", "anata",
                            "kare", "kanojo", "sore", "mata", "soshite",
                            "shikashi", "dakara"};
tokentype reservedType[18] = {VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
			      WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, PRONOUN,
			      PRONOUN, PRONOUN, PRONOUN, CONNECTOR, CONNECTOR,
			      CONNECTOR,CONNECTOR};

int scanner(tokentype& , string& );  // to be called by main
// ------------ Scaner and Driver -----------------------

bool match(tokentype);
ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Abdullah Alshuaibi
int scanner(tokentype& tt, string& w){

  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.

  /*  **
  2. Call the token functions (word and period)
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
  fin >> w;
  cout << "Scanner called using word: " << w << endl;

  if(w == "eofm")
    tt = EOFM;
  else if(word(w)){
    bool reserved = false;
    for(int i = 0; i<18; i++)
      {
	if(w == reservedWords[i])
	  {
	    tt = reservedType[i];
	    reserved = true;
	    break;
	  }
      }
    if(reserved == false)
      {
	if(w[w.size()-1] == 'I' || w[w.size()-1] == 'E')
	  tt = WORD2;
	else
	  tt = WORD1;
      }
  }
  else if(period(w))
    tt = PERIOD;
  else{
    //cout << endl << ">>>>>Lexical Error: "<< w <<" is not a valid token" << endl;
    tt = ERROR; }
  
  return 0; //Why is return type int??
}//the end of scanner

//prototypes for story
void story();
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();


//=================================================
// File parser.cpp written by Group Number: 5
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------
//Parser Globals                                                                                                                                                                

tokentype  saved_token;
string saved_lexeme;
bool   token_available;
bool exitFlag = false;

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.

// Type of error: 
// Done by: Abdullah Alshuaibi
void syntaxerror1(tokentype expected, string lexeme){
  cout << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << lexeme << endl;
  exitFlag = true;
  char sORr;
  /* do{
    cout<<"Skip or replace the token? (s or r)";
    cin>>sORr;
  }while(sORr != 's' && sORr != 'r');
  if(sORr == 's') {
    exitFlag =true;}
    

  else{
    match(expected);
    }*/
}
// Type of error: **
// Done by: **
void syntaxerror2( string lexeme, string parserFunction ) {
  cout << "\nSYNTAX ERROR: unexpected " << lexeme << " found in " << parserFunction << endl;
  exitFlag = true;
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: THe purpose of this function is to check the next token
//          and return the token type
// Done by: Eduardo Lopez Aguirre
tokentype next_token(){

  string lexeme;

  if (!token_available)   // if there is no saved token from previous lookahead
    {
      if (exitFlag)
	exit(1);
      scanner(saved_token, lexeme);
      cout << "Scanner called using word: " << lexeme << endl;
      if (saved_token == ERROR) {
      cout << "\nLexical Error: " << lexeme << " is not a valid token" << endl;
      }
      token_available = true;                  // mark that fact that you have saved it
      saved_lexeme = lexeme;

    }
  return saved_token;    // return the saved token
}

// Purpose: The purpose of this function is to determine whether the next token
//          matched the grammer rule returning true if it does and fale
//          if it does not
// Done by: Eduardo Lopez Aguirre
bool match(tokentype expected) {
  if (exitFlag)
    return false;
  if (next_token() != expected)  // mismatch has occurred with the next token
    { // generate a syntax error message here
      // do error handling here if any
      syntaxerror1(expected, saved_lexeme);
      return false;
    }
  else  // match has occurred
    {
      cout << "Matched " << tokenName[expected] << endl; // say there was a match
      token_available = false;  // eat up the token
      return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// 1 <story> ::= <s> { <s> }
// Done by: Jorge Sanchez
void story()
{
  if (exitFlag)
    return;
  cout << "Processing <story>" << endl << endl;
  s();
  while (true)
    {
      if (exitFlag)
	return;
      switch (next_token()) // look ahead to see if the valid start is there
	{
	case CONNECTOR: s();// found another beginning
	  // so do it
	  break;
	case WORD1:s();// found another beginning
	  // so do it
	  break;
	case PRONOUN:s();// found another beginning
	  // so do it
	  break;
	default:
	  cout << "\nSuccessfully parsed <story>.\n" << endl;
	  return;  // loop stops
	  
	  
	}//end switch
    }//end loop
}


//2 <s>  ::=  [CONNECTOR] <noun> SUBJECT <afterSubject>
// Done by: Jorge Sanchez
void s()
{
  if (exitFlag)
    return;
  cout << "Processing <s>" << endl;
  if (next_token() == CONNECTOR)    // start of what is in [ ] is found
    match(saved_token);// do it

  noun();
  match(SUBJECT);
  afterSubject();
}

// 3 <afterSubject> ::=  <verb> <tense> PERIOD | <noun> <afterNoun>
// Done by: Jorge Sanchez
void afterSubject()
{
  if (exitFlag)
    return;
  cout << "Processing <afterSubject>" << endl;
  switch (next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      afterNoun();
      break;

    default:
      syntaxerror2(saved_lexeme, "afterSubject");
    }

}

// 4 <afterNoun> :: = <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterObject>
// Done by: Jorge Sanchez
void afterNoun()
{
  if (exitFlag)
    return;
  cout << "Processing <afterNoun>" << endl;
  switch (next_token())
    {
    case IS:
    case WAS:
      be();
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      afterObject();
      break;

    default:
      syntaxerror2(saved_lexeme, "afterNoun");
    }
}

// 5 <afterObject> ::=  <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
// Done by: Jorge Sanchez
void afterObject()
{
  if (exitFlag)
    return;
  cout << "Processing <afterObject>" << endl;
  switch (next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;

    case WORD1:
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;

    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// 6 <noun> :: = WORD1 | PRONOUN
// Done by: Jorge Sanchez
void noun()
{
  if (exitFlag)
    return;
  cout << "Processing <noun>" << endl;
  switch (next_token())
    {
    case WORD1:
      match(WORD1);
      break;

    case PRONOUN:
      match(PRONOUN);
      break;

    default:
      syntaxerror2(saved_lexeme, "noun");
    }
}

// 7 <verb> ::= WORD2
// Done by: Jorge Sanchez
void verb()
{
  if (exitFlag)
    return;
  cout << "Processing <verb>" << endl;
  match(WORD2);
}

// 8 <be> :: = IS | WAS
// Done by: Jorge Sanchez
void be()
{
  if (exitFlag)
    return;
  cout << "Processing <be>" << endl;
  switch (next_token())
    {
    case IS:
      match(IS);
      break;

    case WAS:
      match(WAS);
      break;

    default:
      syntaxerror2(saved_lexeme, "be");
    }
}

// 9 <tense> : = VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Jorge Sanchez
void tense()
{
  if (exitFlag)
    return;
  cout << "Processing <tense>" << endl;
  switch (next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;

    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;

    case VERB:
      match(VERB);
      break;

    case VERBNEG:
      match(VERBNEG);
      break;

    default:
      syntaxerror2(saved_lexeme, "tense");
    }
}


//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by:  Jorge Sanchez
int main()
{
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file
  story();

  fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
