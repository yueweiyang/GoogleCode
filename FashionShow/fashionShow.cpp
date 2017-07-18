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
#include <iostream>

using namespace std;

int main(int argc,char * argv[]){
  ifstream input;
  input.open(argv[1],ifstream::in);

  vector<string> lines;
  string s;
  while (getline(input,s)){
    lines.push_back(s);
  }

  input.close();

  ofstream output;
  output.open("output.txt");
 
  size_t nline = 1;
  size_t nCase = 0;
  while (nline<lines.size()){
    char* pEnd;
    long int N = strtol(lines[nline].c_str(),&pEnd,10);
    long int M = strtol(pEnd,&pEnd,10);
    int * crossModel = new int[N*N]();
    int * plusModel = new int[N*N]();
    int * Row = new int[N]();
    int * Col =new int[N]();
    int * DiagonalSub = new int[2*N-1]();
    int * DiagonalSum = new int[2*N-1]();
    int points = 0;
    for (long int n = 1; n<=M; n++){
      char model = lines[nline+n].c_str()[0];
      pEnd = &lines[nline+n][2];
      long int row = strtol(pEnd,&pEnd,10);
      long int col = strtol(pEnd,&pEnd,10);
      switch (model){
      case '+':
	plusModel[(row-1)*N+col-1]=1;
	DiagonalSub[row-col+N-1]=1;
	DiagonalSum[row+col-2]=1;
	points++;
	break;
      case 'x':
	crossModel[(row-1)*N+col-1]=1;
	Row[row-1]=1;
	Col[col-1]=1;
	points++;
	break;
      case 'o':
	plusModel[(row-1)*N+col-1]=1;
	crossModel[(row-1)*N+col-1]=1;
	DiagonalSub[row-col+N-1]=1;
	DiagonalSum[row+col-2]=1;
	Row[row-1]=1;
	Col[col-1]=1;
	points +=2;
	break;
      }
    }
    nline +=M+1;
    nCase++;

    output<<"Case #"<<nCase<<": ";
    cout<<"Case #"<<nCase<<": ";

    size_t cModel = 0;
    for (long int nRow=0;nRow<N;nRow++){
      if (Row[nRow]==1){
	continue;
      }
      for(long int nCol=0;nCol<N&&Row[nRow]!=1;nCol++){
	if (Col[nCol]==1){
	  continue;
	}
	else {
	  crossModel[nRow*N+nCol]=2;
	  Row[nRow]=1;
	  Col[nCol]=1;
	  points++;
	  cModel++;
	}
      }
    }

    /*    for (long int nRow=0;nRow<N;nRow++){
      for (long int nCol=0;nCol<N;nCol++){
	if (DiagonalSub[nRow-nCol+N-1]==1||DiagonalSum[nRow+nCol]==1){ continue;
	}
	else {
	  if (nRow+nCol-1>N){
	    plusModel[(N-1)*N+nRow+nCol-N+1]=2;
	    plusModel[N*N-nRow+nCol]=2;
	    points += 2;
	    cModel += 2;
	  }
	  else {
	    plusModel[nRow*N+nCol]=2;
	    points++;
	    cModel++;
	  }
	  DiagonalSub[nRow-nCol+N-1]=1;
	  DiagonalSum[nRow+nCol]=1;  
	  }
    

	if (plusModel[nRow*N+nCol]*crossModel[nRow*N+nCol]==4){
	  cModel--;
	}
      }
      }*/

      vector<int> ds;
      for(int i = 0; i < N - 1; i++) {
	ds.push_back(i);
	ds.push_back(N * 2 - i - 2);
      }
      ds.push_back(N - 1);
      
      for(int d: ds) {
	if(DiagonalSum[d]) { points++; continue; }
	int i = d < N ? d : N - 1;
	int j = d < N ? 0 : d - N + 1;
	
    for(; i >= 0 && j < N; i--, j++) {
      if(DiagonalSub[i - j + N - 1]) continue;
      
      plusModel[i*N+j] = 1;
      DiagonalSub[i - j + N - 1] = true;
      points++;
      if (plusModel[i*N+j]*crossModel[i*N+j]!=4){
	  cModel++;
      }
      break;
    }
  }

    output<<points<<" "<<cModel<<endl;
    cout<<points<<" "<<cModel<<endl;

    for (long int nRow=0;nRow<N;nRow++){
      for (long int nCol=0;nCol<N;nCol++){
	if (plusModel[nRow*N+nCol]*crossModel[nRow*N+nCol]>1){
	  output<<"o "<<nRow+1<<" "<<nCol+1<<endl;
	  cout<<"o "<<nRow+1<<" "<<nCol+1<<endl;
	}
	else if (plusModel[nRow*N+nCol]==2){
	  output<<"+ "<<nRow+1<<" "<<nCol+1<<endl;
	  cout<<"+ "<<nRow+1<<" "<<nCol+1<<endl;
	}
	else if (crossModel[nRow*N+nCol]==2){
	  output<<"x "<<nRow+1<<" "<<nCol+1<<endl;
	  cout<<"x "<<nRow+1<<" "<<nCol+1<<endl;
	}
      }
    }
    delete crossModel;
    delete plusModel;
    delete Row;
    delete Col;
    delete DiagonalSub;
    delete DiagonalSum;
  }

  return EXIT_SUCCESS;
}
