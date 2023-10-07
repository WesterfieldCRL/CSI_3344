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

private:
    map<T, std::set<T>> adjacencyList;
};

template<typename T>
Graph<T>::Graph() {
    adjacencyList = map<T, set<T>>();
}

template<typename T>
void Graph<T>::addVertex(T vertex) {
    adjacencyList[vertex] = set<T>();
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

#endif
