//
//  heap.h
//  BathroomStalls Google Codes
//
//  Created by Yue wei Yang on 5/11/17.
//  Copyright © 2017 Yue wei Yang. All rights reserved.
//

#ifndef heap_h
#define heap_h

template <typename T>
class BinHeap {
    class Node {
    public:
        T data;
        Node * left;
        Node * right;
        Node * parent;
    
        Node():data(NULL),left(NULL),right(NULL),parent(NULL);
        Node(const T& d,Node * p):data(d),left(NULL),right(NULL),parent(p);
    }
        
        Node * root;
        
        BinHeap():root(NULL);
        BinHeap(Node n):
    
    
public:
        void insert(const T& item){
            Node ** current = &root;
            while (*current!=NULL){
                if ((*current)->left!=NULL){
                    current = &(*current)->right;
                }
                else current = &(*current)->left;
            }
            *current = new Node(item,corrent);
            
        }
        
        const T & removeRoot(){
            
        }
};


#endif /* heap_h */
