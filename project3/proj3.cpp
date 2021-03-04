#include "proj3.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
// I just follow the hint professor given in project3 file.
{
    // key: word just saw; value: immediately before it?
    std::map<std::string, std::string> mapping;
    std::queue<std::string> q;

    q.push(s1);
    int count = 0;
    // store all possible pairs in mapping
    while(not q.empty())
    {
        std::string current = q.front();
        if (current == s2)
        {
            break;
        }
        for (int j = 0; j < 26; j++)
        {
            for (int i = 0; i < current.length(); i++)
            {
                std::string temp = current;
                temp[i] = 'a'+j;
                if (words.contains(temp) && temp!=current)
                {
//                  mapping.insert(std::pair<std::string, std::string> (current, temp));
                    mapping.insert(std::pair<std::string, std::string> (temp, current));
                    q.push(temp);
                    count++;
                }
            }
        }
        q.pop();
    }
    
    // put all nodes into a stack in order    
    std::stack<std::string> container;
    container.push(s2);
    std::string pos = s2;
    while (pos != s1)
    {
        std::string record = mapping.at(pos);
        pos = record;
        container.push(record);
    }
    
    // get the path
    std::string result = container.top();
    container.pop();
    
    while (not container.empty())
    {
        result += " --> ";
        result += container.top();
        container.pop();
     
    }
    for (auto v : mapping)
    {
        std::cout << v.second << " --> " << v.first << std::endl;
    }
    std::cout << count << std::endl;

    return result;
}
