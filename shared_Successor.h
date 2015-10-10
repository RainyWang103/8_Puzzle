//
//  Successor.h
//  1.a_Uninformed_BFS
//
//  Created by WangYuli on 5/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Successor_h
#define Successor_h
#include "shared_Node.h"
using namespace std;

struct potentialSuc
{
    bool valid;
    Node content;
};

class Successor
{
private:
    Node parent;
    potentialSuc lrud[4]; //successors by moving 0 to: left, right, up, down
    int x,y;   //the position of (0), which is the empty box
    
    void Swap(int& a, int& b) {
        int temp = a; a=b; b=temp;
    }
    
public:
    Successor(Node input) {             //Constructor
        parent = input;
        for(int i=0; i<3;i++)
            for(int j=0;j<3;j++)
                if(parent.state[i][j]==0){x=i; y=j;} //mark the position of (0)
    }
    
    bool IsValid(int i) {               //check if a successor is valid
        if(lrud[i].valid) {return true;}
        return false;
    }
    
    void MakeSuccessor() {
        lrud[0].valid = (y==0)? false:true; //left
        lrud[1].valid = (y==2)? false:true; //right
        lrud[2].valid = (x==0)? false:true; //up
        lrud[3].valid = (x==2)? false:true; //down
        
        for(int i=0; i<4; i++)
        {
            if(IsValid(i))
            {
                // set the state array of child nodes
                lrud[i].content = parent;
                int x2=x;  int y2=y;                     //target swap postion for -1
                if(i==0||i==1){y2=(i==0)?(y2-1):(y2+1);} //for left/right
                else          {x2=(i==2)?(x2-1):(x2+1);} //for up/down
                Swap(lrud[i].content.state[x][y],lrud[i].content.state[x2][y2]); //swap (0) to an valid location
            }
        }
    }
    Node GetContent(const int& i){
        return lrud[i].content;
    }
    
};


#endif /* Successor_h */
