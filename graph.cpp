#include "graph.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;


Graph::Graph()
{
    nodeCount = 0;
    sourceNode = -1;
    targetNode = -1;
    negativeEdgeExists = false;
}

int Graph::getSize() const 
{ 
    return nodeCount; 
}
int Graph::getSource() const 
{ 
    return sourceNode; 
}
int Graph::getTarget() const 
{ 
    return targetNode; 
}
bool Graph::containsNegativeEdge() const 
{ 
    return negativeEdgeExists; 
}
const vector<Edge>& Graph::getAllEdges() const
{
    return allEdges;
}
double Graph::getDelay(int node) const
{
    if (node < 0 || node >= nodeCount) 
        return 0.0;
    return delayValues[node];
}


const vector<Edge>& Graph::getNeighbors(int node) const
{
    if (node < 0 || node >= nodeCount)
    {
        cerr << "Runtime Error: Attempted to access neighbors of invalid node " << node << endl;
        static const vector<Edge> emptyEdges;
        return emptyEdges;
    }
    return adjacencyList[node];
}


double Graph::computeCost(int vertex, double d, double t, double w) const
{
    if (vertex < 0 || vertex >= nodeCount)
        return d * t * w;

    return (d * t * w) + delayValues[vertex];
}


bool Graph::loadFromFile(const string& fileName)
{
    ifstream inputFile(fileName);

    if (!inputFile)
    {
        cerr << "File Error: Cannot open or locate file '" << fileName << "'." << endl;
        return false;
    }

    int edgeCount;
    if (!(inputFile >> nodeCount >> edgeCount))
    {
        cerr << "Parse Error: Invalid or missing header (N and M) in graph file." << endl;
        return false;
    }

    if (nodeCount <= 0 || edgeCount < 0)
    {
        cerr << "Data Error: Invalid graph configuration (Nodes: " << nodeCount 
             << ", Edges: " << edgeCount << ")." << endl;
        return false;
    }

    delayValues.resize(nodeCount);
    for (int i = 0; i < nodeCount; i++)
    {
        if (!(inputFile >> delayValues[i]))
        {
            cerr << "Parse Error: Missing delay value for node " << i << endl;
            return false;
        }
        if (delayValues[i] < 0)
            cerr << "Warning: Negative delay detected at node " << i << " (" << delayValues[i] << ")." << endl;

    }

    adjacencyList.assign(nodeCount, vector<Edge>());
    allEdges.clear();
    negativeEdgeExists = false;

    for (int i = 0; i < edgeCount; i++)
    {
        int fromNode;
        int toNode;
        double d, t, w;

        if (!(inputFile >> fromNode >> toNode >> d >> t >> w))
        {
            cerr << "Parse Error: Invalid edge specification at line/index " << i + 1 << endl;
            return false;
        }

        if (fromNode < 0 || fromNode >= nodeCount || toNode < 0 || toNode >= nodeCount)
        {
            cerr << "Validation Error: Edge indices out of bounds ("
                 << fromNode << " -> " << toNode << ") at edge index " << i + 1 << endl;
            return false;
        }

        if (d < 0 || t < 0 || w < 0)
        {
            cerr << "Validation Error: Metrics (d, t, w) cannot be negative at edge "
                 << fromNode << " -> " << toNode << endl;
            return false;
        }

        Edge edge;
        edge.from = fromNode;
        edge.to = toNode;
        edge.d = d;
        edge.t = t;
        edge.w = w;
        edge.cost = computeCost(toNode, d, t, w);

        if (edge.cost < 0)
        {
            negativeEdgeExists = true;
        }

        adjacencyList[fromNode].push_back(edge);
        allEdges.push_back(edge); 
    }
    string routeLine;
    if (!getline(inputFile >> ws, routeLine))
    {
        cerr << "Parse Error: Missing source and destination nodes at the end of the file."<< endl;
        return false;
    }
    stringstream routeStream(routeLine);
    vector<int> routeNodes;
    int node;
    while (routeStream >> node)
    {
        routeNodes.push_back(node);
    }
    if (!routeStream.eof())
    {
        cerr << "Parse Error: The last line must contain only integer node numbers."<< endl;
        return false;
    }
    if (routeNodes.size() < 2)
    {
        cerr << "Parse Error: The last line must contain a source and at least one destination."<< endl;
        return false;
    }
    // اولین عدد خط آخر، مبدأ است
    sourceNode = routeNodes[0];
    if (sourceNode < 0 || sourceNode >= nodeCount)
    {
        cerr << "Validation Error: Source node "<< sourceNode<< " is out of bounds."<< endl;
        return false;
    }

    // تمام اعداد بعد از مبدأ، مقصد هستند
    vector<int> destinations;
    for (int i = 1; i < static_cast<int>(routeNodes.size()); i++)
    {
        int destination = routeNodes[i];
        if (destination < 0 || destination >= nodeCount)
        {
            cerr << "Validation Error: Destination node "<< destination<< " is out of bounds."<< endl;
            return false;
        }
        destinations.push_back(destination);
    }
    targetNode = destinations[0];// برای حالت تک مقصدی
    multiDestinations.clear();
    if (destinations.size() > 1) // اگر بیشتر از یک مقصد وجود داشته باشد
        multiDestinations = destinations;
   
    return true;
}

const vector<int>& Graph::getMultiDestinations() const
{
    return multiDestinations;
}

bool Graph::hasMultiDestinations() const
{
    return !multiDestinations.empty();
}
