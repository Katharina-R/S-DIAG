// tarjan has been tested on hackerearth:
// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/a-walk-to-remember-qualifier2/
#pragma once

#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

// recursively finds strongly connected components
// tarjan's algorithm
void tarjans_SCC_rec(
	int cur, 
	const vector<vector<int>>& graph, 
	stack<int>& stack_t, 
	vector<bool>& on_stack, 
	vector<int>& discovery, 
	int& next_id,
	vector<int>& id_new, 
	vector<int>& low){

	// put vertex on stack
	stack_t.push(cur);
	on_stack[cur] = true;

	// assign next available id
	discovery[cur] = low[cur] = next_id++; 

	// visit neighbours & update low value
	for(int v : graph[cur]){
		// if v is unvisited -> visit
		if(discovery[v] == 0){
			tarjans_SCC_rec(v, graph, stack_t, on_stack, discovery, next_id, id_new, low);
		}
		// if v is on stack -> use v to update low
		if(on_stack[v]){
			low[cur] = min(low[cur], low[v]);
		}
	}

	// cur can reach itself => found SCC
	if(discovery[cur] == low[cur]){
		int v;
		do {
			// remove v from stack
			v = stack_t.top();
			stack_t.pop();
			on_stack[v] = false;

			// all vertexes in the SCC have the same low value
			id_new[v] = cur;
		} while(v != cur);
	}
}

// O(V + E)
// finds strongly connected components (SCC)
vector<int> tarjans_SCC(const vector<vector<int>>& graph){

	// init tarjan data structures
	stack<int> stack_t;
	vector<bool> on_stack(graph.size(), false);

	int next_id = 1;
	vector<int> discovery(graph.size(), 0); // 0: unseen
	vector<int> id_new(graph.size()); // vertex id after compression
	vector<int> low(graph.size(), 0); // lowest id reachable

	// running dfs for each vertex (there might be several roots)
	for(int u = 1; u < graph.size(); u++){
		// unseen vertex
		if(discovery[u] == 0) {
			tarjans_SCC_rec(u, graph, stack_t, on_stack, discovery, next_id, id_new, low);
		}
	}

	return id_new;
}

// updates the id of the alarm
void update_alarms(int id_old, int id_new, unordered_set<int>& alarms){
	if(alarms.contains(id_old)){
		alarms.erase(id_old);
		alarms.insert(id_new);
	}
}

// O(V + E*log(E))
// compresses strongly connected components, updates edges & alarms
// keeps the id's of the vertexes, e.g.:
// {1} -> {1}
// SCC {1, 2, 3} -> {1} or {2} or {3}
void compress_graph(vector<int>& id_new, vector<vector<int>>& graph){
	// compressed graph
	vector<vector<int>> graph_c(graph.size());

	// compress vertex id's (id -> id_new)
	for(int u = 1; u < graph.size(); u++){

		// change id of current vertex
		if(u != id_new[u]){
			printf("Compressing %d into %d\n", u, id_new[u]);
		} 
		for(int v : graph[u]){
			// no self-loops
			if(id_new[u] != id_new[v]){
				graph_c[id_new[u]].push_back(id_new[v]);
			}
		}
	}

	// remove duplicate edges
	for(int i = 1; i < graph.size(); i++){
		sort(graph_c[i].begin(), graph_c[i].end());
		auto it_end = unique(graph_c[i].begin(), graph_c[i].end());
		graph_c[i].resize(it_end - graph_c[i].begin());
		graph[i] = graph_c[i];
	} 
}

// O(V)
void compress_alarms(vector<int>& id_new, unordered_set<int>& alarms_r, unordered_set<int>& alarms_s){

	// compress vertex id's (id -> id_new)
	for(int u = 1; u < id_new.size(); u++){

		// change id of current vertex
		if(u != id_new[u]){
			update_alarms(u, id_new[u], alarms_r);
			update_alarms(u, id_new[u], alarms_s);
		} 
	}
}