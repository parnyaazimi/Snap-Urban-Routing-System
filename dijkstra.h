#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>

#include "graph.h"

using namespace std;

struct ShortestPathResult
{
    vector<double> distances;
    vector<int> previousNodes;
};

ShortestPathResult dijkstra(const Graph& graph,int startNode);

vector<int> reconstructPath(int startNode,int destinationNode,const vector<int>& previousNodes);

#endif