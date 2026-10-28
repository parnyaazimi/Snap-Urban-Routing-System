#include "bellman_ford.h"
#include <limits>
#include <algorithm>

using namespace std;

vector<int> BellmanFord::buildPath(int source, int target, const vector<int>& parent)
{
    vector<int> path;

    int current=target;

    while (current != -1)
    {
        path.push_back(current);

        if (current == source)
            break;

        current=parent[current];
    }

    reverse(path.begin(), path.end());

    if (path.empty() || path[0] != source)
    {
        path.clear();
    }

    return path;
}

BellmanFordResult BellmanFord::run(const Graph& graph)
{
    int n=graph.getSize();
    int source=graph.getSource();
    int target=graph.getTarget();
    const double INF=numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    dist[source]=0;
    const vector<Edge>& edges=graph.getAllEdges();
    for (int i=0;i<n-1;i++)
    {
        bool changed=false;
        for (const Edge& edge:edges)
        {
            int u=edge.from;
            int v=edge.to;
            double cost=edge.cost;
            if (dist[u] != INF && dist[v] > dist[u] + cost)
            {
                dist[v]=dist[u] + cost;
                parent[v]=u;
                changed=true;
            }
        }
        
        if (!changed)
            break;
    }
    bool hasNegativeCycle=false;
    for (const Edge& edge:edges)
    {
        int u=edge.from;
        int v=edge.to;
        double cost=edge.cost;
        if (dist[u] != INF && dist[v] > dist[u] + cost)
        {
            hasNegativeCycle=true;
            break;
        }
    }
    vector<int> path;
    if (!hasNegativeCycle && dist[target] != INF)
        path=buildPath(source, target, parent);
    BellmanFordResult result;
    result.hasNegativeCycle=hasNegativeCycle;
    result.dist=dist;
    result.parent=parent;
    result.path=path;
    return result;
}

BellmanFordResult BellmanFord::run(const Graph& graph, int source, int target)
{
    int n=graph.getSize();
    const double INF=numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    dist[source]=0;
    const vector<Edge>& edges=graph.getAllEdges();
    for (int i=0;i<n-1;i++)
    {
        bool changed=false;
        for (const Edge& edge:edges)
        {
            int u=edge.from;
            int v=edge.to;
            double cost=edge.cost;
            if (dist[u] != INF && dist[v] > dist[u] + cost)
            {
                dist[v]=dist[u] + cost;
                parent[v]=u;
                changed=true;
            }
        }
        if (!changed)
            break;
    }
    bool hasNegativeCycle=false;
    for (const Edge& edge : edges)
    {
        int u=edge.from;
        int v=edge.to;
        double cost=edge.cost;
        if (dist[u] != INF && dist[v] > dist[u] + cost)
        {
            hasNegativeCycle=true;
            break;
        }
    }
    vector<int> path;
    if (!hasNegativeCycle && dist[target] != INF)
        path=buildPath(source, target, parent);
    BellmanFordResult result;
    result.hasNegativeCycle=hasNegativeCycle;
    result.dist=dist;
    result.parent=parent;
    result.path=path;
    return result;
}