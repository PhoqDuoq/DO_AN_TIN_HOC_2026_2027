#ifndef BOOKGRAPH_H
#define BOOKGRAPH_H

#include <unordered_map>
#include <vector>
using namespace std;

class Book;

class BookGraph {
public:
    BookGraph();
    ~BookGraph();

    void addBook(int id);
    void addEdge(int fromBookId, int toBookId);
    vector<int> shortestPath(int startId, int endId) const;
    void clear();

private:
    unordered_map<int, vector<int>> adjacencyList;
};

#endif
