//
//  main.cpp
//  BathroomStalls
//
//  Created by Yue wei Yang on 5/10/17.
//  Copyright © 2017 Yue wei Yang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

using namespace std;


/*bool myfunction (int i,int j) { return (i>j); }

vector<long int> bathStalls(long int N,long int K){
    vector<long int> result;
    vector<long int> stalls;
    
    stalls.push_back(N);
    make_heap(stalls.begin(), stalls.end());
    long int min,max;
    for (size_t person=0;person<K-1;person++){
        
        
        long int num = stalls.front()-1;
        
        min = num/2;
        max = num-min;
        
        
        
        
        if(max!=0){
            stalls.push_back(max);
            push_heap(stalls.begin(), stalls.end());
        }
        
        if (min!=0){
            stalls.push_back(min);
            push_heap(stalls.begin(), stalls.end());
        }
        
        
        pop_heap(stalls.begin(), stalls.end());
        stalls.pop_back();
        
    }
    
    min = (stalls.front()-1)/2;
    max = stalls.front()-1-min;
    result.push_back(max);
    result.push_back(min);
    
    return result;
}*/

vector<long int> bathStalls(long int N,long int K){
    vector<long int> result;
    long int max =0,min=0,NUM;
    
    long int temp = N;
    long int sum = 1;
    long int num = 1;
    
    while (sum<K){
        num *=2;
        sum +=num;
        temp /=2;
    }
    
    if (sum-K>=(temp+1)*num-N-1){
        NUM = temp;
    }
    else {
        NUM = temp-1;
    }
    
   
    min = (NUM-1)/2;
    max = (NUM-1)-min;
    
    result.push_back(max);
    result.push_back(min);
    
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
        char* enptr;
        long int N = strtol(lines[i].c_str(),&enptr,10);
        long int K = strtol(enptr, &enptr, 10);
        vector<long int> S = bathStalls(N, K);
        output<<"Case #"<<i<<": "<<S[0]<<" "<<S[1]<<endl;
    }

    
    return 0;
}
