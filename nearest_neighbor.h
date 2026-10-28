#ifndef NEAREST_NEIGHBOR_H
#define NEAREST_NEIGHBOR_H

#include "graph.h"
#include <vector>
#include <string>

using namespace std;

struct NearestNeighborResult
{
    bool success;
    bool hasNegativeCycle;
    double totalCost;
    vector<int> route;
    string message;
};

NearestNeighborResult nearestNeighborRoute(const Graph& graph,int start,vector<int> destinations);

#endif