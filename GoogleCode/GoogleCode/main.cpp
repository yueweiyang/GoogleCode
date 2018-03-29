//
//  main.cpp
//  GoogleCode
//
//  Created by Yue wei Yang on 5/9/17.
//  Copyright © 2017 Yue wei Yang. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

void flipPancake(char *s, long int K){
    for (long int i = 0;i<K;i++){
        if (*s=='+'){
            *s = '-';
        }
        else{
            *s = '+';
        }
        s++;
    }
    
    return;
}
string trimNumber(string s){
    size_t pos = s.find_first_of(" ");
    s.erase(pos);
    return s;
}

long int extractNumber(string s){
    char * ptr;
    char * endptr;
    ptr = strchr(s.c_str(), ' ');
    long int K = strtol(ptr,&endptr, 10);
    if (endptr==NULL){
        return -1;
    }
    else return K;
}


int main(int argc, const char * argv[]) {
    
    
    vector<string> lines;

    ifstream file;
    ofstream output;
    file.open(argv[1],ifstream::in);
    if (!file.is_open()){
        cerr<<"Cannot open file"<<endl;
        exit(EXIT_FAILURE);
    }
        string s;
    
    while (getline(file,s)){
        lines.push_back(s);
    }
    
    output.open("output.txt");
    for (int i =1;i<lines.size();i++){
        long int K = extractNumber(lines[i]);
        if (K==-1){
            cerr<<"K is not found"<<endl;
            exit(EXIT_FAILURE);
        }
        string temp = trimNumber(lines[i]);
        int iterations = 0;
        size_t pos = temp.find_first_of("-");
        char * flip;
        while (pos<=temp.length()-K){
            flip = &temp[pos];
            flipPancake(flip, K);
            pos = temp.find_first_of("-");
            iterations++;
        }
        if (pos!=string::npos){
            output<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
        }
        else output<<"Case #"<<i<<": "<<iterations<<endl;
    
    }
    
    return EXIT_SUCCESS;
}

