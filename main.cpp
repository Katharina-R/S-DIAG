#include <unordered_set>
#include <vector>

#include "io.cpp"
#include "s-diag.cpp"
#include "scc.cpp"

using namespace std;

bool can_reach_silent_alarm(int cur, vector<bool>& seen, const vector<vector<int>>& graph, const unordered_set<int> alarms_s){
	if(seen[cur]) return false;
	seen[cur] = true;

	if(alarms_s.contains(cur)) return true;

	for(int v : graph[cur]){
		if(can_reach_silent_alarm(v, seen, graph, alarms_s)){
			return true;
		}
	}

	return false;
}

bool valid_input(const vector<vector<int>>& graph, const unordered_set<int> alarms_r, const unordered_set<int> alarms_s){
	// at least one vertex required
	if(graph.size() < 1){
		printf("The graph needs at least one vertex\n");
		return false;
	}

	// at least 1 ringing alarm required
	if(alarms_r.size() < 1){
		printf("No ringing alarms. There is nothing to do.");
		return false;
	}

	// A ringing alarm may not reach a silent alarm
	vector<bool> seen(graph.size(), false);

	for(int a : alarms_r){
		if(can_reach_silent_alarm(a, seen, graph, alarms_s)){
			printf("Alarm %d can reach a silent alarm. This is not allowed.\n", a);
			return false;
		}
	}

	return true;
}

int main(){

	// read in the graph & the alarms
	auto[graph, alarms_r, alarms_s] = read_input();

	// validate input
	if(!valid_input(graph, alarms_r, alarms_s)){
		return 0;
	}

    // find & compress SSC
    tarjans_SCC(graph);
    compress_SCC(graph, alarms_r, alarms_s);
    print_graph(graph);

	// find minimum set S which contains at least one failure source
	s_diag(graph, alarms_r, alarms_s);

    return 0;
}