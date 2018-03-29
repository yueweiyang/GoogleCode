//
//  main.cpp
//  Tidy Numbers
//
//  Created by Yue wei Yang on 5/10/17.
//  Copyright © 2017 Yue wei Yang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

long int tidyNumber(long int num){
    vector<int> digits;
    while (num!=0){
        digits.push_back(num%10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    size_t i  =0;
    while (i!=digits.size()-1){
        if (digits[i]>digits[i+1]){
            for (size_t j = i+1;j<digits.size();j++){
                digits[j]=9;
            }
            digits[i]=digits[i]-1;
            if (i!=0){
                i--;
            }
        }
        else {
            i++;
        }
    }
    
    long int result = 0;
    for (size_t i=0;i<digits.size();i++){
        result *=10;
        result += digits[i];
    }
    
    return result;
}

int main(int argc, const char * argv[]) {
    ifstream input;
    input.open(argv[1],ifstream::in);
    if (!input.is_open()){
        cerr<<"Cannot open file"<<endl;
        exit(EXIT_FAILURE);
    }
    
    vector<string> lines;
    string s;
    
    while (getline(input, s)){
        lines.push_back(s);
    }
    
    
    ofstream output;
    output.open("output.txt");
    for (int i=1;i<lines.size();i++){
        size_t sz;
        long int number = stol(lines[i],&sz);
        output<<"Case #"<<i<<": "<<tidyNumber(number)<<endl;
    }
    
    return 0;
}
