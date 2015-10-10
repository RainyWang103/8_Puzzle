//
//  ids_functions.h
//  1.b_IDS
//
//  Created by WangYuli on 8/10/2015.
//  Copyright © 2015 WangYuli. All rights reserved.
//

#ifndef ids_functions_h
#define ids_functions_h
#include "shared_Successor.h"
#include <map>
using namespace std;

void PrintNode(Node a, std::map<Node,int>& tree)     // debug function to print out any given node
{
    for(int i=0; i<3;i++) {
        for(int j=0; j<3; j++)
            cout<<a.state[i][j]<<",";
        cout<<endl;
    }
    cout<<"depth = "<<a.depth<<endl;
    //cout<<endl;
}

void ids_ExpandNode(const Node& parent,                         //Helper for idsS_search()
                    Node& goal,
                    bool& accomplish,      //The finish flag, updated when child reach goal
                    int& endDepth,         //The resulting moves, updated when child reach goal
                    std::map<Node,int>& tree,
                    stack<Node>& myStack)
{
    Successor child(parent); child.MakeSuccessor();
    for(int i=0; i<4; i++)
        if(child.IsValid(i))
        {
            Node toBePush = child.GetContent(i);
            toBePush.depth = parent.depth + 1;
            
            if( toBePush == goal)
            {
                accomplish = true;
                endDepth = toBePush.depth;
                goal.depth = toBePush.depth;
                return;
            }
            
            else if(toBePush.depth <= endDepth)
              {
                if(tree.count(toBePush)==0||toBePush.depth<tree[toBePush]) //The condition for adding to tree & stack:
                {                                                          //Not found in tree || the new one has optimal depth
                    tree[toBePush]=toBePush.depth;
                    myStack.push(toBePush);
//                    cout<<"Add Node to Tree&Stack------------"<<endl;
//                    PrintNode(toBePush, tree);
//                    cout<<"As Child of------------"<<endl;
//                    PrintNode(parent, tree);
                    
                }
            }
        }
    
}

#endif /* ids_functions_h */
