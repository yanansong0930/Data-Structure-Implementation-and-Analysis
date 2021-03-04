
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#include "proj4.hpp"

std::string keepOnlyLetters(std::string s);


// This is a demo of how to read from the stream, isolate each 
// word, and convert them all to lowercase.
// While this isn't a perfect way to count words, it's what we will use 
// for this project.
// It does mean that "Bill" (in the context of a person's name) and "bill" 
// (in the context of an invoice) are counted as the same word.
// You may use or modify any of this code as you wish for this project. 
void countWords(std::istream & in, MyAVLTree<std::string, unsigned> & counter)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			word = keepOnlyLetters(word);
			if( word != "")	// "" means no letters got retained. 
			{
		//		std::cout << word << std::endl;
				// In the "real program," you do something else here.
                if (not counter.contains(word))
                {
                    counter.insert(word, 1);
                }
                else { counter.find(word)++; }
			}
			else
			{
				// In "real program," you don't do anything here.
				// This output is for your information here.
				// Comment it out or delete it before submitting. 
         		std::cout << "Skipped because found something like a number or special characters." << std::endl; 
			}
		}
	}

}


std::string keepOnlyLetters(std::string s)
{
	std::string ret = "";
	for (size_t i=0; i < s.length(); i++)
	{
		if ( isalpha(s[i]) ) // isalpha() checks if this is a letter.
		{
			ret += std::tolower( s[i] );
		}

	}
	return ret;
}



