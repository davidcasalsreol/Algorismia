#include <iostream>
#include <vector>
#include "graf.h"
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;

queue<int> difusioIC(Graf G, double p, set<int> &Activats){
    set<int> ActTot = Activats; //Aquesta implementació visita els vertex activats ordenats creixentment per id de node
    //unordered_set<int> ActTot = Activitats ho per FIFO
    //queue<int> ActTot = Activat5s ho fa per FIFO pero no tenim la opcio de cridar a .find() com si ho podem fer a les altres
    queue<int> rta;
    while(Activats.size() > 0 and ActTot.size() < G.nNodes()){
        auto it = Activats.begin();
        rta.push(*it);
        cout << "analitzemmm " << *it << endl;
        int node = *it ;
        Activats.erase(it);
        vector<int> adj = G.nodesadjacents(node);
        for(int i = 0; i < adj.size(); ++i){
            cout << adj[i] << endl;
            cout <<"posicio de activada " << *ActTot.find(adj[i]) << " sobre " << *ActTot.end() << endl;
            if(ActTot.find(adj[i]) == ActTot.end()) {
                double r = (double)rand()/ (double)RAND_MAX;
                cout << "amb probabilitat de " << r << endl;
                if(r < p){
                    cout << "activo " << adj[i]<< endl;
                    Activats.insert(adj[i]);
                    ActTot.insert(adj[i]);
                    
                }
            }
        }
        
    }
    return rta;
}


int main(){
    Graf G;
    Node N;
    cout << "TEST: NOMBRENODES " << G.nNodes() << endl;
    vector<int> test_adj = G.nodesadjacents(0);
    for(int i = 0; i < test_adj.size(); i++){
        cout << test_adj[i] << " ";
    }

    cout << endl;
    set<int> conjIni;
    conjIni.insert(0);
    queue<int> solLT = difusioIC(G,0.9,conjIni);
    unordered_set<int> sol;
    cout << "començo" << endl;
    while (solLT.size() != 0) {
        int node = solLT.front();
        cout <<node <<  ' ';
        solLT.pop();
    }
    cout << endl;
    cout << "acabat" << endl;

    cout << "TEST: NOMBRENODES2 " << G.nNodes() << endl;
    test_adj = G.nodesadjacents(5);
    for(int i = 0; i < test_adj.size(); i++){
        cout << test_adj[i] << " ";
    }
    cout << endl;
}