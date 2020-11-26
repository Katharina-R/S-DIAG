#include <cstdio>
#include "scc.cpp"

using namespace std;

// graph
vector<vector<int>> graph;


void print_graph(){
    printf("number of vertices: %ld\n", graph.size() - 1);
    printf("graph: \n");
    for(int u = 1; u < graph.size(); u++){
        for(int v : graph[u]){
            printf("%d -> %d, ", u, v);
        }
        if (graph[u].size() > 0) printf("\n");
    }
}

int main(){

    //read in the number of vertices
    int num_vertices;
    printf("Enter the number of vertices:\n");
    scanf("%d", &num_vertices);
    
    // read in the graph
    graph.resize(num_vertices + 1);
    printf("Enter the 1-based graph of the graph (e.g. 1 2 for the edge 1 -> 2):\n");
    int u, v;
    while(scanf("%d%d", &u, &v) != EOF && u != 0 && v != 0){
        graph[u].push_back(v);
    }

    // compress strongly connected components
    print_graph();
    tarjans_SCC(graph);
    compress_SCC(graph);
    print_graph();

    return 0;
}