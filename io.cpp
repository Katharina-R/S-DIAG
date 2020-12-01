#pragma once

#include <algorithm>
#include <cstdio>
#include <unordered_set>
#include <vector>

using namespace std;

// O(A) <= O(V)
unordered_set<int> read_alarms(string alarm_type){
    // read the number of ringing alarms
    int num_alarms, a;
    printf("Enter the number of %s alarms:\n", alarm_type.c_str());
    scanf("%d", &num_alarms);

    // read the alarms
    printf("Enter the ids of the %d %s alarms\n", num_alarms, alarm_type.c_str());
    unordered_set<int> alarms;
    for(int i = 1; i <= num_alarms; i++){
        scanf("%d", &a);
        alarms.insert(a);
    }

    return alarms;
}

// O(V + E + A) = O(V + E)
tuple<vector<vector<int>>, unordered_set<int>, unordered_set<int>> read_input(){ 

	//read the number of vertices & edges
    int num_vertices, num_edges;
    printf("Enter the number of vertices:\n");
    scanf("%d", &num_vertices);
    printf("It is assumed that the vertices have the following ids: [1, ..., %d]\n", num_vertices);
    printf("Enter the number of edges:\n");
    scanf("%d", &num_edges);

    // read the graph
    vector<vector<int>> graph(num_vertices + 1);
    printf("Enter the %d edges of the graph (e.g. 1 2 represents the edge 1 -> 2):\n", num_edges);
    int u, v;
    for(int i = 1; i <= num_edges; i++){
    	scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }

    return {graph, read_alarms("ringing"), read_alarms("silent")};
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
void print_alarms(string alarm_type, const unordered_set<int>& alarms){
	printf("%s alarms: ", alarm_type.c_str());
	for(int a : alarms){
		printf("%d, ", a);
	}
	printf("\n");
}

void print_all(vector<vector<int>> graph, unordered_set<int> alarms_r, unordered_set<int> alarms_s){
    print_graph(graph);
    print_alarms("ringing", alarms_r);
    print_alarms("silent", alarms_s);
}

// O(R) <= O(A)
void print_number_of_result(const vector<int>& result){

    if(result.size() == 1){
        printf("Found 1 minimal set:\n");
    }
    else{
        printf("Found %ld minimal sets:\n", result.size());
    }
}

// O(V + E)
void print_predecessors_rec(int cur, const vector<vector<int>>& graph_t){
    printf("%d ", cur);
    for(int p : graph_t[cur]){
        print_predecessors_rec(p, graph_t);
    }
}

// O(V + E)
void print_predecessors(int cur, const vector<vector<int>>& graph_t){
    printf("Minimum set with at least one fault cause: ");
    print_predecessors_rec(cur, graph_t);
}