#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long long multiply(string num1, string num2)
{
    long long result = 0;

    //check if each num is 1 digit
    if (num1.length() <= 1  && num2.length() <= 1)
    {
        return stol(num1) * stol(num2);
    }

    //split numbers into halves

    int digits = num1.length();

    string x1 = num1.substr(0,digits/2);
    string x0 = num1.substr(digits/2,digits);

    string y1 = num2.substr(0,digits/2);
    string y0 = num2.substr(digits/2,digits);

    //recursively combine
    long long a = multiply(x1,y1);
    long long b = multiply(x0,y0);
    long long c = (stol(x1) + stol(x0)) * (stol(y1) + stol(y0));

    //final result
    result = (a * pow(10,digits)) + (c - a - b) * (pow(10,digits/2)) + b;

    return result;

}

int main(int argc, char* argv[])
{
    //note: assuming here that each number is the same length and a power of 2
    //additionally, assuming each number is not negative

    cout << multiply(argv[1],argv[2]) << endl;

    return 0;
}