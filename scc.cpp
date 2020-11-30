// tarjan has been tested on hackerearth:
// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/a-walk-to-remember-qualifier2/

#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

// tarjan's data structures
vector<int> id; // -1: unseen
vector<int> low; // lowest id reachable
int next_id; // next available id
stack<int> t_stack;
vector<bool> on_stack;
vector<int> new_id; // id for compression

// recursively finds strongly connected components
// tarjan's algorithm
void tarjans_SCC_rec(int cur, const vector<vector<int>>& graph){

	// put vertex on stack
	t_stack.push(cur);
	on_stack[cur] = true;

	// assign next available id
	id[cur] = next_id; 
	low[cur] = next_id; 
	next_id++; 

	// visit neighbours & update low value
	for(int v : graph[cur]){
		// if v is unvisited -> visit
		if(id[v] == -1){
			tarjans_SCC_rec(v, graph);
		}
		// if v is on stack -> use v to update low
		if(on_stack[v]){
			low[cur] = min(low[cur], low[v]);
		}
	}

	// cur can reach itself => found SCC
	if(id[cur] == low[cur]){
		while(t_stack.size() > 0){
			// remove v from stack
			int v = t_stack.top();
			t_stack.pop();
			on_stack[v] = false;
			// all vertexes in the SCC have the same low value
			low[v] = low[cur];
			new_id[v] = cur;
			if(v == cur) break;
		}
	}
}

// O(V + E)
// finds strongly connected components (SCC)
void tarjans_SCC(const vector<vector<int>>& graph){

	// init tarjan data structures
	for(int i = 0; i < graph.size(); i++){
		on_stack.push_back(false);
		id.push_back(-1);
		low.push_back(0);
		new_id.push_back(i);
	}

	next_id = 1;

	// for each vertex (they can belong to unconnected components)
	for(int i = 1; i < graph.size(); i++){
		// this vertex has been seen already
		if(id[i] == -1) {
			tarjans_SCC_rec(i, graph);
		}
	}
}

// updates the id of the alarm
void update_alarms(int id_old, int id_new, unordered_set<int>& alarms){
	if(alarms.contains(id_old)){
		alarms.erase(id_old);
		alarms.insert(id_new);
	}
}

// O(V + E*log(E))
// compresses strongly connected components & updates edges
// keeps the id's of the vertexes, e.g.:
// {1} -> {1}
// SCC {1, 2, 3} -> {1} or {2} or {3}
void compress_SCC(vector<vector<int>>& graph, unordered_set<int>& alarms_r, unordered_set<int>& alarms_s){

	vector<vector<int>> graph_c;
	graph_c.resize(graph.size());

	// compress vertex id's (id -> id_comp)
	for(int u = 1; u < graph.size(); u++){

		// compress
		if(u != new_id[u]){
			update_alarms(u, new_id[u], alarms_r);
			update_alarms(u, new_id[u], alarms_s);
			printf("Compressing %d into %d\n", u, new_id[u]);
		} 
		for(int v : graph[u]){
			// no self-loops
			if(new_id[u] != new_id[v]){
				graph_c[new_id[u]].push_back(new_id[v]);
			}
		}
	}

	// remove duplicates
	for(int i = 1; i < graph.size(); i++){
		sort(graph_c[i].begin(), graph_c[i].end());
		auto it_end = unique(graph_c[i].begin(), graph_c[i].end());
		graph_c[i].resize(it_end - graph_c[i].begin());
		graph[i] = graph_c[i];
	} 
}