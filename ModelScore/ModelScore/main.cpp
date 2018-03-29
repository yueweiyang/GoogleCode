//
//  main.cpp
//  ModelScore
//
//  Created by Yue wei Yang on 7/14/17.
//  Copyright © 2017 Yue wei Yang. All rights reserved.
//

#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc,char * argv[]){
    ifstream input;
    input.open(argv[1],ifstream::in);
    
    vector<string> lines;
    string s;
    while (getline(input,s)){
        lines.push_back(s);
    }
    
    ofstream output;
    output.open("output.txt");
    
    size_t nline = 1;
    size_t nCase = 0;
    while (nline<lines.size()){
        char* pEnd;
        long int N = strtol(lines[nline].c_str(),&pEnd,10);
        long int M = strtol(pEnd,&pEnd,10);
        int crossModel[N][N],plusModel[N][N],Row[N],Col[N],Diagonal[N];
        int points = 0;
        for (size_t n = 1; n<=M; n++){
            char model = lines[nline+n].c_str()[0];
            pEnd = &model+1;
            long int row = strtol(&model,&pEnd,10);
            long int col = strtol(pEnd,&pEnd,10);
            row--;col--;
            switch (model){
            case '+':
                plusModel[row][col]=1;
                Diagonal[abs(row-col)]=1;
                points++;
                break;
            case 'x':
                crossModel[row][col]=1;
                Row[row]=1;
                Col[col]=1;
                points++;
                break;
            case 'o':
                plusModel[row][col]=1;
                crossModel[row][col]=1;
                Diagonal[abs(row-col)]=1;
                Row[row]=1;
                Col[col]=1;
                points +=2;
                break;
            }
        }
        nline +=M+1;
        nCase++;
        
        output<<"Case #"<<nCase<<": ";
        
        size_t cModel = 0;
        for (size_t nRow=0;nRow<N;nRow++){
            if (Row[nRow]==1){
                continue;
            }
            for(size_t nCol=0;nCol<N;nCol++){if (Col[nCol]==1){
                continue;
            }
            else {
                crossModel[nRow][nCol]=2;
                Row[nRow]=1;
                Col[nCol]=1;
                points++;
                cModel++;
            }
            }
        }
        
        for (long int nRow=0;nRow<N;nRow++){
            for (long int nCol=0;nCol<N;nRow++){
                if (Diagonal[abs(nRow-nCol)]==1){ continue;
                }
                else {
                    plusModel[nRow][nCol]=2;
                    Diagonal[abs(nRow-nCol)]=1;
                    points++;
                    cModel++;
                }
                
                if (plusModel[nRow][nCol]*crossModel[nRow][nCol]==4){
                    cModel--;
                }
            }
        }
        
        output<<points<<" "<<cModel<<endl;
        
        for (size_t nRow=0;nRow<N;nRow++){
            for (size_t nCol=0;nCol<N;nCol++){
                if (plusModel[nRow][nCol]*crossModel[nRow][nCol]==4){
                    output<<"o "<<nRow+1<<" "<<nCol+1<<endl;
                }
                else if (plusModel[nRow][nCol]==2){   output<<"o "<<nRow+1<<" "<<nCol+1<<endl;
                }
                else if (plusModel[nRow][nCol]==2){
                    output<<"+ "<<nRow+1<<" "<<nCol+1<<endl;
                }
                else if (crossModel[nRow][nCol]==2){
                    output<<"x "<<nRow+1<<" "<<nCol+1<<endl;
                }
            }
        }
        
    }
    
    return EXIT_SUCCESS;
}
