#include "str_int.h"
#include<algorithm>

using namespace std;


vector<int> Code::toCode(vector<string> keys){
    vector<char[]> tmp;
    vector<char> based_char;
    vector<int> based;
    int pre_ba;
    int ba = 1;

    vector<int> turn;
    int max_lenth = 0;
    for (int i = 0; i < keys.size(); i++){
        if (keys[i].length() > max_lenth) max_lenth = keys[i].length();
        strcpy(tmp[i],keys[i].c_str());
    }
    for (int i = 0; i < max_lenth; i++){
        vector<char> compare;
        for (int j = 0; j < tmp.size(); j++) compare.push_back(tmp[j][i]);
        vector<char>::iterator max = max_element(compare.begin(), compare.end());
        vector<char>::iterator min = min_element(compare.begin(), compare.end());
        based_char.push_back(*min);
        pre_ba = *max-*min+1;
        if (i != 0) ba *= pre_ba;
        based.push_back(ba);
    }
    for (int i = 0; i < tmp.size(); i++){
        int num = 0;
        for (int j = 0; j < strlen(tmp[i]); j++){
            num += based[j] * (int)(tmp[i][j] - based_char[j]);
        }
        
        turn.push_back(num);
    }
    return turn;
}