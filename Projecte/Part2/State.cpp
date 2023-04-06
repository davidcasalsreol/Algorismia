#include <iostream>
#include <vector>
#include <set>
#include "State.h"
#include "../Part1/difusioIC.cpp"
using namespace std;

const float p = 0.5;

Graf g;
set<int> nodes; //conjunt de nodes solució

State::State(){}

State::State(Graf g, set<int> nodes)
{
    this->g = g;
    this->nodes = nodes;
}

//Pre: newState has not been initialized
bool State::addNode(int n, State& newState)
{
    if(nodes.find(n) != nodes.end())
        return false; //the node n is already in the current state
    
    set<int> newNodes = nodes;
    newNodes.insert(n);
    State newState (g, newNodes);

    return true;
}

//Pre: newState has not been initialized
bool State::removeNode(int n, State& newState)
{
    if(nodes.find(n) == nodes.end())
        return false; //the node n does not exist in the current state

    set<int> newNodes = nodes;
    newNodes.erase(n);
    State newState (g, newNodes);

    return true;
}

//Pre: succesors is not initialized
void State::getSuccessors(vector<State>& successors)
{
    for(int i = 0; i < g.nNodes(); i++)
    {
        State successor;
        if(addNode(i, successor))
            successors.push_back(successor);
        
        State successor2;
        if(removeNode(i, successor2))
            successors.push_back(successor2);
    }
}

bool State::isSolution()
{
    //We do 10 experiments, and check the at least 60% of them are solution. If it is the case, we consider State as a solution.
    int sum = 0;
    for(int i = 0; i < 10; i++)
    {
        if(difusioIC(g, p, nodes).size() == g.nNodes())
            sum++;
        
        if(sum >= 6)
            return true;
    }

    return false;
}

int State::eval()
{
    return nodes.size();
}

