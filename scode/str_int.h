#include <string.h>
#include <vector>
#include <iostream>
#include<algorithm>

using  namespace std;

// class Code{
//     public:
//         vector<int> toCode(vector<string> keys);
// };

//vector<int> Code::toCode(vector<string> keys){

vector<int> toCode(vector<string> keys){
    //vector<char*> tmp;
    vector<char> based_char;
    vector<int> based;
    int pre_ba;
    int ba = 1;

    vector<int> turn;
    int max_lenth = 0;
    for (int i = 0; i < keys.size(); i++){
        if (keys[i].length() > max_lenth) max_lenth = keys[i].length();
        //strcpy(tmp[i],keys[i].c_str());

    }
    for (int i = 0; i < max_lenth; i++){
        vector<char> compare;
        for (int j = 0; j < keys.size(); j++) compare.push_back(keys[j][i]);
        vector<char>::iterator max = max_element(compare.begin(), compare.end());
        vector<char>::iterator min = min_element(compare.begin(), compare.end());
        based_char.push_back(*min);
        pre_ba = *max-*min+1;
        if (i != 0) ba *= pre_ba;
        based.push_back(ba);
    }
    for (int i = 0; i < keys.size(); i++){
        int num = 0;
        for (int j = 0; j < keys[i].length(); j++){
            cout << j << ": num+ " << num << endl;
            num += based[j] * (int)(keys[i][j] - based_char[j]);
        }
        
        turn.push_back(num);
    }
    for (int i = 0; i < based.size(); i++)
        cout << i << "_based: " << based[i] << endl; 
    return turn;
}