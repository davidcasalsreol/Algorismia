#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <cfloat>
#include <random>

using namespace std;

mt19937 gen(random_device{}());
uniform_real_distribution<> dis(0, 1);

vector<int> greedy_ic(vector<vector<int>>& graf, double p) {
    int n = graf.size();
    vector<int> S;
    vector<bool> activats (n, false);
    vector<int> total_adj(n, 0);

    // Cuenta el numero total de vecinos activados para cada nodo
    for (int i = 0; i < n; i++) {
        for (int j : graf[i]) {
            total_adj[i] += activats[j];
        }
    }

    //Bucle que no para fins activar tots els nodes
    while (count(activats.begin(), activats.end(), false) > 0) {
        int millor_node = -1;
        double menor_fracció = DBL_MAX;
        //Càlcul del node amb la menor fracció veïns activats
        for (int i = 0; i < n; i++) {
            if (!activats[i]) {
                int adj_activats = total_adj[i];
                int total_adj = graf[i].size() - 1;

                double fracció = (double) adj_activats / total_adj;

                if (fracció < menor_fracció) {
                    millor_node = i;
                    menor_fracció = fracció;
                }
            }
        }
        //Activació del node seleccionat
        if (millor_node > -1) {S.push_back(millor_node);}
        else break;
        //cout << "añado " << millor_node << endl;
        activats[millor_node] = true;

        queue<int> q;
        for (int adj : graf[millor_node]) {
            //double random = dis(gen);
            //cout << random << endl;
            //cout << p << endl;
            //cout << (random < p) << endl;
            if ((!activats[adj]) && dis(gen) < p) {
                activats[adj] = true;
                q.push(adj);
                total_adj[adj]--;
            }
        }

        //Propagació del node activat
        while (!q.empty()) {
            int act = q.front();
            q.pop();

            for (int adj : graf[act]) {
                if (!activats[adj] && double(dis(gen)) < p) {
                    activats[adj] = true;
                    q.push(adj);
                    total_adj[adj]--;
                }
            }
        }
    }

    return S;
}


int main() {
    int n, m;
    double p;
    cin >> n >> m >> p;

    char c;

    vector<vector<int>> graf(n);

    for (int i = 0; i < m; ++i) {
        cin >> c;
        int u, v;
        cin >> u >> v;
        graf[u-1].push_back(v-1);
        graf[v-1].push_back(u-1);
    }

    auto start_time = chrono::high_resolution_clock::now();

    //Crida a l'algorisme greedy basat en Vertex cover
    vector<int> S = greedy_ic(graf, p);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    //cout << "p = " << p << endl;
    cout << /*"Temps d'execució: " << */duration.count() << " ms ";
    cout << /*"Nombre de vèrtexs activats: " <<*/S.size() << " nodes" << endl;
    //cout << "Subconjunt de vértexs seleccionats: { ";
    /*for (int v : S) {
        cout << v + 1 << " ";
    }
    cout << endl;*/
}