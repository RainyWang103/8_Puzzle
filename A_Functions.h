//
//  A_MIS_Functions.h
//  1.c1_A_MIS
//
//  Created by WangYuli on 9/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef A_MIS_Functions_h
#define A_MIS_Functions_h
#include "shared_Successor.h"
#include<iostream>
using namespace std;

int H_Mis(int state[][3])
{
    int mis = 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
        {
            if(state[i][j]!=(i*3+j)&&state[i][j]!=0)
                mis++;
        }
    return mis;
}

int Distance(int i, int j, int data)
{
    int row = data/3; int col = data%3;
    int dis = abs(row-i)+abs(col-j);
    return dis;
}

int H_Manhattan(int state[][3])
{
    int manhattan = 0;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(state[i][j]!=0)
                manhattan+=Distance(i,j,state[i][j]);
    return manhattan;
}

void PrintNode(Node a)                 // debug function to print out any given node
{
    for(int i=0; i<3;i++) {
        for(int j=0; j<3; j++)
            cout<<a.state[i][j]<<",";
        cout<<endl;
    }
    cout<<"depth = "<<a.depth<<endl;
//    cout<<"Misplacement = "<<H_Mis(a.state)<<endl;
//    cout<<"cost = "<<H_Mis(a.state)+a.depth;
//    cout<<"Manhattan = "<<H_Manhattan(a.state)<<endl;
//    cout<<"cost = "<<H_Manhattan(a.state)+a.depth;
    //cout<<endl;
}

void Heuristic_ExpandTarget(Node parent,
                            Node& goal,
                            bool& finish,           //The finish flag, updated when child reach goal
                            int& goalDepth,         //The resulting moves, updated when child reach goal
                            std::map<Node,bool>& memory,
                            const string& command)
{
    memory[parent] = true;                              //Set parent expanded
    Successor child(parent); child.MakeSuccessor();     //Make child states, waiting for expanding
    for(int i=0; i<4; i++)
        if (child.IsValid(i))       //Check if every child state is valid to use
        {
            //make the exact child node
            Node toBePush = child.GetContent(i);
            toBePush.depth = parent.depth+1;
            toBePush.cost = ((command=="MIS")? H_Mis(toBePush.state) : H_Manhattan(toBePush.state))
                            + toBePush.depth;
            
            if(toBePush == goal) {
                finish = true;
                goalDepth = toBePush.depth;
                goal.depth = toBePush.depth;
            }
            
            else if(memory.count(toBePush)==0||toBePush.depth<memory[toBePush])
            {
                memory[toBePush]=false;
            
            //Debug--------------------------------------
//            cout<<endl<<"Push Child---"<<endl;
//            PrintNode(toBePush);

            }
        }
    //Debug--------------------------------------
//    cout<<"SET THIS EXPANDED-------"<<endl;
//    cout<<memory[parent]<<endl;
//    PrintNode(parent);
}

Node BestNext(std::map<Node,bool>& memory)
{
    std::map<Node,bool>::iterator it = memory.begin();
    Node bestNode;
    int bestCost = 200;
    
    bool assigned = false;
    
    while(!assigned && it!=memory.end()) {  //Check for assign is very important here!!!!!
        if(!it->second) {
            bestNode = it->first;
            bestCost = it->first.cost;
            assigned = true;
        }
        it++;
    }
    while(it!=memory.end()) {   //Actual checking start, finding the best node to expand
        if(!it->second) // Not expanded yet
        {
            if(it->first.cost<bestCost ||                                       //Update when Lower cost
               (it->first.cost == bestCost && it->first.depth<bestNode.depth))  //Or same cost but better depth
            {
                bestCost = it->first.cost;
                bestNode = it->first;
            }
        }
        it++;
    }
//    cout<<endl<<"Check this--if !goal, expand-------"<<endl;
//    PrintNode(bestNode);
    
    return bestNode;
}
    

#endif /* A_MIS_Functions_h */
