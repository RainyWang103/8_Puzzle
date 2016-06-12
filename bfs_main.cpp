//
//  bfs_main.cpp
//  1.a2_Uninformed_bfs
//
//  Created by WangYuli on 7/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//
/* Please read the following description first----------------------------------------------------------------------------------
 
 This program is done by uninformed breadth-first search algorithm, a few notes as follows:
 0. IDE for programming: Xcode
    Language: c++
 1. The 8-puzzle problem is stored by using 2-D arrays, with '0' to denote the empty space
    e.g. 123
         056    -> array[3][3]={{1,2,3},{0,5,6},{7,8,9}};
         789
 2. Data structures: map (for memory tree in checking replication), queue (for BFS)
 3. Description of the 3 header files:
    "shared_Node.h": [lowest hierarchy] defines the Node struct, overloads operator '<' '=' and '=='
    "shared_Successor.h": an independent class named Successor, generating valid child state for any parent state
    "bfs_Function.h": implements function to check if(target==goal) and expand node when false,
                  also specify debug function to print out nodes during process
 4. I have also included some test cases (in comment)to initialize the state
    some are marked with ending_Depth, and no. of nodes stored in tree
 
    Description end-------------------------------------------------------------------------------------------------------------
*/

#include <iostream>
#include <map>
#include <queue>
#include "bfs_Functions.h"
using namespace std;

void bfs_search(Node root, Node goalNode)     // BFS_Search algorithm function, ExpandNode() is in Node&op.h
{
    map<Node,int> tree;
    queue<Node> myQueue;
    bool goalReached = false;
    int finaldepth = 0;
    
    //search start
    tree[root]=0;
    bfs_ExpandNode(root, goalNode, goalReached, finaldepth,tree, myQueue);
    while(!goalReached && !myQueue.empty())
    {
        Node toCompare = myQueue.front(); myQueue.pop();
        bfs_ExpandNode(toCompare, goalNode, goalReached, finaldepth,tree, myQueue);
    }
    
    if(goalReached)
    {
        cout<<endl<<"Success!"<<endl;
        cout<<"----------------------------From"<<endl;
        PrintNode(root, tree);
        cout<<"-----------Use uninformed BFS to"<<endl;
        PrintNode(goalNode, tree);
        cout<<"--------------------------------"<<endl;
        cout<<"Number of Moves = "<<finaldepth<<endl;
        cout<<"Total number of Nodes stored in Tree = "<<tree.size()<<endl<<endl;
    }
    else
    {
       cout<<endl<<"OOPS!!!!!!Fail!"<<endl;
    }
}


int main() {                                   //main function
    
    int initialState[3][3]={
        {7,2,4},{5,0,6},{8,3,1}
        
        //standard case: moves: 26
        //time spent if print out nothing but final output: 2s
        //no. of nodes stored in map: 164918
        
        //{1,2,0},{3,4,5},{6,7,8}//test case:2
        //{1,2,5},{3,4,0},{6,7,8}//test case:3
        //{1,2,5},{3,4,8},{6,7,0}//test case:4
        //{1,2,5},{3,4,8},{6,7,0}//test case:4
        //{1,2,5},{3,4,8},{6,0,7}//test case:5
        //{1,2,5},{3,4,8},{0,6,7}//test case:6
        //{1,2,5},{3,7,0},{6,8,4}//test case:7
        //{1,2,5},{3,0,7},{6,8,4}//test case:8
        //{1,2,5},{0,3,7},{6,8,4}//test case:9
        //{0,2,5},{1,3,7},{6,8,4}//test case:10
        //{2,0,5},{1,3,7},{6,8,4}//test case:11
        //{2,5,0},{1,3,7},{6,8,4}//test case:12
        //{2,5,7},{1,3,0},{6,8,4}//test case:13
        //{2,5,7},{1,0,3},{6,8,4}//test case:14
        //{2,5,7},{0,1,3},{6,8,4}//test case:15
        //{2,5,7},{6,1,3},{0,8,4}//test case:16
        //{2,5,7},{6,1,3},{8,0,4}//test case:17, 12676
        //{2,5,7},{6,1,3},{8,4,0}//test case:18, 17428
        //{2,5,7},{6,1,0},{8,4,3}//test case:19, 39591
        //{2,5,7},{6,0,1},{8,4,3}//test case:20, 53478
        //{2,5,7},{0,6,1},{8,4,3}//test case:21,
        //{2,5,0},{7,6,1},{8,4,3}//test case:22,
    };
    int goalState[][3]={
        {0,1,2},{3,4,5},{6,7,8}
    };
    
    Node root (initialState, 0); Node goal(goalState,-1);
    bfs_search(root, goal);
    
    return 0;
}



