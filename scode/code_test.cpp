#include <string.h>
#include <vector>
#include <iostream>
#include "str_int.h"

using namespace std;
using namespace adgMod;

int main(){

    vector<string> vstr;
    vstr.push_back("aab");
    vstr.push_back("lbdd");
    vstr.push_back("bcb");
    vstr.push_back("bc");

    vector<double> ack = toCode(vstr);
    
    for (int i = 0; i < ack.size(); i++)
        cout << i << ": " << vstr[i] << " -> " << ack[i] << endl; 
    
    return 0;
}