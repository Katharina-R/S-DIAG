#include <vector>

vector<bool> seen;
vector<int> to_remove;

void mark_reachable_vertexes_to_remove(int cur, const vector<vector<int>>& graph){

	// mark current vertex as seen
	if(seen[cur]) return;
	seen[cur] = true;

	// mark children as to_remove
	for(int v : graph[cur]){
		to_remove[v] = true;
		mark_reachable_vertexes_to_remove(v, graph);
	}
}

void mark_reachable_from_ringing_alarm(const vector<vector<int>>& graph, const vector<int>& alarms){

	for(int a : alarms){
		mark_reachable_vertexes_to_remove(a, graph);
	}
}

bool find_alarm(int cur, const vector<vector<int>>& graph, const vector<int>& alarms){

	// seen this vertex before
	if(seen[cur]) return !to_remove[cur];
	seen[cur] = true;

	// cur has alarm => there will not be any interesting children
	// see: mark_reachable_from_ringing_alarm
	if(find(alarms.begin(), alarms.end(), cur) != alarms.end()){
		return true;
	}

	// test children
	bool found_alarm = false;
	for(int v : graph[cur]){
		found_alarm |= find_alarm(v, graph, alarms);
	}

	// no child has an alarm
	if(!found_alarm){
		to_remove[cur] = true;
	}

	return found_alarm;
}

void mark_cannot_reach_ringing_alarm(const vector<vector<int>>& graph, const vector<int>& alarms){
	for(int i = 1; i < graph.size(); i++){
		find_alarm(i, graph, alarms);
	}
}

void mark_can_reach_silent_alarm(const vector<vector<int>>& graph, const vector<int>& alarms){
	//TODO
}

void compress(vector<vector<int>>& graph){

	vector<vector<int>> graph_c;
	graph_c.resize(graph.size());

	for(int u = 1; u < graph.size(); u++){
		if(to_remove[u]) continue;

		for(int v : graph[u]){
			if(!to_remove[v]){
				graph_c[u].push_back(v);
			}
		}
	}

	graph = graph_c;
}

void reduce_graph(vector<vector<int>>& graph, vector<int>& alarms_r, vector<int>& alarms_s){

	// init data structures
	for(int i = 1; i < graph.size(); i++){
		seen.push_back(false);
		to_remove.push_back(false);
	}

	// mark vertexes which are reachable from a ringing alarm
	mark_reachable_from_ringing_alarm(graph, alarms_r);

	// mark vertexes which don't reach a ringing alarm
	seen.assign(seen.size(), false);
	mark_cannot_reach_ringing_alarm(graph, alarms_r);

	// mark vertexes which reach a silent alarm
	seen.assign(seen.size(), false);
	mark_can_reach_silent_alarm(graph, alarms_s);

	// remove marked vertexes & edges to marked vertexes
	compress(graph);
}