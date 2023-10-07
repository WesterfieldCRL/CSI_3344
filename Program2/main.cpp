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
                for (int l = 0; l < members[k].langUnderstood.size(); l++) // for each language understood by member[k]
                {
                    if (members[i].langSpoken[j] == members[k].langUnderstood[l]) // if member[i] speaks a language that member[k] understands
                    {
                        graph.addEdge(members[i].name, members[k].name);
                    }
                }
            }
        }
    }

    set<string> memberSet = graph.largestStronglyConnectedComponent();

    int unintelligbleMembers = members.size()-memberSet.size();

    cout << unintelligbleMembers << endl;

    return 0;
}