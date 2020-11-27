#include <cstdio>

#include "io.cpp"
#include "unused_nodes.cpp"
#include "scc.cpp"

using namespace std;

vector<vector<int>> graph;
vector<int> alarms;

int main(){

	// read in the graph & the alarms
	read_input(graph, alarms);

    // compress strongly connected components
    tarjans_SCC(graph);
    compress_SCC(graph);

    // remove all nodes which are reachable from an alarm
    remove_unused_nodes(graph, alarms);
    print_graph(graph);
	print_alarms(alarms);

    // remove components without alarms
    return 0;
}