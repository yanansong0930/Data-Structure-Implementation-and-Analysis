#include "proj2.hpp"
#include <vector>
#include "LLQueue.hpp"

void countPaths(const std::vector< std::vector<unsigned> > & friends, unsigned start, std::vector<unsigned> & pathLengths, std::vector<unsigned> & numShortestPaths)
{
    // initialize pathLengths and numShortestPaths
    for (int i = 0; i < friends.size(); i++)
    {
        if (i == start) {pathLengths[i] = 0;}   // the shortest path from start to itself must be 0
        else { pathLengths[i] = -1;}            // the number of the shortest from start to itself must be 1
    }
    for (int j = 0; j < friends.size(); j++)
    {
        if (j == start) {numShortestPaths[j] = 1;}
        else {numShortestPaths[j] = 0;}
    }

    std::vector<bool> discovered(friends.size(), false);  // vector used for tracking if a vertex has been visited
    LLQueue<unsigned> q;     // store vertices

    q.enqueue(start);
    discovered[start] = true;

    // use BFS: traversing graph by starting at the root(start), and exploring all
    // friends of current vertex on the current level;
    // after check all vertices on the current level, move to the vertices on the next level.
    while (not q.isEmpty())
    {
        unsigned vertex = q.front();
        for (auto v : friends[vertex])    // iterate all neighbors of this vertex 
        {
            if (not discovered[v])   // check if this neighbor is visited
            {
                discovered[v] = true;
                q.enqueue(v);
            }
            // if it's the current shortest path, add all same-length paths together
            if (pathLengths[v] == pathLengths[vertex]+1)
            {
                numShortestPaths[v] += numShortestPaths[vertex];
            }
            // if not, update the length of shortest path and num of total same-length paths
            else if (pathLengths[v] == -1 || pathLengths[v] > pathLengths[vertex]+1)
            {
                pathLengths[v] = pathLengths[vertex]+1;
                numShortestPaths[v] = numShortestPaths[vertex];
            }

        }
        q.dequeue();     // after check all neighbors, remove this vertex
    }


}
