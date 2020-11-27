#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

void read_input(vector<vector<int>>& graph, vector<int>& alarms){

	//read the number of vertices & edges
    int num_vertices, num_edges;
    printf("Enter the number of vertices:\n");
    scanf("%d", &num_vertices);
    printf("Enter the number of edges:\n");
    scanf("%d", &num_edges);

    // read the graph
    graph.resize(num_vertices + 1);
    printf("Enter the %d edges of the graph (e.g. 1 2 for the edge 1 -> 2):\n", num_edges);
    int u, v;
    for(int i = 1; i <= num_edges; i++){
    	scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }

    // read the number of alarms
    int num_alarms, a;
    printf("Enter the number of alarms:\n");
    scanf("%d", &num_alarms);

    // read & sort the alarms
    printf("Enter the %d alarm ids\n", num_alarms);
    for(int i = 1; i <= num_alarms; i++){
    	scanf("%d", &a);
        printf("read alarm: %d", a);
    	alarms.push_back(a);
    }
    sort(alarms.begin(), alarms.end());
}

void print_graph(const vector<vector<int>>& graph){
    printf("number of vertices: %ld\n", graph.size() - 1);
    printf("graph: \n");
    for(int u = 1; u < graph.size(); u++){
        for(int v : graph[u]){
            printf("%d -> %d, ", u, v);
        }
        if (graph[u].size() > 0) printf("\n");
    }
}

void print_alarms(const vector<int>& alarms){
	printf("alarms: ");
	for(int a : alarms){
		printf("%d, ", a);
	}
	printf("\n");
}