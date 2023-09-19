#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <bits/stdc++.h>

using namespace std;

int main() 
{
    ofstream out;
    int lines = 10000;
    int randomOut[lines];
    int reverseOut[lines];

    mt19937 generator{random_device{}()};
    //modify range according to your need "A-Z","a-z" or "0-9" or whatever you need.
    uniform_int_distribution<int> distribution{'0', '9'};

    srand(time(0));

    

    

    for (int i = 0; i < lines; i++)
    {
        int generate_len = rand()%5+1;
        string rand_str(generate_len, '\0');
        for(auto& dis: rand_str)
            dis = distribution(generator);
        randomOut[i] = stoi(rand_str);
        reverseOut[i] = stoi(rand_str);
    }

    out.open("QuickSort10k.txt");

    for (int i = 0; i < lines; i++)
    {
        out << randomOut[i] << "\n" << endl;
    }

    out.close();

    out.open("QuickSort10kR.txt");

    sort(reverseOut, reverseOut + lines, greater<int>());

    for (int i = 0; i < lines; i++)
    {
        out << reverseOut[i] << "\n" << endl;
    }

    out.close();

    out.open("QuickSort10kSemi2k.txt");

    return 0;
}