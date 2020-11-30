#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

// O(A)
void read_alarms(string alarm_type, vector<int>& alarms){
    // read the number of ringing alarms
    int num_alarms, a;
    printf("Enter the number of %s alarms:\n", alarm_type.c_str());
    scanf("%d", &num_alarms);

    // read & sort the ringing alarms
    printf("Enter the ids of the %d %s alarms\n", num_alarms, alarm_type.c_str());
    for(int i = 1; i <= num_alarms; i++){
        scanf("%d", &a);
        alarms.push_back(a);
    }
}

// O(V + E + A)
void read_input(vector<vector<int>>& graph, vector<int>& alarms_r, vector<int>& alarms_s){

	//read the number of vertices & edges
    int num_vertices, num_edges;
    printf("Enter the number of vertices:\n");
    scanf("%d", &num_vertices);
    printf("It is assumed that the vertices have the following ids: [1, ..., %d]\n", num_vertices);
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

    // read the ringing alarms 
    read_alarms("ringing", alarms_r);

    // read the silent alarms
    read_alarms("silent", alarms_s);
}

// O(V + E)
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

// O(A)
void print_alarms(string alarm_type, const vector<int>& alarms){
	printf("%s alarms: ", alarm_type.c_str());
	for(int a : alarms){
		printf("%d, ", a);
	}
	printf("\n");
}

// O(A)
void print_ringing_alarms(const vector<int>& alarms){
    print_alarms("ringing", alarms);
}

// O(A)
void print_silent_alarms(const vector<int>& alarms){
    print_alarms("silent", alarms);
}