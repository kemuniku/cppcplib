#pragma once
#include <string>
#include <vector>

std::vector<std::pair<char,int>> run_length_encode(std::string s){
    std::vector<std::pair<char,int>> res;
    int n = s.size();
    for(int i = 0; i < n;){
        int j = i;
        while(j < n && s[j] == s[i]) j++;
        res.push_back({s[i],j-i});
        i = j;
    }
    return res;
}