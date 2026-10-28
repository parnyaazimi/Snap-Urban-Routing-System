#include "dijkstra.h"

#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>

using namespace std;

ShortestPathResult dijkstra(const Graph& graph, int startNode)
{
    const int nodeCount = graph.getSize();
    const double infinity = numeric_limits<double>::infinity();

    if (startNode < 0 || startNode >= nodeCount)
    {
        cerr << "Algorithm Error: Invalid source node passed to Dijkstra."<< endl;

        return {vector<double>(max(0, nodeCount), infinity),vector<int>(max(0, nodeCount), -1)};
    }

    vector<double> shortestDistance(nodeCount, infinity);
    vector<int> previous(nodeCount, -1);
    shortestDistance[startNode] = 0.0;


    using QueueNode = pair<double, int>;

    priority_queue<QueueNode,vector<QueueNode>,greater<QueueNode>> minHeap;


    minHeap.push({0.0, startNode});

    while (!minHeap.empty())
    {
        QueueNode current = minHeap.top();
        minHeap.pop();

        double currentDistance = current.first;
        int currentNode = current.second;

        if (currentDistance != shortestDistance[currentNode])
            continue;

        const vector<Edge>& edgeList = graph.getNeighbors(currentNode);

        for (const Edge& edge : edgeList)
        {
            const int nextNode = edge.to;
            const double newCost = edge.cost;

            if (shortestDistance[nextNode] >shortestDistance[currentNode] + newCost)
            {
                shortestDistance[nextNode] =shortestDistance[currentNode] + newCost;

                previous[nextNode] = currentNode;

                minHeap.push({shortestDistance[nextNode],nextNode});
            }
        }
    }

    ShortestPathResult result;

    result.distances = move(shortestDistance);
    result.previousNodes = move(previous);

    return result;
}

vector<int> reconstructPath(int startNode,int destinationNode,const vector<int>& previousNodes)
{
    const int nodeCount = static_cast<int>(previousNodes.size());

    if (startNode < 0 || startNode >= nodeCount ||destinationNode < 0 || destinationNode >= nodeCount)
        return {};
    

    vector<int> finalPath;

    int currentNode = destinationNode;
    int visitedNodes = 0;

    while (currentNode != -1 && visitedNodes <= nodeCount)
    {
        finalPath.emplace_back(currentNode);

        if (currentNode == startNode)
            break;

        currentNode = previousNodes[currentNode];
        ++visitedNodes;
    }

    if (finalPath.empty() || finalPath.back() != startNode ||visitedNodes > nodeCount)
        return {};

    reverse(finalPath.begin(), finalPath.end());

    return finalPath;
}
