#include <cstdio>

#include "io.cpp"
#include "unused_nodes.cpp"
#include "scc.cpp"

using namespace std;

vector<vector<int>> graph;
vector<int> alarms_r; // ringing alarms
vector<int> alarms_s; // silent alarms

int main(){

	// read in the graph & the alarms
	read_input(graph, alarms_r, alarms_s);

    // compress strongly connected components
    tarjans_SCC(graph);
    compress_SCC(graph);

	// remove all components which:
		// - can be reached from a ringing alarm
		// - can NOT reach a ringing alarm
		// - can reach a silent alarm
    reduce_graph(graph, alarms_r, alarms_s);
    print_graph(graph);
	print_ringing_alarms(alarms_r);
	print_silent_alarms(alarms_s);

    // create reverse graph
    // TODO
    return 0;
}