#pragma once

#include <algorithm>
#include <cstdio>
#include <unordered_set>
#include <vector>

using namespace std;

// O(V + E)
vector<vector<int>> read_graph(){
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

    return graph;
}

// O(A) <= O(V)
unordered_set<int> read_alarms(bool ringing_only){
    int num_alarms, a;
    string alarm_type = ringing_only? "ringing alarms" : "alarms";
    printf("Enter the number of %s:\n", alarm_type.c_str());
    scanf("%d", &num_alarms);

    unordered_set<int> alarms;
    printf("Enter the ids of the %s:\n", alarm_type.c_str());
    for(int i = 1; i <= num_alarms; i++){
        scanf("%d", &a);
        alarms.insert(a);
    }

    return alarms;
}

// O(V + E)
void print_graph(const vector<vector<int>>& graph){
    printf("edges: \n");
    for(int u = 1; u < graph.size(); u++){
        for(int v : graph[u]){
            printf("%d -> %d, ", u, v);
        }
        if (graph[u].size() > 0) printf("\n");
    }
}

// O(A)
void print_alarms(const unordered_set<int>& alarms_r, const unordered_set<int>& alarms_s){
	printf("ringing alarms: ");
	for(int a : alarms_r){
		printf("%d, ", a);
	}
    printf("\n");

	printf("silent alarms: ");
    for(int a : alarms_s){
        printf("%d, ", a);
    }
    printf("\n");
}

void print_alarms(string alarm_type, const unordered_set<int>& alarms_r){
    printf("%s alarms: ", alarm_type.c_str());
    for(int a : alarms_r){
        printf("%d, ", a);
    }
    printf("\n");
}

// O(V + E + A)
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
void print_predecessors_rec(int cur, const vector<vector<int>>& graph_t, vector<bool>& seen){
    
    if(seen[cur]) return;
    seen[cur] = true;

    printf("%d ", cur);
    for(int p : graph_t[cur]){
        print_predecessors_rec(p, graph_t, seen);
    }
}

// O(V + E)
void print_predecessors(int cur, const vector<vector<int>>& graph_t){
    printf("Minimum set with at least one fault cause: ");

    // count each predecessor only once
    vector<bool> seen(graph_t.size(), false);

    print_predecessors_rec(cur, graph_t, seen);
    printf("\n");
}