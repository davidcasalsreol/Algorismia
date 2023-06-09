#include <iostream>
#include <vector>
#include "graf.h"
#include <queue>
using namespace std;

queue<int> difusioIC(Graf G, double p, queue<int> &Activats){
    queue<int> ActTot = Activats;
    while(Activats.size() > 0){
        int node = Activats.front();
        Activats.pop();
        if(G.esValid(node)){
            vector<int> adj = G.nodesadjacents(node);
            for(int i = 0; i < adj.size(); ++i){
                if((double)rand()/ (double)RAND_MAX < p){
                    Activats.push(adj[i]);
                    ActTot.push(adj[i]);
                }
            }
        }
    }
    return ActTot;
}

queue<int> difusioLT(Graf G, double r, queue<int> &Activats){
    queue<int> ActTot = Activats;
    vector<int> InfluenciaNodes(G.nNodes(), 0);
    while(Activats.size() > 0){
        int node = Activats.front();
        if(G.esValid(node)){
            vector<int> adj = G.nodesadjacents(node);
            for(int i = 0; i < adj.size(); ++i){
                InfluenciaNodes[adj[i]]++;
                if(InfluenciaNodes[adj[i]] > r*G.grauNode(adj[i])){
                    Activats.push(adj[i]);
                    ActTot.push(adj[i]);
                }
            }
        }
    }
    return ActTot;
}

int main(){
    Graf G;
    Node N;
    N.id = 0;
    N.adjacents.push_back(make_pair(0, true));
    N.valid = true;
    G.afegirNode(N);
    cout << "TEST: NOMBRENODES " << G.nNodes() << endl;
    vector<int> test_adj = G.nodesadjacents(4);
    for(int i = 0; i < test_adj.size(); i++){
        cout << test_adj[i] << " ";
    }
    cout << endl;
    G.eliminarNode(3);
    cout << "TEST: NOMBRENODES2 " << G.nNodes() << endl;
    test_adj = G.nodesadjacents(3);
    for(int i = 0; i < test_adj.size(); i++){
        cout << test_adj[i] << " ";
    }
    cout << endl;
}