#include<iostream>
#include<fstream>
#include<string>
using namespace std;


//=====================================================
// File scanner.cpp written by: Group Number: 5
//=====================================================

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
      else
      if ((state == 0|| state == 1) && (s[charpos] == 'd'||s[charpos] == 'w'||
          s[charpos] == 'z'||s[charpos] == 'y'||s[charpos] == 'j')){
        state = 2;}
      else
      if ((state == 0) && (s[charpos] == 'b'||s[charpos] == 'm'||
          s[charpos] == 'k'||s[charpos] == 'n'||s[charpos] == 'h'||
          s[charpos] == 'p'||s[charpos] == 'r'||s[charpos] == 'g')){
        state = 3;}
      else
      if ((state == 0|| state == 1)&& s[charpos] == 't')
        state = 4;
      else
      if ((state == 0|| state == 1) && s[charpos] == 's')
        state = 5;
      else
      if ((state == 0|| state == 1) && s[charpos] == 'c')
        state = 6;
      else
      if ((state == 0|| state == 1)&& s[charpos] == 'n')
        state = 0;
      else
      if (state == 1 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if ((state == 1) && (s[charpos] == 'b'||s[charpos] == 'm'||
          s[charpos] == 'k' ||s[charpos] == 'h'|| s[charpos] == 'p'||
          s[charpos] == 'r'||s[charpos] == 'g')){
          state = 3;}
      else
      if (state == 2 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 3 && s[charpos] == 'y')
        state = 2;
      else
      if (state == 3 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 4 && s[charpos] == 's')
        state = 2;
      else
      if (state == 4 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 5 && s[charpos] == 'h')
        state = 2;
      else
      if (state == 5 && (s[charpos] == 'a'||s[charpos] == 'e'||
          s[charpos] == 'i'||s[charpos] == 'o'||s[charpos] == 'u'||
          s[charpos] == 'E'||s[charpos] == 'I')){
        state = 1;}
      else
      if (state == 6 && s[charpos] == 'h')
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
  else
  if (state == 1)
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
    cout<<endl;
    fin >> w;

    if(w == "eofm")
      tt = EOFM;
    else
    if(word(w)){
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
    else
    if(period(w))
      tt = PERIOD;
    else{
      cout << endl << ">>>>>Lexical Error: "<< w <<" is not a valid token" << endl;
      tt = ERROR; }

    return 0; //Why is return type int??
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!!
// Done by:  Rika
int main(){
  tokentype thetype;
  string theword;
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end
