#include <iostream>
#include <vector>
#include "graf.h"
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;


queue<int> difusioLT(Graf G, double r, set<int> &Activats){
    set<int> ActTot = Activats;
    queue<int> rta;
    vector<int> InfluenciaNodes(G.nNodes(), 0);
    while(Activats.size() > 0 and ActTot.size() < G.nNodes()){
        auto it = Activats.begin();
        rta.push(*it);
        cout << "analitzemmm " << *it << endl;
        int node = *it ;
        Activats.erase(it);        
        if(G.esValid(node)){
            cout << "valid" << endl;
            vector<int> adj = G.nodesadjacents(node);
            for(int i = 0; i < adj.size(); ++i){
                int g  = G.grauNode(adj[i]);
                if(ActTot.find(adj[i]) == ActTot.end()) {   
                    cout << adj[i] << " amb grau "<< g<<", tenim " << InfluenciaNodes[adj[i]]  << " i necessitem " <<r*g << endl;
                    InfluenciaNodes[adj[i]]++;
                    if(InfluenciaNodes[adj[i]] > r*g){
                        cout << adj[i] << " ha superat el seu llindar " << r*g << endl;
                        Activats.insert(adj[i]);
                        ActTot.insert(adj[i]);
                    }
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
    conjIni.insert(11);
    queue<int> solLT = difusioLT(G,0.4,conjIni);
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