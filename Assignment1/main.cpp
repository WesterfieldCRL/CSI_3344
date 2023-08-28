#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

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

string add(string num1, string num2)
{
    string result = "";

    int temp = 0;
    bool carry;

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

string subtract(string num1, string num2)
{
    string result = "";

    int temp = 0;
    bool borrow;

    equalize(num1, num2);

    borrow = false;

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

string multiply(string num1, string num2)
{
    string result;

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
    cout << result << endl;
    return result;

}

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
        cout << multiply("100000000000","1000000000000") << endl;
    }

    return 0;
}