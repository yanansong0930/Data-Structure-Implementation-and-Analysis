#ifndef __PROJ_1__HPP
#define __PROJ_1__HPP

#include <map>

/* 
 * Project 1:  you need to implement this function.
 I promise that any of my test cases will have an empty 
 	map as the fourth parameter when called.
 If the puzzle IS solvable, return true AND make the mapping indicate the solution.
 If the puzzle is NOT solvable, it is enough to return false.

 See the project 1 write-up for a better description. 
 */


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping);

bool search(std::string s1, std::string s2, std::string s3, int pos ,std::map<char, unsigned>& mapping, std::vector<bool>& digits, const std::vector<char>& letters);

void initializeMapping(std::string s, std::vector<char>& letters, std::map<char, unsigned int>& mapping);

bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping);

int findDigit(std::string s, const std::map<char, unsigned> & mapping);


#endif
