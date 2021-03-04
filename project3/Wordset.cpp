#include "Wordset.hpp"
#include <string>
#include <iostream>
const int BASE_TO_USE = 37; 
const double LOAD_LIMIT = 0.25;


// returns s, as a number in the given base, mod the given modulus
int hashFunction(std::string s, int base, int mod)
{
     int current = 0;
     for (int i = 0; i < s.length(); i++)
     {
         current *= base;
         current = current % mod;
         int num = s[i] - 'a';
         current += num;
         current %= mod;
     }
     return current;
}


WordSet::WordSet()
    : wordSetArray{new std::string[SIZES[0]]}, pos{0}, cap{SIZES[0]}, sz{0} 
{
    initArray();
}

WordSet::~WordSet()
{
    delete[] wordSetArray;
}

void WordSet::insert(std::string s)
{
    sz++;
    // rehash
    double loadf = sz / static_cast<double>(cap);
    
    if (loadf > LOAD_LIMIT)
    {
        pos++;
        int pre_cap = cap;
        cap = SIZES[pos];
        std::string* pre_wordSet = wordSetArray;
        wordSetArray = new std::string[cap];
        initArray();

        for (int i = 0; i < pre_cap; i++)
        {
            if (pre_wordSet[i] != "")
            {
                addWord(pre_wordSet[i]);
            }
        }
        delete[] pre_wordSet;
    }

    // add word
    addWord(s);    
}


bool WordSet::contains(std::string s) const
{
    int key = hashFunction(s, BASE_TO_USE, cap);
    int i = 0;
    while (i < cap)
    {
        key = (key + i*i) % cap;
        if (wordSetArray[key] == s) { return true;}
        else if (wordSetArray[key] == "") {return false;}
        i++;
    }
    return false;

}

// return how many distinct strings are in the set
int WordSet::getCount() const
{
	return sz;
}

// return how large the underlying array is.
int WordSet::getCapacity() const
{
	return cap;
}

// helper function: initialize all elements in array to be empty string
void WordSet::initArray()
{
    for (int i = 0; i < cap; i++)
    {
        wordSetArray[i] = "";
    }
}
// add new word into word array
void WordSet::addWord(std::string word)
{
    int key = hashFunction(word, BASE_TO_USE, cap);
    int i = 0;
    
    while (true)
    {
        key = (key + i*i) % cap;
        if (wordSetArray[key] ==  "")
        {
            wordSetArray[key] = word;
            break;
        }
        i++;
       
    }
    
}
