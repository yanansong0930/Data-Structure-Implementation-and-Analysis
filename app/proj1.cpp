#include "proj1.hpp"
#include <map>
#include <string>
#include <vector>


bool puzzleSolver(std::string s1, std::string s2, std::string s3, std::map<char, unsigned> & mapping)
{
    // vector digits used to check if some digit has already been used for puzzle
    // eg, if a digit i isn't used, digits[i] = true, otherwise digits[i] = false
    std::vector<bool> digits(10, true);
    // collect all distinct letter 
    std::vector<char> letters;

    // add all unique letters into mapping
    initializeMapping(s1, letters, mapping);
    initializeMapping(s2, letters, mapping);
    initializeMapping(s3, letters, mapping);

    // if the number of unique letters is greater than 10, there can't be a solution for this puzzle
    if (mapping.size() > 10) { return false;}
  
    // use recursive function to check if it has a solution
    return search(s1, s2, s3, mapping.size()-1, mapping, digits, letters);
}

// recursive function
bool search(std::string s1, std::string s2, std::string s3, int pos ,std::map<char, unsigned>& mapping, std::vector<bool>& digits, const std::vector<char>& letters)
{
    // base case:
    if (pos == 0)
    {
        for (int j = 0; j < 10; j++)
        {
            if (digits[j])
            {   // assign unused digits to the last letter and check if the current mapping is a correct solution
                mapping.at(letters[0]) = j;
              
                if (verifySolution(s1, s2, s3, mapping))
                {
                    // if there's a correct solution, return true
                    return true;
                }
            }
        }
   
    }

    // recursive case:
    else if (pos > 0)
    {
        for (int i = 0; i < 10; i++)
        {
            // check if i has already been used
            if (digits[i])
            {
                // if not, assign letters in pos equal to i and change digits[i] = false
                mapping.at(letters[pos]) = i;
                digits[i] = false;

                // recursive call
                if (search(s1, s2, s3, pos-1, mapping, digits, letters))
                {
                    return true;             // recursivly call this function to assign unused digits to the rest in letters 
                }                            // until the last letter is assigned a digit(base case)  
                else { digits[i] = true; }   // if recursive call returns false, re-assign this digit to be true(not used)
            }                                // and assign next unused digit to the first letter
        }
    }
    // if it's not a correct solution, return false
    return false;
}


// initialize the map
void initializeMapping(std::string s, std::vector<char>& letters, std::map<char, unsigned int>& mapping)
{
    for (int i=0; i<s.length(); i++)
    {
        if (mapping.count(s[i]) == 0)
        {
            mapping.insert(std::pair<char, unsigned int>(s[i],10));
            letters.push_back(s[i]);
        }
    }
}


// I directly copy and paste my code in project0 in order to help my recursive function check if
// the current mapping is the correct solution
bool verifySolution(std::string s1, std::string s2, std::string s3, const std::map<char, unsigned> & mapping)
{
    int a=0,b=0,s=0;
    a = findDigit(s1, mapping);
    b = findDigit(s2, mapping);
    s = findDigit(s3, mapping);

    return (a+b) == s; 
}

int findDigit(std::string s, const std::map<char, unsigned> & mapping)
{
    int result = 0;
    int len = s.length();
    for(int i = 0; i<s.length(); i++)
    {
        int c = 0;
        c += mapping.at(s[i]);
        int j = i;
        while(j < len-1)
        {
            c *= 10;
            j++;
        }
        result += c;
    }
    return result;
}


