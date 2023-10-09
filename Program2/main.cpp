/* CSI 3334
 * Programming Assignment 2
 * Filename: main.cpp
 * Student name: Wesley Anastasi
 * version: 1.0
 * 
 * This file contains the driver for the this project. It reads in a list of
 * members and the languages they speak and understand from standard input and
 * uses a graph to determine the minimum number of members that need to be
 * present at a meeting to ensure that all members can understand at least one
 * other member. The program will print the minimum number of members that 
 * need to be removed to ensure that all members can understand at least 
 * one other member.
 */

#include "graph.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct Member
{
    public: 
    vector<string> langSpoken;
    vector<string> langUnderstood;
    string name;

};

/**
 * getMembers
 *
 * This function reads in a list of members and the languages they speak and
 * understand from a file and returns a vector of members.
 * 
 * Parameters:
 *   file: the file to read from
 * 
 * Return value: a vector of members
 */

vector<Member> getMembers(ifstream &file)
{
    vector<Member> members;
    string line;
    getline(file, line);
    int numMembers = stoi(line);
    for (int i = 0; i < numMembers; i++)
    {
        Member member;
        getline(file, line);
        stringstream ss(line);
        ss >> member.name;
        ss >> line;
        do
        {
            member.langSpoken.push_back(line);
            member.langUnderstood.push_back(line);
            ss >> line;
        } while (line != "*");

        while (ss >> line)
        {
            member.langUnderstood.push_back(line);
        }
        members.push_back(member);

    }
    return members;
}

/**
 * main
 *
 * This function is the driver for the program. It reads in a list of members
 * and the languages they speak and understand from standard input and adds
 * them to a graph. It then adds edges to the graph between members that speak
 * a language that another member understands. It then prints the graph.
 * 
 * Parameters:
 *   argc: the number of command line arguments
 *   argv: the command line arguments
 * 
 * Return value: 0 (indicating a successful run)
 */

int main(int argc, char* argv[]) 
{
    Graph<string> graph;
    vector<Member> members;
    if (argc != 2)
    {
        cout << "Invalid number of arguments" << endl;
        return 0;
    }
    else
    {
        string input = argv[1];

        ifstream file;
        file.open(input);

        if (file.is_open())
        {
            members = getMembers(file);
        }
        else
        {
            cout << "File not found" << endl;
            return 0;
        }

    }



    for (int i = 0; i < members.size(); i++)
    {
        graph.addVertex(members[i].name);
    }

    for (int i = 0; i < members.size(); i++) // for each member
    {
        for (int j = 0; j < members[i].langSpoken.size(); j++) // for each language spoken by member[i]
        {
            for (int k = 0; k < members.size(); k++) // for each member
            {
                if (i == k)
                {
                    continue;
                }
                else if (graph.isPath(members[i].name, members[k].name)) //check if k is already in the graph
                {
                    continue;
                }
                for (int l = 0; l < members[k].langUnderstood.size(); l++) // for each language understood by member[k]
                {
                    if (members[i].langSpoken[j] == members[k].langUnderstood[l]) // if member[i] speaks a language that member[k] understands
                    {
                        if (i != k)
                        {
                            graph.addEdge(members[i].name, members[k].name);
                        }
                    }
                }
            }
        }
    }

    graph.printGraph(cout);


    return 0;
}