/*
Author: Wesley Anastasi
Class: CSI 3344
Due Date: September 1, 2023
*/

/*
This program uses Karatsuba's algorithm to multiply two large numbers
efficently. Since it is dealing with potentially very large numbers,
it uses strings to store the numbers, and then converts them to integers
when needed. This allows for numbers of any size to be multiplied, as
long as they are not negative.

equalize adds leading zeros so that the numbers will be the same in length

add and subtract to exactly what they say

multiply uses Karatsuba's algorithm to multiply the two numbers.

*/


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/**
 * equalize
 * 
 * adds leading zeros to the shorter string
 * 
 * Parameters:
 *   num1 - first number passed by reference
 *   num2 - second number passed by reference
 * 
 * Return value: none
 */
void equalize(string &num1, string &num2)
{
    //check that each num is the same length
    if (num1.length() > num2.length())
    {
        while (num1.length() > num2.length())
        {
            num2 = "0" + num2;
        }
    }
    else if (num2.length() > num1.length())
    {
        while (num2.length() > num1.length())
        {
            num1 = "0" + num1;
        }
    }
}

/**
 * add
 * 
 * adds two (potentially) large numbers together
 * 
 * Parameters:
 *   num1 - first number passed by reference
 *   num2 - second number passed by reference
 * 
 * Return value: string containing the sum
 */
string add(string num1, string num2)
{
    string result = "";

    int temp = 0;
    bool carry = false;

    equalize(num1, num2);

    for (int i = num1.length()-1; i >= 0; i--)
    {
        temp = stoi(num1.substr(i,1)) + stoi(num2.substr(i,1));
        if (carry)
        {
            temp++;
        }
        if (temp >= 10)
        {
            carry = true;
            temp -= 10;
        }
        else
        {
            carry = false;
        }
        result = to_string(temp) + result;
    }

    if (carry)
    {
        result = "1" + result;
    }

    //remove leading 0s
    while (result.length() > 1 && result[0] == '0')
    {
        result = result.substr(1,result.length());
    }

    return result;
}

/**
 * subtract
 * 
 * subtracts two (potentially) large numbers
 * 
 * Parameters:
 *   num1 - first number passed by reference
 *   num2 - second number passed by reference
 * 
 * Return value: string containing the difference
 */
string subtract(string num1, string num2)
{
    string result = "";

    int temp = 0;
    bool borrow = false;

    equalize(num1, num2);

    for (int i = num1.length()-1; i >= 0; i--)
    {
        temp = stoi(num1.substr(i,1)) - stoi(num2.substr(i,1));
        if (borrow)
        {
            temp--;
        }
        if (temp < 0)
        {
            borrow = true;
            temp += 10;
        }
        else
        {
            borrow = false;
        }
        result = to_string(temp) + result;
    }

    //remove leading 0s
    while (result.length() > 1 && result[0] == '0')
    {
        result = result.substr(1,result.length());
    }

    return result;
}

/**
 * multiply
 * 
 * multiplies two (potentially) large numbers
 * using Karatsuba's algorithm
 * 
 * Parameters:
 *   num1 - first number passed by reference
 *   num2 - second number passed by reference
 * 
 * Return value: string containing the product
 */
string multiply(string num1, string num2)
{
    string result;
    bool isNegative;
    if (num1[0] == '-' && num2[0] == '-')
    {
        isNegative = false;
        num1 = num1.substr(1,num1.length());
        num2 = num2.substr(1,num2.length());
    }
    else if (num1[0] == '-' || num2[0] == '-')
    {
        isNegative = true;
        if (num1[0] == '-')
        {
            num1 = num1.substr(1,num1.length());
        }
        else
        {
            num2 = num2.substr(1,num2.length());
        }
    }
    else
    {
        isNegative = false;
    }

    //check if each num is 1 digit
    if (num1.length() == 1  && num2.length() == 1)
    {
        return to_string(stoi(num1) * stoi(num2));
    }

    //check that each num is a power of 2
    if (num1.length() % 2 != 0)
    {
        num1 = "0" + num1;
    }
    if (num2.length() % 2 != 0)
    {
        num2 = "0" + num2;
    }

    equalize(num1, num2);

    //split numbers into halves

    int digits = num1.length();

    string x1 = num1.substr(0,digits/2);
    string x0 = num1.substr(digits/2,digits);

    string y1 = num2.substr(0,digits/2);
    string y0 = num2.substr(digits/2,digits);

    //recursively combine
    string a = multiply(x1,y1);
    string b = multiply(x0,y0);
    string c = multiply(add(x1,x0), add(y1,y0));

    //final result

    string sub = subtract(subtract(c, a), b);
    //string subString = to_string(sub);
    for (int i = 0; i < digits/2; i++)
    {
        sub += "0";
    }

    //string aString = to_string(a);
    for (int i = 0; i < digits; i++)
    {
        a += "0";
    }

    result = add(add(a, sub), b);
    if (isNegative)
    {
        result = "-" + result;
    }
    return result;

}

/**
 * main
 * 
 * gets input from the user or a file, or failing that,
 * multiplies 42 * 42
 * 
 * Parameters:
 *   argc - number of arguments passed
 *   argv - array of arguments passed
 * 
 * Return value: integer representing success or failure
 */
int main(int argc, char* argv[])
{
    //assumes each number is not negative

    if (argc == 2)
    {
        string input = argv[1];

        ifstream file;
        file.open(input);

        if (file.is_open())
        {
            string num1;
            string num2;

            getline(file,num1);
            getline(file,num2);

            cout << multiply(num1,num2) << endl;
        }
        else
        {
            cout << "File not found" << endl;
        }

    }
    else if (argc == 3)
    {
        cout << multiply(argv[1],argv[2]) << endl;
    }
    else
    {
        cout << "No input, multiplying 42 * 42" << endl;
        cout << multiply("42","42") << endl;
    }

    return 0;
}