#include <vector>

vector<bool> seen;
vector<int> to_remove;

void mark_reachable_from_ringing_alarm_rec(int cur, const vector<vector<int>>& graph){

	// mark current vertex as seen & removable
	if(seen[cur]) return;
	seen[cur] = true;
	to_remove[cur] = true;

	// mark children as to_remove
	for(int v : graph[cur]){
		mark_reachable_from_ringing_alarm_rec(v, graph);
	}
}

// O(V + E)
// input: graph, ringing alarms
void mark_reachable_from_ringing_alarm(const vector<vector<int>>& graph, const vector<int>& alarms){

	// for each ringing alarm: mark children as removable
	for(int a : alarms){
		for(int v : graph[a]){
			mark_reachable_from_ringing_alarm_rec(v, graph);
		}
	}
}

void mark_cannot_reach_ringing_alarm_rec(int cur, const vector<vector<int>>& graph, const vector<int>& alarms){

	// removed / seen this vertex before
	if(to_remove[cur] || seen[cur]) return;
	seen[cur] = true;

	// cur has a ringing alarm (=> children are not interesting)
	if(find(alarms.begin(), alarms.end(), cur) != alarms.end()){
		// to_remove[cur] stays false
		return;
	}	

	// assume cur can be removed
	to_remove[cur] = true;

	// test if a child disagrees with that
	for(int v : graph[cur]){
		mark_cannot_reach_ringing_alarm_rec(v, graph, alarms);
		to_remove[cur] &= to_remove[v];
	}
}

// input: graph, ringing alarms
void mark_cannot_reach_ringing_alarm(const vector<vector<int>>& graph, const vector<int>& alarms){
	
	// for each vertex: try to reach a ringing alarm
	for(int i = 1; i < graph.size(); i++){
		mark_cannot_reach_ringing_alarm_rec(i, graph, alarms);
	}
}

// input: graph, silent alarms
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