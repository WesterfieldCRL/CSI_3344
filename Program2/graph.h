#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <set>
#include <map>
#include <fstream>

using namespace std;

template<typename T>
class Graph {
public:

    Graph();
        // constructor

    void addVertex(T vertex);
        // add a vertex to the graph

    void addEdge(T from, T to);
        // add an edge from vertex "from" to vertex "to"

    void printGraph(ostream &out);
        // print the graph (for debugging purposes

    set<T> getVertexSet(string);
        // get set of vertex for debugging purposes

    set<T> bfs(T start);
        // perform a breadth-first search starting at vertex "start"

    set<T> largestStronglyConnectedComponent();
        // return the largest strongly connected component of the graph

private:
    map<T, std::set<T>> adjacencyList;
    int numVertices;
};

template<typename T>
Graph<T>::Graph() {
    adjacencyList = map<T, set<T>>();
}

template<typename T>
void Graph<T>::addVertex(T vertex) {
    adjacencyList[vertex] = set<T>();
    numVertices++;
}

template<typename T>
void Graph<T>::addEdge(T from, T to) {
    adjacencyList[from].insert(to);
}

template<typename T>
void Graph<T>::printGraph(ostream &out) {
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
    {
        out << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            out << *it2 << " ";
        }
        out << endl;
    }
}

template<typename T>
set<T> Graph<T>::getVertexSet(string name)
{
    return adjacencyList[name];
}

template<typename T>
set<T> Graph<T>::bfs(T start) {
    set<T> visited;
    set<T> frontier;
    frontier.insert(start);
    while (!frontier.empty())
    {
        T current = *frontier.begin();
        frontier.erase(frontier.begin());
        visited.insert(current);
        for (auto it = adjacencyList[current].begin(); it != adjacencyList[current].end(); it++)
        {
            if (visited.find(*it) == visited.end())
            {
                frontier.insert(*it);
            }
        }
    }
    return visited;
}

template<typename T>
set<T> Graph<T>::largestStronglyConnectedComponent() {
    set<T> largest;
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)//it->first = key, it->second = set<T>
    {
        set<T> visited = bfs(it->first); //find all vertices that the vertex has a path too
        for (auto it2 = visited.begin(); it2 != visited.end(); it2++) //check if path goes both ways
        {
            set<T> visited2 = bfs(*it2); //find all vertices that the vertex has a path too
            bool containsVertex = false;
            for (auto it3 = visited2.begin(); it3 != visited2.end(); it3++)
            {
                if (it->first == *it3)
                {
                    containsVertex = true;
                    break;
                }
            }
            if (!containsVertex)//remove vertex from set
            {
                visited.erase(*it2);
            }
        }
        if (visited.size() > largest.size())
        {
            largest = visited;
        }
    }
    return largest;
}

#endif
