#include <bits/stdc++.h>
using namespace std;
#define null 99

vector<int> Component(100, null);

//custom hash function because cpp has no default hash function to pair<int,int>
struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};
struct Graph {
    
    Graph(int numberOfV) {
        v = numberOfV;
    }

    int v;
    vector<pair<int,int>> e;
    unordered_map<pair<int,int>, int, pair_hash> weight;
}; 

vector<int> minEdge(100, 9999);
vector<pair<int,int>> edge(100, {-1,-1});

unordered_set<pair<int,int>, pair_hash> boruvkaMST(Graph & G) {
   
    unordered_set<pair<int,int>, pair_hash> MST;
    
    int numberofComponents = G.v;

    while ( numberofComponents > 1 ) {
        for (auto & [u,v] : G.e) {
            int ComponentU = Component[u]; 
            int ComponentV = Component[v];
    
            if (ComponentU != ComponentV) {
                if (G.weight[{u,v}] < minEdge[ComponentU]) { minEdge[ComponentU] = G.weight[{u,v}]; edge[ComponentU] = {u,v}; }
                if (G.weight[{u,v}] < minEdge[ComponentV]) { minEdge[ComponentV] = G.weight[{u,v}]; edge[ComponentV] = {u,v}; }
            }

        }
  
    //i for components and min[i] weights
        for (int i = 99; i >= 0; i--) {
            if (minEdge[i] != 9999) {
                MST.insert(edge[i]);

                int u = edge[i].first;
                int v = edge[i].second;
                Component[v] = Component[u]; //union.
                numberofComponents--;
            } 
        }

    }
    
    return MST;
}

int main() {
    int V, E;
    cout << "Number of Vertcies : ";
    cin >> V;
    cout << "Number of Edges : ";
    cin >> E;

    Graph G(V);

    int i = 100;
    cout << "parent<space>neibour<space>edge-weight : ";
    while ( E-- ) {
        int u, v, w;
        cin >> u >> v >> w;

        G.e.push_back({u,v});
        G.weight[{u,v}] = w;
        Component[u] = i; i--;
    } 

    unordered_set<pair<int,int>, pair_hash> minimumSpaningTree =  boruvkaMST(G);
    cout << "\nMST : \n";
    for (const auto & [u,v] : minimumSpaningTree) {
        cout << "("<<u<<","<<v<<")" << endl;
    }
    return 0;
}
