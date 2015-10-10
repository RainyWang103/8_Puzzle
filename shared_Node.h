//
//  Node.h
//  1.a2_Uninformed_bfs
//
//  Created by WangYuli on 8/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Node_h
#define Node_h
using namespace std;
struct Node {                                   // structure to store states
    // Member variables
    int state[3][3];    // the state content, stored in 2-dimensional array, '0' denotes empty space
    int depth;
    int cost;        //for A* only
    
    // Node constructors
    Node(){}
    Node(const int input[][3], const int& input_depth) {
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                state[i][j] = input[i][j];
        depth = input_depth;
    }
    
    void operator=(const Node& a) {                     // Assignment operator overloading for copying
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                state[i][j] = a.state[i][j];
        depth = a.depth;
    }
};

bool operator==(const Node& a, const Node& b) {         //== operator overloading for compare two nodes
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(a.state[i][j]!=b.state[i][j])
                return false;
    return true;
}

bool operator<(const Node& a, const Node& b){           //< operator overloading for consistency of map    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if(a.state[i][j]<b.state[i][j]) return true;
            else if(a.state[i][j]>b.state[i][j]) return false;
        }
    return false;
}

#endif /* Node_h */
