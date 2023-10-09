/* CSI 3334
 * Programming Assignment 2
 * Filename: graph.h
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the header for the graph class. The graph class is used
 * to represent the relationships between members of a club. The graph class
 * uses an adjacency list to represent the graph.
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
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

    bool isPath(T from, T to);
        // return true if there is a path from vertex "from" to vertex "to"
        // return false otherwise

private:
    map<T, std::vector<T>> adjacencyList;
};

/**
 * Graph
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   none
 * 
 * Return value: none
 */

template<typename T>
Graph<T>::Graph() {
    adjacencyList = map<T, vector<T>>();
}

/**
 * addVertex
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   T: the vertex to add
 * 
 * Return value: none
 */

template<typename T>
void Graph<T>::addVertex(T vertex) {
    adjacencyList[vertex] = vector<T>();
}

/**
 * addEdge
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   from: the vertex to add the edge from
 *   to: the vertex to add the edge to
 * 
 * Return value: none
 */

template<typename T>
void Graph<T>::addEdge(T from, T to) {
    adjacencyList[from].push_back(to);
}

/**
 * printGraph
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   out: the output stream to print to
 * 
 * Return value: none
 */

template<typename T>
void Graph<T>::printGraph(ostream &out) {
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
        out << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            out << *it2 << " ";
        }
        out << endl;
    }
}

/**
 * isPath
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   from: the vertex to start from
 *   to: the vertex to end at
 * 
 * Return value: true if there is a path from "from" to "to", false otherwise
 */

template<typename T>
bool Graph<T>::isPath(T from, T to) {
    for (int i = 0; i < adjacencyList[from].size(); i++)
    {
        if (adjacencyList[from][i] == to)
            return true;
    }
    return false;
}

#endif
