#include "dijkstra.h"
#include "graph.h"
#include "bellman_ford.h"
#include "nearest_neighbor.h"

#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

static void displayPath(const vector<int>& route)
{
    bool firstNode = true;

    for (int node : route)
    {
        if (!firstNode)
            cout << " -> ";

        cout << node;
        firstNode = false;
    }

    cout << endl;
}

int main()
{
    Graph graph;
    const bool loaded = graph.loadFromFile("map.txt");

    if (!loaded)
        return 1;

    const int startNode = graph.getSource();
    const int destinationNode = graph.getTarget();

    cout << "Graph loaded successfully." << endl;
    cout << "Nodes: " << graph.getSize()<< " | Source: " << startNode;

    if (!graph.hasMultiDestinations())
    {
        cout << " | Target: " << destinationNode;
    }
    cout << endl << fixed << setprecision(2);
    // حالت چندمقصدی
    if (graph.hasMultiDestinations())
    {
        cout << "[Info]: Multi-destination input found." << endl;
        cout << "---- Multi-destination route using Nearest Neighbor ----" << endl;
        if (graph.containsNegativeEdge())
            cout << "[Info]: Graph contains negative edge weights. "<< "ShortestPathCost will use Bellman-Ford." << endl;
        else
            cout << "[Info]: Graph has no negative edge weights. "<< "ShortestPathCost will use Dijkstra." << endl;
        const vector<int>& destinations = graph.getMultiDestinations();
        cout << "Destinations: ";
        displayPath(destinations);
        NearestNeighborResult multiRoute = nearestNeighborRoute(graph, startNode, destinations);
        if (!multiRoute.success)
        {
            cout << "Multi-destination routing failed: "<< multiRoute.message << endl;
            return 0;
        }
        cout << "Total route cost: " << multiRoute.totalCost << endl << "Route: ";
        displayPath(multiRoute.route);
        return 0;
    }

    // حالت تک‌ مقصدی
    if (graph.containsNegativeEdge())
    {
        cout << "[Info]: Graph contains negative edge weights. Bellman-Ford will be used." << endl;
        BellmanFordResult result = BellmanFord::run(graph);
        if (result.hasNegativeCycle)
        {
            cout << "NEGATIVE CYCLE FOUND" << endl;
            cout << "Shortest path cannot be calculated because a negative cycle exists." << endl;
            return 0;
        }

        if (result.path.empty())
        {
            cout << "Routing Notice: No path exists between node "<< startNode << " and node " << destinationNode << "." << endl;
            return 0;
        }
        cout << "Shortest distance: " << result.dist[destinationNode] << endl;
        cout << "Path: ";
        displayPath(result.path);
    }
    else
    {
        cout << "[Info]: Graph has no negative edge weights. Dijkstra will be used." << endl;
        const ShortestPathResult shortestPath = dijkstra(graph, startNode);
        vector<int> route =
            reconstructPath(startNode, destinationNode, shortestPath.previousNodes);

        if (route.empty())
        {
            cout << "Routing Notice: No path exists between node "<< startNode << " and node " << destinationNode << "." << endl;
            return 0;
        }

        cout << "Shortest distance: "<< shortestPath.distances[destinationNode] << endl;
        cout << "Path: ";
        displayPath(route);
    }

    return 0;
}