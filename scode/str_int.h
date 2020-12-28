#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>  
using  namespace std;

// class Code{
//     public:
//         vector<int> toCode(vector<string> keys);
// };

//vector<int> Code::toCode(vector<string> keys){

vector<int> toCode(vector<string> keys){
    vector<char> based_char;
    vector<int> based_num;
    int pre_ba;
    int based = 1;

    vector<int> turn;
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
        int num = 0;
        for (int j = 0; j < keys[i].length(); j++){
            num += based_num[j] * (int)(keys[i][j] - based_char[j]);
        }
        
        turn.push_back(num);
    }
    // for (int i = 0; i < based_num.size(); i++)
    //     cout << i << "_based_num: " << based_num[i] << endl; 
    // for (int i = 0; i < based_char.size(); i++)
    //     cout << i << "_based_char: " << based_char[i] << endl; 
    return turn;
}