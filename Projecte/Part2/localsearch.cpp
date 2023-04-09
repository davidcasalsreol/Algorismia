#include <iostream>
#include "State.h"
using namespace std;

#include <queue>

State hillClimbingIC(Graf g)
{
    cout << 3 << endl;
    //Generate initial solution
    State currentState;
    cout << 4 << endl;
    currentState.generateFullSolution(g);
   
   int i = 0;
    while(true)
    {
        cout << "Iteration " << i << endl;

        vector<State> neighbours;
        currentState.getSuccessorsIC(neighbours);

        cout << "Sucesores: " << neighbours.size() << endl;

        State nextState;
        int bestSolution;

        if(neighbours.size() > 0)
        {
            nextState = neighbours[0];
            bestSolution = neighbours[0].eval();

            cout << "eval curent sate = " << currentState.eval() << endl;
            cout << "current state: ";
            currentState.printNodes();

            for(int i = 1; i < neighbours.size(); i++)
            {
                cout << "neighbour " << i << ": eval = " << neighbours[i].eval() << endl;
                cout << "nodes: "; neighbours[i].printNodes();

                

                if(neighbours[i].eval() < bestSolution)
                {
                    nextState = neighbours[i];
                    bestSolution = neighbours[i].eval();
                }

                cout << "best solution: " << bestSolution << endl;
                cout << "next state: "; nextState.printNodes();
            }
        }
        else
            return currentState;
        
        if(currentState.eval() < bestSolution)
        {
            cout << "FOOOOOOOOUUUUUUNDDD" << endl;
            return currentState;
        }
        
        currentState = nextState;
    }
}

State hillClimbingLT()
{
    State currentState; // = generarSolucioInicial();
    while(true)
    {
        vector<State> neighbours;
        currentState.getSuccessorsLT(neighbours);

        State nextState = currentState;
        int bestSolution = currentState.eval();
        for(int i = 0; i < neighbours.size(); i++)
        {
            if(neighbours[i].eval() < bestSolution)
            {
                nextState = neighbours[i];
                bestSolution = neighbours[i].eval();
            }
        }
        
        if(currentState.eval() < bestSolution)
            return currentState;
        
        currentState = nextState;
    }
}

int main()
{
    /*Graf g;
    g.llegirGraf();

    State state;
    state.generateFullSolution(g);

    set<int> act = state.getNodes();
    cout << "set de nodes:";
    set<int>::iterator it;
    for(it = act.begin(); it != act.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    cout << "Nodes activats amb Full Solution: " << difusioIC2(g, 1, act).second << endl;

    if(act.erase(2) == 1)
    {
        cout << "Node 2 eliminat del set" << endl;
    }

    cout << "Queden els nodes ";
    for(it = act.begin(); it != act.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Fem difusio ara" << endl;
    cout << "Nodes activats amb el nou set: " << difusioIC2(g, 1, act).second << "nodes activats" << endl;*/

    Graf g;
    g.llegirGraf();
    State sol = hillClimbingIC(g);
    set<int> nodes = sol.getNodes();
    set<int>::iterator it;

    for(it = nodes.begin(); it != nodes.end(); it++)
        cout << *it << " ";
    
    cout << endl;
}