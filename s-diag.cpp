#pragma once

#include <unordered_set>
#include <vector>

#include "io.cpp"

void remove_successor_alarm_rec(int cur, const vector<vector<int>>& graph, unordered_set<int>& alarms_r, vector<bool>& seen, vector<int> to_erase){

	if(seen[cur]) return;
	seen[cur] = true;

	// alarm can be reached from caller 
	if(alarms_r.contains(cur)){
		to_erase.push_back(cur);
	}

	// check children
	for(int v : graph[cur]){
		remove_successor_alarm_rec(v, graph, alarms_r, seen, to_erase);
	}
}

void remove_successor_alarm(const vector<vector<int>>& graph, unordered_set<int>& alarms_r){

	vector<bool> seen(graph.size(), false);
	vector<int> to_erase;

	// try to reach an alarm from an alarm
	for(int a : alarms_r){
		for(int v : graph[a]){
			remove_successor_alarm_rec(v, graph, alarms_r, seen, to_erase);
		}
	}

	// remove ringing alarms that can be reached from another ringing alarm
	for(int a : to_erase){
		alarms_r.erase(a);
	}
}

vector<vector<int>> transpose(const vector<vector<int>>& graph){

	// reset reverse graph
	vector<vector<int>> graph_t(graph.size());

	// fill reverse graph
	for(int u = 1; u < graph.size(); u++){
		for(int v : graph[u]){
			graph_t[v].push_back(u);
		}
	}

	return graph_t;
}

// travers via graph_t, remove edges in graph
void remove_predecessors_silent_alarm_rec(int cur, vector<vector<int>>& graph, const vector<vector<int>>& graph_t, vector<bool>& seen){

	if(seen[cur]) return;
	seen[cur] = true;

	// delete predecessors 
	for(int v : graph_t[cur]){
		remove_predecessors_silent_alarm_rec(v, graph, graph_t, seen);
	}

	// remove all outgoing edges of cur (in the initial graph)
	// cur's predecessors have already removed the incoming edges 
	graph[cur].clear();
}

void remove_predecessors_silent_alarm(vector<vector<int>>& graph, const vector<vector<int>>& graph_t, const unordered_set<int>& alarms_s){

	// init seen
	vector<bool> seen(graph.size(), false);

	// for each silent alarm: delete children & self
	for(int s : alarms_s){
		remove_predecessors_silent_alarm_rec(s, graph, graph_t, seen);
	}
}

// returns: the number of predecessors
int get_num_pred(int cur, const vector<vector<int>>& graph_t){

	// count all predecessors
	int num_pred = 1;
	for(int p : graph_t[cur]){
		num_pred += get_num_pred(p, graph_t);
	}
	return num_pred;
}

void find_set_S(const vector<vector<int>>& graph_t, const unordered_set<int>& alarms_r){

	int min_pred_alarm = 0;
	int min_num_pred = graph_t.size();

	// find the ringing alarm with the minimum number of predecessors
	int num_pred;
	for(int a : alarms_r){
		num_pred = get_num_pred(a, graph_t);
		if(num_pred < min_num_pred){
			min_pred_alarm = a;
			min_num_pred = num_pred;
		}
	}

	// print result
	print_predecessors(min_pred_alarm, graph_t);
}

void s_diag(vector<vector<int>>& graph, unordered_set<int>& alarms_r, const unordered_set<int>& alarms_s){

	// remove all alarms that have a ringing alarm as predecessor
	remove_successor_alarm(graph, alarms_r);

	// create transposed graph (predecessors)
	vector<vector<int>> graph_t = transpose(graph);

	// remove all predecessors of silent alarms
	// traverses 'graph_t', updates 'graph'
	remove_predecessors_silent_alarm(graph, graph_t, alarms_s);

	// update transposed graph
	graph_t = transpose(graph);

	// find minimum set S such that S contains at least one failure source
	find_set_S(graph_t, alarms_r);
}