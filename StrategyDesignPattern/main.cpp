#include <bits/stdc++.h>
using namespace std;

class Interface
{
    void function()
    {   
        cout << "basic strategy" << endl;
    }
};

class Client1 : private Interface
{
    void function()
    {   
        cout << "common strategy" << endl;
    }
};

class Client2 : private Interface
{
    void function()
    {   
        cout << "common strategy" << endl;
    }
};

class Client3 : private Interface
{
    void function()
    {   
        cout << "client3 strategy" << endl;
    }
};

int main(int argc, char* argv[])
{

    return 0;
}