#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <iostream>
#include "proj3.hpp"
#include "Wordset.hpp"


int main()
{

    WordSet words;
    std::ifstream in("words.txt");
    loadWordsIntoTable(words, in);

    std::string r = convert("abstraction","aestipctiea", words);
    
    std::cout << r;

    return 0;
}

