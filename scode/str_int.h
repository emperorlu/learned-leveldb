#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>  
using  namespace std;

namespace adgMod {

vector<double> toCode(vector<string> keys){
    vector<char> based_char;
    vector<double> based_num;
    double pre_ba;
    double based = 1;

    vector<double> turn;
    int max_lenth = 0;
    for (int i = 0; i < keys.size(); i++){
        reverse(keys[i].begin(),keys[i].end());
        if (keys[i].length() > max_lenth) max_lenth = keys[i].length();
    }
    for (int i = 0; i < max_lenth; i++){
        vector<char> compare;
        for (int j = 0; j < keys.size(); j++) {
            compare.push_back(keys[j][i]);
        }
        vector<char>::iterator max = max_element(compare.begin(), compare.end());
        vector<char>::iterator min = min_element(compare.begin(), compare.end());
        based_char.push_back(*min);

        if (i != 0) based *= pre_ba;
        pre_ba = *max-*min+1;
        based_num.push_back(based);
    }
    for (int i = 0; i < keys.size(); i++){
        double num = 0;
        for (int j = 0; j < keys[i].length(); j++){
            num += based_num[j] * (double)(keys[i][j] - based_char[j]);
        }
        
        turn.push_back(num);
    }

    return turn;
}

double OnetoCode(string keys, vector<double> based_num, vector<char> based_char){
    double num = 0;
    for (int i = 0; i < keys.size(); i++){
        num += based_num[i] * (double)(keys[i] - based_char[i]);
    }
    return num;
}

}