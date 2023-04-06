#ifndef ESTAT_H
#define ESTAT_H
#include<iostream>
#include <vector>
#include <set>
#include "../Part1/graf.h"
using namespace std;

class State
{
    private:
        Graf g;
        set<int> nodes;
        bool addNode(int n, State& newState);
        bool removeNode(int n, State& newState);

    public:
        State();
        State(Graf g, set<int> nodes);
        //Returns succesors that ARE Solutions
        void getSuccessors(vector<State>& successors);
        
        //Returns the quality of the state
        int eval();

        bool isSolution();
};



#endif