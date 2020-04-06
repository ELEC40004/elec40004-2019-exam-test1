#include "mu0.hpp"

#include <iostream>

int16_t mu0_input()
{
    int x;
    cin >> x;
    if(cin.fail()){
        return -1;
    }
    if(x < -1<<15){
        return -1;
    }
    if(x >= 1<<15){
        return -1;
    }
    return x;
}

// Used to implement the OUT instruction
void mu0_output(int16_t value)
{
    cout << (int)value << endl;
}