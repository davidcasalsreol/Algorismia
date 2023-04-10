#include <iostream>
#include <vector>
#include <set>
#include "State.h"
#include "../Part1/difusioIC.cpp"
#include "../Part1/difusioLT.cpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

const float p = 0.5;
const float r = 0.5;

State::State(){}

State::State(Graf g, set<int> nodes)
{
    this->g = g;
    this->nodes = nodes;
}

//Pre: newState has not been initialized
bool State::addNode(int n, State& newState)
{
    //cout << "AddNode(" << n << ")" << endl;
    if(nodes.find(n) != nodes.end())
    {
        //cout << "El nodo " << n << " ya existe" << endl;
        return false; //the node n is already in the current state
    }
    
    set<int> newNodes = nodes;
    newNodes.insert(n);
    newState = State(g, newNodes);

    //cout << "Nodo añadido" << endl;
    return true;
}

//Pre: newState has not been initialized
bool State::removeNode(int n, State& newState)
{
    //cout << "RemoveNode(" << n << ")" << endl;
    if(nodes.find(n) == nodes.end())
    {
        //cout << "El nodo " << n << " NO existe" << endl;
        return false; //the node n does not exist in the current state
    }

    set<int> newNodes = nodes;
    newNodes.erase(n);
    newState = State(g, newNodes);

    //cout << "Nodo " << n << " eliminado" << endl;
    return true;
}

//Pre: succesors is not initialized
void State::getSuccessorsIC(vector<State>& successors)
{
    //cout << " Entramos en getSuccessorIC: nb nodes = " << g.nNodes() << endl;
    for(int i = 0; i < g.nNodes(); i++)
    {
        //cout << "123" << endl;
        State successor;
        if(addNode(i, successor) && successor.isSolutionIC())
            successors.push_back(successor);
        
        State successor2;
        //cout << "RemodeNode(" << i << ")" << endl;
        if(removeNode(i, successor2) && successor2.isSolutionIC())
            successors.push_back(successor2);
    }
}

//Pre: succesors is not initialized
void State::getSuccessorsLT(vector<State>& successors)
{
    /*cout << "GetSuccessors(), nodes: ";
    set<int>::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;*/

    for(int i = 0; i < g.nNodes(); i++)
    {
        State successor;
        /*bool b1 = addNode(i, successor);
        cout << "AddNode " << i << " = " << b1 << endl;
        cout << "Despues de addNode "; successor.printNodes(); cout << endl;
        bool b2 = successor.isSolutionLT();
        cout << "Despues de isSolutionLT "; successor.printNodes(); cout << endl;
        cout << "is solution " << b2 << endl; */
        if(addNode(i, successor) && successor.isSolutionLT())
        {
            //cout << "Successor: "; successor.printNodes(); cout << endl;
            successors.push_back(successor);
        }
        
        State successor2;
        if(removeNode(i, successor2) && successor2.isSolutionLT())
            successors.push_back(successor2);
    }
}

bool State::isSolutionIC()
{
    //cout << "Es solucion? ";
    //We do 10 experiments, and we check the at least 60% of them are solution. If it is the case, we consider State as a solution.
    int sum = 0;
    for(int i = 0; i < 10; i++)
    {
        //cout << "Exp" << i << endl;
        difusioIC(g, p, nodes);
        if(ActTot.size() == g.nNodes())
        {
            sum++;
        }
        //cout << "sum=" << sum << endl;
        
        if(sum >= 6)
        {
            //cout << "SI" << endl;
            return true;
        }
    }
    //cout << "NO" << endl;
    return false;
}

bool State::isSolutionLT()
{
    difusioLT(g, r, nodes);
    //cout << "ActTotLT.size() = " << ActTotLT.size() << "   " << "g.nNodes() = " << g.nNodes() << endl;
    return ActTotLT.size() == g.nNodes();
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

    this->nodes = set<int>();

    for(int i = 0; i < g.nNodes(); i++)
        this->nodes.insert(i);
    
}

void State::generateSimpleSolution(Graf g)
{
    srand (time(NULL));
    this->g = g;
    this->nodes = set<int>();
    nodes.insert(rand() % g.nNodes());
}

void State::generateSequentialSolution(Graf g)
{
    this->g = g;
    this->nodes = set<int>();

    float limit = (1 - p) * g.nNodes();
    for(int i = 0; i < limit; i++)
    {
        this->nodes.insert(i);
    }
}

//Pre: State has not been initialized, nodes of Graf g start from 0 to g.nNodes() - 1
void State::generateRandomSolution(Graf g)
{
    srand (time(NULL));
    
    this->g = g;

    this->nodes = set<int>();
    float limit = (1 - p) * g.nNodes();
    for(int i = 0; i < limit; i++)
    {
        int nodeId = rand() % g.nNodes();
        this->nodes.insert(nodeId);
    }
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
