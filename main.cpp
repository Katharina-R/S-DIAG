#include <cstdio>

#include "io.cpp"
#include "scc.cpp"

using namespace std;

vector<vector<int>> graph;
vector<int> alarms;

int main(){

	// read in the graph & the alarms
	read_input(graph, alarms);

    // compress strongly connected components
    print_graph(graph);
    tarjans_SCC(graph);
    compress_SCC(graph);
    print_graph(graph);
    print_alarms(alarms);

    // remove all nodes which are reachable from an alarm
    // TODO

    // remove components without alarms
    return 0;
}