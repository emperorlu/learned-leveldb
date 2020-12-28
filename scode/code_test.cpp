#include <string.h>
#include <vector>
#include <iostream>
#include "str_int.h"

using namespace std;
Code test;

int main(){

    vector<string> vstr;
    vstr.push_back("aab");
    vstr.push_back("bdd");
    vstr.push_back("bcb");
    // = ("aab", "bdd", "bcb");
    vector<int> ack = test.toCode(vstr);
    
    for (int i = 0; i < ack.size(); i++)
        cout << i << ": " << vstr[i] << " -> " << ack[i] << endl; 
    
    return 0;
}