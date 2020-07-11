//CS311 Yoshii
//INSTRUCTION:
//Look for ** to complete this program 
//The string output should match my hw1queueDemo.out 

//=========================================================
//HW#: HW1P2 queue
//Your name: Abdullah Alshuaibi
//Complier:  g++
//File type: client program client2.cpp
//===========================================================

using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "queue.h"

//Purpose of the program: getting a set of characters by using queue 

//Algorithm: We start with “A”, “B” and “C” in the queue.
//Loop - Do the following repeatedly:
//1.Remove a string and display it.
//2.Add the string + “A”
//3.Add the string + “B”
//4.Add the string + “C”

int main()
{ // "A", "B", "C" in the queue
  queue characters;
  characters.add("A"); // adding "A" in the queue
  characters.add("B"); // adding "B" in the queue
  characters.add("C"); // adding "C" in the queue 
  // while loop -- indefinitely
  while(!characters.isFull())
    {
      try
	{ 
	  el_t str; // the displied string 
	  characters.remove(str); // caaling remove to get the front elemnt for displying 
	  cout<<str<<endl; // displying the string
	  characters.add(str+"A"); // adding A to the string ex(AA) ... (BBA) ... 
	  characters.add(str+"B"); // adding B to the string ex(AB) ... (BBB) ...
	  characters.add(str+"C"); // adding C to the string ex(AC) ... (BBC) ...
	}
      catch (queue::Overflow) 
	{cout<<"."<<endl<<"."<<endl<<"'Overflows' 'Overflows' 'Overflows'"<<endl; exit(1); }
    }// end of loop

}

