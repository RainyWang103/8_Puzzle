//
//  ids_main.cpp
//  1.b_IDS
//
//  Created by WangYuli on 8/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.

//  This program is done by iterative deepening search algorithm
//  The program organization is similar to the uninformed BFS one, but replace queue with stack
//  It also reuses the "shared_Node.h" & "shared_Successor.h"

#include <iostream>
#include <map>
#include <stack>
#include "ids_Functions.h"
using namespace std;

void Depth_Limited_Search(Node root, Node goalNode, int limit, bool& accomplish, long long& totalSize)
{
    std::map<Node, int> tree; stack<Node> myStack;
    
    tree[root]=0;
    if(root == goalNode) accomplish = true;
    
    ids_ExpandNode(root, goalNode, accomplish, limit,tree, myStack);
    while(!accomplish&&!myStack.empty())
    {
        Node toCompare = myStack.top(); myStack.pop();
        ids_ExpandNode(toCompare, goalNode, accomplish, limit,tree, myStack);
    }
    long long this_size = tree.size();
    totalSize += this_size;
    
    if(accomplish)
    {
        cout<<endl<<"Success!"<<endl;
        cout<<"----------------------------From"<<endl;
        PrintNode(root, tree);
        cout<<"----------------------Use IDS to"<<endl;
        PrintNode(goalNode, tree);
        cout<<"--------------------------------"<<endl;
        cout<<"Number of Moves = "<<limit<<endl;
        cout<<"Number of Nodes in Tree depth("<<limit<<") = "<<this_size<<endl;
        cout<<"Total number of nodes in all trees = "<<totalSize<<endl<<endl;
    }
    else
    {
        cout<<"Finish in depth "<<limit<<endl;
    }
    
}

void IDS_search(Node root, Node goalNode)
{
    bool goalReached = false;
    int depthLimit = 0;
    long long totalSpace = 0;
    while(!goalReached)
    {
        cout<<"Checking Depth limit = "<<depthLimit<<" ------------------"<<endl;
        Depth_Limited_Search(root, goalNode, depthLimit, goalReached, totalSpace);
        depthLimit++;
    }
    
    if(!goalReached) {
        cout<<endl<<"OOPS!!!!!!Fail!"<<endl; //For safety warning
    }
}

int main() {
    
    int initialState[3][3]={
        {7,2,4},{5,0,6},{8,3,1}
        
        //standard case: moves: 26
        //time spent if print out nothing but final output: 8s
        //no. of nodes stored in map (depth = 26): 160596
        //no. of nodes in all trees: 825472
        
        //{0,1,2},{3,4,5},{6,7,8}//test case:0
        //{1,0,2},{3,4,5},{6,7,8}//test case:1
        //{1,2,0},{3,4,5},{6,7,8}//test case:2
        //{1,2,5},{3,4,0},{6,7,8}//test case:3
        //{1,2,5},{3,4,8},{6,7,0}//test case:4
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
        //{2,5,7},{6,1,3},{8,0,4}//test case:17, 12622,34904
        //{2,5,7},{6,1,3},{8,4,0}//test case:18, 17376, 48756
        //{2,5,7},{6,1,0},{8,4,3}//test case:19, 10060, 64962
        //{2,5,7},{6,0,1},{8,4,3}//test case:20, 34931, 128344
        //{2,5,7},{0,6,1},{8,4,3}//test case:21
        //{2,5,0},{7,6,1},{8,4,3}//test case:22
    };
    int goalState[][3]={
        {0,1,2},{3,4,5},{6,7,8}
    };
    
    Node root (initialState, 0); Node goal(goalState,-1); //-1 stands for not found
    IDS_search(root, goal);

    return 0;
}
