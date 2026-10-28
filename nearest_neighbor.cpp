#include "nearest_neighbor.h"
#include "dijkstra.h"
#include "bellman_ford.h"
#include <algorithm>
#include <limits>

using namespace std;

struct PathQueryResult
{
    bool reachable;
    bool hasNegativeCycle;
    double cost;
    vector<int> path;
};

static PathQueryResult shortestPathBetween(const Graph& graph, int source, int target)
{
    PathQueryResult result;
    result.reachable = false;
    result.hasNegativeCycle = false;
    result.cost = numeric_limits<double>::infinity();

    if (graph.containsNegativeEdge())
    {
        BellmanFordResult bellmanResult = BellmanFord::run(graph, source, target);

        if (bellmanResult.hasNegativeCycle)
        {
            result.hasNegativeCycle = true;
            return result;
        }

        if (!bellmanResult.path.empty())
        {
            result.reachable = true;
            result.cost = bellmanResult.dist[target];
            result.path = bellmanResult.path;
        }
    }
    else
    {
        ShortestPathResult dijkstraResult = dijkstra(graph, source);
        vector<int> path = reconstructPath(source, target, dijkstraResult.previousNodes);

        if (!path.empty())
        {
            result.reachable = true;
            result.cost = dijkstraResult.distances[target];
            result.path = path;
        }
    }

    return result;
}

NearestNeighborResult nearestNeighborRoute(const Graph& graph,int start,vector<int> destinations)
{
    NearestNeighborResult result;
    result.success = false;
    result.hasNegativeCycle = false;
    result.totalCost = 0.0;
    result.route.clear();

    if (start < 0 || start >= graph.getSize())// برسی معتبر بودن مبدا 
    {
        result.message = "Invalid start node.";
        return result;
    }

    for (int node : destinations)//برسی معتبر بودن مقصد ها
    {
        if (node < 0 || node >= graph.getSize())
        {
            result.message = "Invalid destination node.";
            return result;
        }
    }

    vector<int> unvisited = destinations;// یک لیست برای نگه داری مقصدهایی که هنوز به آنها نرفتیم
    result.route.push_back(start);
    int current = start;
    while (!unvisited.empty()) // تا زمانی که به همه مقصد ها بروی نزدیک ترین مقصد به مبدا فعلی را پیدا کن
    {
        int bestIndex = -1;
        double bestCost = numeric_limits<double>::infinity();
        vector<int> bestPath;

        for (int i = 0; i < (int)unvisited.size(); i++) // پیدا کردن نزدیکترین مقصد به مبدا فعلی
        {
            int candidate = unvisited[i];
            PathQueryResult pathResult = shortestPathBetween(graph, current, candidate);
            if (pathResult.hasNegativeCycle) // اگر دور منفی داریم 
            {
                result.hasNegativeCycle = true;
                result.message = "Negative cycle found.";
                return result;
            }
            if (pathResult.reachable && pathResult.cost < bestCost) // درصورتی که این مقصد از قبلی ها بهتره مقادیر را به روز کن
            {
                bestCost = pathResult.cost;
                bestIndex = i;
                bestPath = pathResult.path;
            }
        }

        if (bestIndex == -1)// اگر مقصدی یافت نشد پیام بده و خارج شو
        {
            result.message = "No reachable destination found.";
            return result;
        }

        for (int i = 1; i < (int)bestPath.size(); i++) // به روز کردن مسیر
        {
            result.route.push_back(bestPath[i]);
        }
        result.totalCost += bestCost; // به روز کردن هزینه
        current = unvisited[bestIndex]; // به روز رسانی مبدا
        unvisited.erase(unvisited.begin() + bestIndex); // مقصدی که بهش رفتیم رو از لیست مقصد های ویزیت نشده خارج کن
    }

    PathQueryResult returnPath = shortestPathBetween(graph, current, start);  // بعد رفتن به همه مقصد ها به مبدا باز گردد

    if (returnPath.hasNegativeCycle) // اگر دور منفی داشتیم پیام بده و خارج شو
    {
        result.hasNegativeCycle = true;
        result.message = "Negative cycle found.";
        return result;
    }

    if (!returnPath.reachable) // اگر راه بازگشت به مبدا نداریم پیام بده و خارج شو
    {
        result.message = "No path exists to return to the start node.";
        return result;
    }

    for (int i = 1; i < (int)returnPath.path.size(); i++) // به روز کردن مسیر طی شده تا الان
    {
        result.route.push_back(returnPath.path[i]);
    }

    result.totalCost += returnPath.cost;
    result.success = true;
    result.message = "Multi-destination route created successfully.";

    return result;
}