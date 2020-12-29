#include <unordered_set>
#include <vector>

#include "io.cpp"
#include "s-diag.cpp"
#include "scc.cpp"

using namespace std;

int main(){

	// read graph & compress SCC
	auto graph = read_graph();
	printf("INPUT GRAPH: ");
	print_graph(graph);
	auto id_new = tarjans_SCC(graph);
	compress_graph(id_new, graph);
	printf("COMPRESSED GRAPH: ");
	print_graph(graph);

	// read alarms
	auto alarms = read_alarms(false);

	// S-DIAG
	unordered_set<int> alarms_r, alarms_s;
	do {
		// read ringing alarms
		alarms_r = read_alarms(true);
		if(alarms_r.size() < 1){
			printf("No alarms are ringing. Diagnosis is stopped.\n");
			break;
		}
		
		// calculate silent alarms
		alarms_s.clear();
		for(int a : alarms){
			if(!alarms_r.contains(a)){
				alarms_s.insert(a);
			}
		}
		printf("INPUT ALARMS: ");
		print_alarms(alarms_r, alarms_s);

		// find minimum set S which contains at least one failure source
		compress_alarms(id_new, alarms_r, alarms_s);
		printf("ALARMS AFTER COMPRESSION: ");
		print_alarms(alarms_r, alarms_s);
		s_diag(graph, alarms_r, alarms_s);

	} while(true);

	// diagnosis finished
    return 0;
}