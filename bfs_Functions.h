//
//  bfs_Functions.h
//  1.a2_Uninformed_bfs
//
//  Created by WangYuli on 7/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include "shared_Successor.h"
using namespace std;

void PrintNode(Node a, map<Node,int> tree)                                      // debug function to print out any given node
{
    for(int i=0; i<3;i++) {
        for(int j=0; j<3; j++)
            cout<<a.state[i][j]<<",";
        cout<<endl;
    }
    cout<<"depth = "<<a.depth<<endl;
    //cout<<endl;
}

void bfs_ExpandNode(const Node& parent,                         //Helper for BFS_search()
                Node& goal,
                bool& finish,           //The finish flag, updated when child reach goal
                int& goalDepth,         //The resulting moves, updated when child reach goal
                map<Node,int>& tree,    //The memory to check for duplication
                queue<Node>& myQueue)   //The queue for BFS, node will be pushed into it if not in memory
{
    // expanding start
    Successor child(parent); child.MakeSuccessor();     //Make child states, waiting for expanding
    for(int i=0; i<4; i++)
        if (child.IsValid(i))       //Check if every child state is valid to use
        {
            //make the exact child node
            Node toBePush = child.GetContent(i);
            toBePush.depth = parent.depth+1;
            
            if( toBePush == goal) {          // check if child reaches goal
                finish = true;
                goalDepth = toBePush.depth;
                goal.depth = toBePush.depth;
                return;
            }
            
            else if(tree.count(toBePush)==0) // check if child is not in memory (myNote*: count is faster than find!!)
            {
//                cout<<"Add Node to Tree&Queue------------"<<endl;
//                PrintNode(toBePush,tree);                            //Debug; Comment this out will improve some performance
                
                tree[toBePush]=toBePush.depth; //add child to memory, for future replication check
                myQueue.push(toBePush);                                 //add child to queue, wait for expanding in next round
            }
        }
}

#endif /* Header_h */
