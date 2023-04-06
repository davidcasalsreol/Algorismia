#include <iostream>
#include "State.h"
using namespace std;

State hillClimbing()
{
    State currentState; // = generarSolucioInicial();
    while(true)
    {
        vector<State> neighbours;
        currentState.getSuccessors(neighbours);

        State nextState = neighbours[0];
        int bestSolution = neighbours[0].eval();
        for(int i = 1; i < neighbours.size(); i++)
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

}