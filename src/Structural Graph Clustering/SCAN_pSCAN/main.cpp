#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include "disjoint_set.h"
#include "Graph.h"

typedef int Vertex;
typedef std::unordered_map<Vertex, std::vector<Vertex>> AdjacentTable;

void printGraph(int n, AdjacentTable& graph)
{
	for (Vertex u = 0; u < n; u++)
	{
		std::cout << "[" << u << "] ";
		for (Vertex v : graph[u])
		{
			printf("%d ", v);
			std::cout << v << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

AdjacentTable buildGraph(std::vector<std::vector<Vertex>>& edges)
{
	std::cout << "building graph...\n";
	AdjacentTable graph;
	for (std::vector<Vertex>& edge : edges)
	{
		Vertex u = edge[0], v = edge[1];
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	return graph;
}

std::vector<std::vector<Vertex>> readEdges(const char* filename)
{
	//std::cout << "reading edges from file...\n";
	std::vector<std::vector<int>> edges;
	FILE *file = fopen(filename, "r");
	assert(file != NULL);
	char buf[32];
	while (!feof(file))
	{
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), file);
		char *p = strchr(buf, '\t');
		char *q = strchr(buf, '\n');
		if (p == nullptr || q == nullptr) break;
		*p = 0, *q = 0;
		Vertex u = atoi(buf), v = atoi(p + 1);
		edges.push_back({ u, v });
	}
	fclose(file);
	return edges;
}

void TEST1(float epsilon, int miu)
{
	std::cout << "\n======== [ TEST1 ] ========\n";

	std::vector<std::vector<Vertex>> edges = {
		{ 0, 1 }, { 1, 4 }, { 4, 5 }, { 5, 3 }, { 3, 0 }, { 0, 2 }, { 1, 2 }, { 4, 2 },
		{ 5, 2 }, { 3, 2 }, { 4, 6 }, { 5, 7 }, { 7, 8 }, { 8, 9 }, { 9, 11 }, { 11, 10 },
		{ 10, 8 }, { 9, 10 } };
	
	Graph graph(12, edges);
	std::vector<std::vector<Vertex>> C;
	
	std::cout << "\n=== SCAN ===\n";

	C = graph.SCAN(epsilon, miu);
	std::cout << "\nepsilon = " << epsilon << ", miu = " << miu;
	for (unsigned int i = 0; i < C.size(); i++)
	{
		std::cout << "\ncluster " << i + 1 << " [ ";
		for (int v : C[i]) std::cout << v << " ";
		std::cout << "]";
	}
	std::cout << "\n";

	std::cout << "\n=== pSCAN ===\n";

	graph.Reset();
	C = graph.pSCAN(epsilon, miu);
	std::cout << "\nepsilon = " << epsilon << ", miu = " << miu;
	for (unsigned int i = 0; i < C.size(); i++)
	{
		std::sort(C[i].begin(), C[i].end());
		std::cout << "\ncluster " << i + 1 << " [ ";
		for (int v : C[i]) std::cout << v << " ";
		std::cout << "]";
	}
	std::cout << "\n";
}

void TEST2(int nr_vertices, const char* filename, float epsilon, int miu)
{
	std::cout << "\n======== [ TEST2 ] ========\n";

	std::vector<std::vector<int>> edges = readEdges(filename);
	Graph graph(nr_vertices, edges);
	std::vector<std::vector<Vertex>> C;
	clock_t start, end;
	double time_elapsed;

	printf("\n=== SCAN (%s) ===\n", filename);

	start = clock();
	C = graph.SCAN(epsilon, miu);
	end = clock();
	time_elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "\nepsilon = " << epsilon << ", miu = " << miu << ". Time elapsed = " << time_elapsed;
	for (unsigned int i = 0; i < C.size(); i++)
	{
		std::sort(C[i].begin(), C[i].end());
		std::cout << "\ncluster " << i + 1 << " [ ";
		for (int v : C[i]) std::cout << v << " ";
		std::cout << "]";
	}
	std::cout << "\n";
	
	printf("\n=== pSCAN (%s) ===\n", filename);

	graph.Reset();
	start = clock();
	graph.Reset();
	C = graph.pSCAN(epsilon, miu);
	end = clock();
	time_elapsed = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	std::cout << "\nepsilon = " << epsilon << ", miu = " << miu << ". Time elapsed = " << time_elapsed;
	for (unsigned int i = 0; i < C.size(); i++)
	{
		std::sort(C[i].begin(), C[i].end());
		std::cout << "\ncluster " << i + 1 << " [ ";
		for (int v : C[i]) std::cout << v << " ";
		std::cout << "]";
	}
	std::cout << "\n";
}


int main()
{
	freopen("out.txt", "w", stdout);
	float epsilon[] = { 0.5, 0.6, 0.7, 0.8 };
	int miu[] = { 4, 6, 8, 10 };
#if 1
	for (int i = 0; i < _countof(epsilon); i++)
	{
		for (int j = 0; j < _countof(miu); j++)
		{
			TEST2(115, "football\\football.txt", epsilon[i], miu[j]);
		}
	}
#else
	TEST2(62, "dolphins\\dolphins.txt", 0.7, 4);
	TEST2(62, "dolphins\\dolphins.txt", 0.8, 3);
	TEST2(62, "dolphins\\dolphins.txt", 0.5, 4);
#endif
	fclose(stdout);
}