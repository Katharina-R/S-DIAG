#pragma once

#include <unordered_set>
#include <vector>

#include "io.cpp"

void create_reverse_graph(const vector<vector<int>>& graph, vector<vector<int>>& graph_rev){

	// reset reverse graph
	graph_rev.clear();
	graph_rev.resize(graph.size());

	// fill reverse graph
	for(int u = 1; u < graph.size(); u++){
		for(int v : graph[u]){
			graph_rev[v].push_back(u);
		}
	}
}

void remove_predecessors_silent_alarm_rec(int cur, vector<vector<int>>& graph, const vector<vector<int>>& pred, vector<bool>& seen){

	// delete predecessors 
	for(int v : pred[cur]){
		remove_predecessors_silent_alarm_rec(v, graph, pred, seen);
	}

	// delete self: remove all outgoing edges of cur
	// => the reverse graph will not have any incoming edges
	graph[cur] = {};
}

void remove_predecessors_silent_alarm(vector<vector<int>>& graph, const vector<vector<int>>& pred, const unordered_set<int>& alarms_s){

	// init seen
	vector<bool> seen;
	seen.resize(graph.size());
	seen.assign(0, graph.size());

	// for each silent alarm: delete children & self
	for(int s : alarms_s){
		remove_predecessors_silent_alarm_rec(s, graph, pred, seen);
	}
}

void find_num_pred_rec(int cur, const vector<vector<int>>& pred, vector<int>& num_pred){

	// already seen this node
	if(num_pred[cur] != 0){
		return;
	}

	// count all predecessors
	num_pred[cur] = 1;
	for(int p : pred[cur]){
		find_num_pred_rec(p, pred, num_pred);
		num_pred[cur] += num_pred[p];
	}
}

void find_set_S(const vector<vector<int>>& pred, const unordered_set<int>& alarms_r){

	// store the number of predecessors for each (visited) vertex
	vector<int> num_pred;
	num_pred.resize(pred.size());
	num_pred.assign(0, pred.size());

	// find the number of predecessors for each ringing alarm
	for(int a : alarms_r){
		find_num_pred_rec(a, pred, num_pred);
	}

	// find the ringing alarms with the smallest set of predecessors
	vector<int> min_pred_alarms;
	min_pred_alarms.push_back(*alarms_r.begin());
	for(int a : alarms_r){
		// found better set
		if(num_pred[a] < min_pred_alarms[0]){
			min_pred_alarms = {};
			min_pred_alarms.push_back(a);
		}
		// found equally good set
		if(num_pred[a] == min_pred_alarms[0]){
			min_pred_alarms.push_back(a);
		}
	}

	// print result
	print_number_of_result(min_pred_alarms);
	// the sets are mutually exclusive
	for(int a : min_pred_alarms){
		print_predecessors(a, pred);
	}
}

void s_diag(vector<vector<int>>& graph, const unordered_set<int>& alarms_r, const unordered_set<int>& alarms_s){

	// create reverse graph (predecessors)
	vector<vector<int>> pred;
	create_reverse_graph(graph, pred);

	// remove all predecessors of silent alarms
	remove_predecessors_silent_alarm(graph, pred, alarms_s);
	create_reverse_graph(graph, pred);

	// find minimum set S s.t. S contains at least one failure source
	find_set_S(pred, alarms_r);
}