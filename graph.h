#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

struct Edge
{
    int from; 
    int to;
    double d;
    double t;
    double w;
    double cost;
};



class Graph
{
    private:
        int nodeCount;
        int sourceNode;
        int targetNode;
        bool negativeEdgeExists;
        vector<double> delayValues;
        vector<vector<Edge>> adjacencyList;
        vector<Edge> allEdges; 
        vector<int> multiDestinations;

    public:
        Graph();

        int getSize() const;
        int getSource() const;
        int getTarget() const;
        bool containsNegativeEdge() const;
        const vector<Edge>& getNeighbors(int node) const;
        const vector<Edge>& getAllEdges() const;
        double getDelay(int node) const;
        double computeCost(int vertex, double d, double t, double w) const;
        bool loadFromFile(const string& fileName);
        const vector<int>& getMultiDestinations() const;
        bool hasMultiDestinations() const;
};

#endif
