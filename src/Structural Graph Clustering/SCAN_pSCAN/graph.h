#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cassert>
#include "util.h"
#include "disjoint_set.h"

typedef int Vertex;
typedef std::unordered_map<Vertex, std::vector<Vertex>> AdjacentTable;

class Graph
{
public:
	Graph(int nr_vertices, std::vector<std::vector<Vertex>>& edges);
	~Graph() = default;
	std::vector<std::vector<Vertex>> SCAN(float epsilon, int miu);
	std::vector<std::vector<Vertex>> pSCAN(float epsilon, int miu);
	void Reset();

private:
	std::vector<std::vector<Vertex>> edges_;
	AdjacentTable graph_;
	int nr_vertices_;
	float epsilon_;
	int miu_;
	std::vector<bool> visited_;
	std::vector<bool> core_;
	std::vector<std::vector<float>> similarities_;
	DisjointSet set_;
	std::vector<int> similar_degree_, effective_degree_;
	std::unordered_map<Vertex, std::vector<Vertex>> core_clusters_;

	void BuildGraph();
	float GetSimilarity(Vertex u, Vertex v);
	float ComputeSimilarity(Vertex u, Vertex v);
	float ApproximateSimilarity(Vertex u, Vertex v);
	void CheckCore(Vertex u);
	void ClusterCore(Vertex u);
	void Graph::GetCoreClusters();
	std::vector<std::vector<Vertex>> ClusterNoncore();
};

#endif /* GRAPH_H */
