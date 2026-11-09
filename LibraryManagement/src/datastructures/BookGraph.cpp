#include "BookGraph.h"

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <limits>
using namespace std;

BookGraph::BookGraph() = default;

BookGraph::~BookGraph() = default;

void BookGraph::addBook(int id) {
    adjacencyList[id];
}

void BookGraph::addEdge(int fromBookId, int toBookId) {
    adjacencyList[fromBookId].push_back(toBookId);
    adjacencyList[toBookId];
}

vector<int> BookGraph::shortestPath(int startId, int endId) const {
    unordered_map<int, int> dist;
    unordered_map<int, int> prev;
    queue<int> queue;

    if (adjacencyList.find(startId) == adjacencyList.end()) {
        return {};
    }

    dist[startId] = 0;
    queue.push(startId);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int neighbor : adjacencyList.at(current)) {
            if (dist.find(neighbor) == dist.end()) {
                dist[neighbor] = dist[current] + 1;
                prev[neighbor] = current;
                queue.push(neighbor);
                if (neighbor == endId) {
                    vector<int> path;
                    int node = endId;
                    while (node != startId) {
                        path.push_back(node);
                        node = prev[node];
                    }
                    path.push_back(startId);
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return {};
}

void BookGraph::clear() {
    adjacencyList.clear();
}
