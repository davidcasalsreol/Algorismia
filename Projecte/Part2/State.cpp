#include <iostream>
#include <vector>
#include <set>
#include "State.h"
#include "../Part1/difusioIC.cpp"
#include "../Part1/difusioLT.cpp"
using namespace std;

const float p = 1;
const float r = 0.5;

//5 2 1 2 2 0 2 3 0 1 3 1 2 0
//Graf g;
//set<int> nodes; //conjunt de nodes solució

State::State(){}

State::State(Graf g, set<int> nodes)
{
    this->g = g;
    this->nodes = nodes;
}

//Pre: newState has not been initialized
bool State::addNode(int n, State& newState)
{
    cout << "AddNode(" << n << ")" << endl;
    if(nodes.find(n) != nodes.end())
    {
        cout << "El nodo " << n << " ya existe" << endl;
        return false; //the node n is already in the current state
    }
    
    set<int> newNodes = nodes;
    newNodes.insert(n);
    newState = State(g, newNodes);

    cout << "Nodo añadido" << endl;
    return true;
}

//Pre: newState has not been initialized
bool State::removeNode(int n, State& newState)
{
    cout << "RemoveNode(" << n << ")" << endl;
    if(nodes.find(n) == nodes.end())
    {
        cout << "El nodo " << n << " NO existe" << endl;
        return false; //the node n does not exist in the current state
    }

    set<int> newNodes = nodes;
    newNodes.erase(n);
    newState = State(g, newNodes);

    cout << "Nodo " << n << " eliminado" << endl;
    return true;
}

//Pre: succesors is not initialized
void State::getSuccessorsIC(vector<State>& successors)
{
    cout << " Entramos en getSuccessorIC: nb nodes = " << g.nNodes() << endl;
    for(int i = 0; i < g.nNodes(); i++)
    {
        cout << "123" << endl;
        State successor;
        if(addNode(i, successor) && successor.isSolutionIC())
            successors.push_back(successor);
        
        State successor2;
        cout << "RemodeNode(" << i << ")" << endl;
        if(removeNode(i, successor2) && successor2.isSolutionIC())
            successors.push_back(successor2);
    }
}

//Pre: succesors is not initialized
void State::getSuccessorsLT(vector<State>& successors)
{
    for(int i = 0; i < g.nNodes(); i++)
    {
        State successor;
        if(addNode(i, successor) && successor.isSolutionLT())
            successors.push_back(successor);
        
        State successor2;
        if(removeNode(i, successor2) && successor2.isSolutionLT())
            successors.push_back(successor2);
    }
}

bool State::isSolutionIC()
{
    cout << "Es solucion? ";
    //We do 10 experiments, and check the at least 60% of them are solution. If it is the case, we consider State as a solution.
    int sum = 0;
    for(int i = 0; i < 10; i++)
    {
        if(difusioIC(g, p, nodes).second == g.nNodes())
        {
            sum++;
        }
        
        if(sum >= 6)
        {
            cout << "SI" << endl;
            return true;
        }
    }
    cout << "NO" << endl;
    return false;
}

bool State::isSolutionLT()
{
    return difusioLT(g, r, nodes).size() == g.nNodes();
}

int State::eval()
{
    return nodes.size();
}

set<int> State::getNodes()
{
    return this->nodes;
}

//Pre: State has not been initialized, nodes of Graf g start from 0 to g.nNodes() - 1
void State::generateFullSolution(Graf g)
{
    this->g = g;

    set<int> nodes;
    for(int i = 0; i < g.nNodes(); i++)
        nodes.insert(i);
    
    this->nodes = nodes;
}

void State::printNodes()
{
    set<int>::iterator it;
    for(it  = this->nodes.begin(); it != nodes.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}
