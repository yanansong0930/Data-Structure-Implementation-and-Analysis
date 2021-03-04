#include "proj5.hpp"
#include "MyPriorityQueue.hpp"
#include "edge.hpp"


// As a reminder, for this project, edges have positive cost, g[i][j] = 0 means no edge.
std::vector<Edge> compute_mst(std::vector< std::vector<unsigned>> & graph)
{
    int sz = graph.size();
    MyPriorityQueue<std::vector<unsigned>> mpq;
    std::vector<unsigned> key(sz, INT_MAX);
    std::vector<unsigned> parent(sz, -1);
    std::vector<unsigned> child(sz, -1);
    std::vector<bool> inMST(sz, false);
    mpq.insert({0,0});
    parent[0] = 0;
    child[0] = 0;
    key[0] = 0;
    while (not mpq.isEmpty())
    {
        unsigned u = mpq.min()[1];
        mpq.extractMin();
        inMST[u] = true;
        for (unsigned i = 0; i < graph[u].size(); i++)
        {
            unsigned w = graph[u][i];
            if (inMST[i] == false && key[i] > w)
            {
                key[i] = w;
                mpq.insert({w, i});
                parent[i] = u;
                child[u] = i;
            }
        }
    }
         
    std::vector<Edge> res;
    for (unsigned i = 0; i < parent.size(); i++)
    {
        if (not(i==0 && parent[i]==0))
        {
            Edge temp{0,0,0};
            temp.pt1 = parent[i];
            temp.pt2 = i;
            temp.weight = graph[parent[i]][i];
            res.push_back(temp);
        }
    }
    
    return res;
}



// Returns the cost of the edges in the given vector,
// This does not confirm that it is a MST at all.  
unsigned mstCost(const std::vector<Edge> & vE) 
{
	unsigned sum =0;
	for(auto e: vE)
	{
		sum += e.weight;
	}
	return sum;
}
