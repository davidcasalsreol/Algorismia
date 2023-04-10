#include <queue>
#include <set>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "graf.h"
using namespace std;

// Struct que representa una possible solució
struct Individu {
    vector<bool> nodes; 
    double fitness; 
};

int numActivats(vector<bool> nodes) {
    int count = 0;
    for(int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]) { 
            ++count;
        }
    }
    return count;
}

int difusioLT(Graf G, double r, set<int> &Activats){
    set<int> ActivatsTotals = Activats;
    queue<int> rta;
    vector<int> InfluenciaNodes(G.nNodes(), 0);
    while(Activats.size() > 0 and ActivatsTotals.size() < G.nNodes()){
        auto it = Activats.begin();
        rta.push(*it);
        //cout << "analitzemmm " << *it << endl;
        int node = *it ;
        Activats.erase(it);        
        if(G.esValid(node)){
          //  cout << "valid" << endl;
            vector<int> adj = G.nodesadjacents(node);
            for(int i = 0; i < adj.size(); ++i){
                int g  = G.grauNode(adj[i]);
                if(ActivatsTotals.find(adj[i]) == ActivatsTotals.end()) {   
            //        cout << adj[i] << " amb grau "<< g<<", tenim " << InfluenciaNodes[adj[i]]  << " i necessitem " <<r*g << endl;
                    InfluenciaNodes[adj[i]]++;
                    if(InfluenciaNodes[adj[i]] >= r*g){
              //          cout << adj[i] << " ha superat el seu llindar " << r*g << endl;
                        Activats.insert(adj[i]);
                        ActivatsTotals.insert(adj[i]);
                    }
                }
            }
        }
    }
    return ActivatsTotals.size();
}


bool ordre(const Individu& ind1, const Individu& ind2) {
    return (ind1.fitness > ind2.fitness);
}

// Funció para calcular el fitness (relació entre nodes activats finals amb el menors nodes activats inicials)
void calcularFitness(Individu& ind, Graf& G, double r) {
    int count = 0;
    set<int> activats;
    for(int i = 0; i < ind.nodes.size(); ++i) {
        if (ind.nodes[i]) { 
            activats.insert(i);
            ++count;
        }
    }
    int numNodesFinal = difusioLT(G, r, activats);
    ind.fitness = double(numNodesFinal)/double(count);
}


// Funció para generar una població inicial amb n individus amb un node activat diferent cada un.
void generarPoblacioInicial(set<Individu, decltype(&ordre)>& poblacio, Graf& G, double r) {
    int numNodes = G.nNodes();
    for (int i = 0; i < numNodes; ++i) {
        Individu ind;
        ind.fitness = 0;
        ind.nodes = vector<bool> (numNodes, false);
        ind.nodes[i] = true;
        calcularFitness(ind, G, r);
        poblacio.insert(ind);
    }
}

// Funció per crear la solució filla entre les dos millors solucions de la generacio anterior
void recombinar(set<Individu, decltype(&ordre)> poblacio) {
    auto it = poblacio.begin();
    auto it2 = next(poblacio.begin());
    Individu pare = *it;
    Individu mare = *it2;
    Individu fill;
    fill.nodes = vector<bool> (pare.nodes.size());
    int tamGraf = pare.nodes.size();
    int punt = rand() % tamGraf;
    for (int i = 0; i < punt; ++i) {
        fill.nodes[i] = pare.nodes[i];
    }
    for (int i = punt; i < tamGraf; ++i) {
        fill.nodes[i] = mare.nodes[i];
    }
    poblacio.insert(fill);
}

int geneticLT(Graf& G, double r) {
    set<Individu, decltype(&ordre)> Poblacio(&ordre);
    generarPoblacioInicial(Poblacio, G, r);
    for(int i = 0; i < 100 and (Poblacio.size() > 1); ++i) { // 100 it. arbitraries
        set<Individu, decltype(&ordre)> s(&ordre);
        for(int j = 0; j < 2; ++j) {
            auto it = Poblacio.begin();
            Individu ind = *it;
            Poblacio.erase(it);
            calcularFitness(ind, G, r);
            s.insert(ind);
        }
        recombinar(s);
        Poblacio.clear();
        Poblacio = s;
    }
    auto it = Poblacio.begin();
    return numActivats((*it).nodes);
}

int main() {
    srand(time(0));
    double r = 0.2;
    cin >> r;
    if ( (r > 0.0 or r == 0.0) and (r < 1.0 or r == 1.0)) {
        Graf G;
        cout << "Número de nodes activats inicialment: " << geneticLT(G, r)  << endl;
    }
    else cout << "r incorrecta" << endl;
}
