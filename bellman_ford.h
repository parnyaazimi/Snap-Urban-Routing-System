#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "graph.h"
#include <vector>

using namespace std;

struct BellmanFordResult
{
    bool hasNegativeCycle;
    vector<double> dist;
    vector<int> parent;
    vector<int> path;
};

class BellmanFord
{
    private:
        static vector<int> buildPath(int source, int target, const vector<int>& parent);

    public:
        static BellmanFordResult run(const Graph& graph);
        static BellmanFordResult run(const Graph& graph, int source, int target);
};

#endif