#include <iostream>
#include "State.h"
#include <ctime>
using namespace std;

#include <queue>

State hillClimbingIC(Graf g)
{
    //Generate initial solution
    State currentState;
    currentState.generateFullSolution(g);
   
   int i = 0;
    while(true)
    {

        vector<State> neighbours;
        currentState.getSuccessorsIC(neighbours);

        State nextState;
        int bestSolution;

        if(neighbours.size() > 0)
        {
            nextState = neighbours[0];
            bestSolution = neighbours[0].eval();

            for(int i = 1; i < neighbours.size(); i++)
            {

                if(neighbours[i].eval() < bestSolution)
                {
                    nextState = neighbours[i];
                    bestSolution = neighbours[i].eval();
                }
            }
        }
        else
            return currentState;
        
        if(currentState.eval() < bestSolution)
        {
            return currentState;
        }
        
        currentState = nextState;
    }
}

State hillClimbingLT(Graf g)
{
    //Generate initial solution
    State currentState;
    currentState.generateRandomSolution(g);
    //cout << "Init sol "; currentState.printNodes(); cout << endl;
   
    while(true)
    {
        vector<State> neighbours;
        currentState.getSuccessorsLT(neighbours);

        /*for(int j = 0; j < neighbours.size(); j++)
        {
            cout << "Neighbour " << j << ": "; neighbours[j].printNodes(); cout << endl;
        }*/

        State nextState;
        int bestSolution;

        if(neighbours.size() > 0)
        {
            nextState = neighbours[0];
            bestSolution = neighbours[0].eval();

            for(int i = 1; i < neighbours.size(); i++)
            {

                if(neighbours[i].eval() < bestSolution)
                {
                    nextState = neighbours[i];
                    bestSolution = neighbours[i].eval();
                }
            }
        }
        else
            return currentState;
        
        if(currentState.eval() < bestSolution)
        {
            return currentState;
        }
        
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


    std::clock_t start;
    double duration;
    
    start = std::clock(); // se guarda el tiempo de inicio

    Graf g;
    g.llegirGraf();
    cout << "Llegit" << endl;
    State sol = hillClimbingLT(g);
    
    cout << "SOLUTION: " << sol.getNodes().size() << endl;
    cout << "is solution? ";
    if(sol.isSolutionLT())
        cout << "Yes";
    else
        cout << "No";
    cout << endl;

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecución: " << duration << " segundos" << std::endl;



    /*Graf g;
    g.llegirGraf();
    set<int> act;
    act.insert(0);
    act.insert(1);

    difusioLT2(g, 0.5, act);

    set<int>::iterator it;
    for(it = ActTotLT2.begin(); it != ActTotLT2.end(); it++)
    {
        cout << *it << " " ;
    }
    cout << endl;*/
    
    /*set<int>::iterator it;
    for(it = sol.getNodes().begin(); it != sol.getNodes().end(); it++)
        cout << *it << " ";
    cout << endl;*/

}