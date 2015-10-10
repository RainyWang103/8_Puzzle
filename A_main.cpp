//
//  main.cpp
//  1.c1_A_MIS
//
//  Created by WangYuli on 9/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//
//  This program is done by A* algorithm
//  The program organization is similar to the uninformed BFS one, but not use queue/stack
//  It finds best node by search through the whole memory and choose only one to expand
//  The search method can be choose to type in: "MIS" or "MAN"
//  It also reuses the "shared_Node.h" & "shared_Successor.h"

#include <iostream>
#include <map>
#include "A_Functions.h"
using namespace std;

void Heuristic_Search(Node root, Node goal, const string& command)
{
    std::map<Node,bool> memory; //value indicates if it's expanded or not
    bool goalReached = false;
    int finalDepth = 0;
    
    root.cost = (command=="MIS")? H_Mis(root.state) : H_Manhattan(root.state);
    memory[root]=false; //add to map as unexpanded
    
    Node current = root;
    if(current==goal) goalReached = true;
    
    while(!goalReached){
            Heuristic_ExpandTarget(current, goal, goalReached, finalDepth, memory,command);
            current = BestNext(memory);
    }
    if(goalReached)
    {
        cout<<endl<<"Success!"<<endl;
        cout<<"----------------------------From"<<endl;
        PrintNode(root);
        cout<<"----------------Use A* search to"<<endl;
        PrintNode(goal);
        cout<<"Number of Moves = "<<finalDepth<<endl;
        cout<<"Total number of Nodes stored = "<<memory.size()<<endl<<endl;
    }
    else
    {
        cout<<endl<<"OOPS!!!!!!Fail!"<<endl;
    }
}


int main() {
    int initialState[3][3]={
        {7,2,4},{5,0,6},{8,3,1}
        
        //standard case: moves: 26
        //time spent if print out nothing but final output: h1(n)-- 1min   ; h2(n)-- 2s
        //no. of nodes stored in map: h1(n)--62443    ; h2(n)-- 6172
        
        //{1,0,2},{3,4,5},{6,7,8}//test case:1
        //{1,2,0},{3,4,5},{6,7,8}//test case:2
        //{1,2,5},{3,4,0},{6,7,8}//test case:3
        //{1,2,5},{3,4,8},{6,7,0}//test case:4
        //{1,2,5},{3,4,8},{6,0,7}//test case:5
        //{1,2,5},{3,4,8},{0,6,7}//test case:6
        //{1,2,5},{0,4,8},{3,6,7}//test case:7.2
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
        //{2,5,7},{6,1,3},{8,0,4}//test case:17, 1286
        //{2,5,7},{6,1,3},{8,4,0}//test case:18, 1816
        //{2,5,7},{6,1,0},{8,4,3}//test case:19, 3289
        //{2,5,7},{6,0,1},{8,4,3}//test case:20, 5931
        //{2,5,7},{0,6,1},{8,4,3}//test case:21
        //{2,5,0},{7,6,1},{8,4,3}//test case:22
    };
    int goalState[][3]={
        {0,1,2},{3,4,5},{6,7,8}
    };
    
    string command;
    Node root (initialState, 0); Node goal(goalState,-1);
    cout<<"-------------A* Search------------"<<endl;
    cout<<"-----------Two Heurstics----------"<<endl<<endl;
    cout<<"Misplacement(MIS) || Manhattan(MAN)"<<endl<<endl;
    cout<<"Choose: ";
    cin>>command;
    cout<<endl<<"----------------------------------"<<endl
    <<"********** RUNNING NOW ***********"<<endl;
    if(command=="MIS"){
        cout<<"***** Use Misplacement Tiles *****"<<endl;
    }
    else {
        cout<<"** Use Total Manhattan distance **"<<endl;
    }
    
    cout<<"----------------------------------"<<endl<<endl;
    
    Heuristic_Search(root, goal, command);
    
    return 0;
}
