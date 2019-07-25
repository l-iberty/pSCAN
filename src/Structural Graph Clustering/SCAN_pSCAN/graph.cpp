#include "Graph.h"

Graph::Graph(int nr_vertices, std::vector<std::vector<Vertex>>& edges)
	: nr_vertices_(nr_vertices), edges_(edges),
	epsilon_(0), miu_(0),
	visited_(nr_vertices, false),
	core_(nr_vertices, false),
	set_(nr_vertices),
	similarities_(nr_vertices, std::vector<float>(nr_vertices, 0)),
	similar_degree_(nr_vertices, 0),
	effective_degree_(nr_vertices, 0)
{
	BuildGraph();
}

void Graph::Reset()
{
	epsilon_ = 0, miu_ = 0;
	visited_.assign(nr_vertices_, false);
	core_.assign(nr_vertices_, false);
	similarities_.assign(nr_vertices_, std::vector<float>(nr_vertices_, 0));
	similar_degree_.assign(nr_vertices_, 0);
	effective_degree_.assign(nr_vertices_, 0);
	core_clusters_.clear();
}

std::vector<std::vector<Vertex>> Graph::SCAN(float epsilon, int miu)
{
	assert(epsilon > 0 && epsilon <= 1 && miu >= 2);
	epsilon_ = epsilon, miu_ = miu;

	// compute structural similarity for each edge, and ϵ-neighborhoods for each vertex.
	AdjacentTable epsilon_neis; // ϵ-neighborhoods
	for (std::vector<Vertex>& e : edges_)
	{
		Vertex u = e[0], v = e[1];
		float sim = ComputeSimilarity(u, v);
		//printf("[%d,%d] %.2f\n", u, v, sim);

		// each vetex belongs to its ϵ-neighborhoods.
		if (!visited_[u])
		{
			visited_[u] = true;
			epsilon_neis[u].push_back(u);
		}
		if (!visited_[v])
		{
			visited_[v] = true;
			epsilon_neis[v].push_back(v);
		}

		if (sim >= epsilon)
		{
			epsilon_neis[u].push_back(v);
			epsilon_neis[v].push_back(u);
		}
	}
	
	//std::cout << "\nepsilon-neighborhoods for each vertex:\n";
	//printGraph(epsilon_neis);

	visited_.assign(nr_vertices_, false);
	std::vector<std::vector<Vertex>> clusters;
	for (Vertex u = 0; u < nr_vertices_; u++)
	{
		if (!visited_[u])
		{
			std::vector<int> cluster = { u };
			for (unsigned int i = 0; i < cluster.size(); i++)
			{
				Vertex v = cluster[i];
				if (!visited_[v])
				{
					visited_[v] = true;
					if (epsilon_neis[v].size() >= miu)
					{
						cluster = my_union(cluster, epsilon_neis[v]);
					}
				}
			}
			if (cluster.size() > 1) clusters.push_back(cluster);
		}
	}
	return clusters;
}

std::vector<std::vector<Vertex>> Graph::pSCAN(float epsilon, int miu)
{
	assert(epsilon > 0 && epsilon <= 1 && miu >= 2);
	epsilon_ = epsilon, miu_ = miu;

	for (Vertex u = 0; u < nr_vertices_; u++)
	{
		similar_degree_[u] = 0;
		effective_degree_[u] = graph_[u].size() + 1;
	}

	for (Vertex u = 0; u < nr_vertices_; u++)
	{
		CheckCore(u);
		if (similar_degree_[u] >= miu_)
		{
			core_[u] = true;
			ClusterCore(u);
		}
	}
	//set_.DispRoots();
	GetCoreClusters();
	std::vector<std::vector<Vertex>> clusters = ClusterNoncore();

	return clusters;
}

void Graph::BuildGraph()
{
	for (std::vector<Vertex>& e : edges_)
	{
		Vertex u = e[0], v = e[1];
		graph_[u].push_back(v);
		graph_[v].push_back(u);
	}
}

float Graph::GetSimilarity(Vertex u, Vertex v)
{
	assert(similarities_[u][v] == similarities_[v][u]);
	return similarities_[u][v];
}

float Graph::ComputeSimilarity(Vertex u, Vertex v)
{
	if (GetSimilarity(u, v) != 0) return GetSimilarity(u, v);

	std::vector<Vertex> neis_u = graph_[u] + u;
	std::vector<Vertex> neis_v = graph_[v] + v;
	float sim = static_cast<float>(my_intersection(neis_u, neis_v).size()) /
		static_cast<float>(std::sqrt(neis_u.size() * neis_v.size()));
	similarities_[u][v] = similarities_[v][u] = sim;
	return sim;
}

float Graph::ApproximateSimilarity(Vertex u, Vertex v)
{
	return ComputeSimilarity(u, v);
#if 0
	// In practice, we still need to compute the exact structural similarity between
	// vertices u and v. That is, we cannot use pruning rule for effectively determining
	// whether vertices u and v are structural-similar.

	if (GetSimilarity(u, v) != 0) return GetSimilarity(u, v);

	std::vector<Vertex> neis_u = graph_[u] + u;
	std::vector<Vertex> neis_v = graph_[v] + v;

	int deg_u = neis_u.size();
	int deg_v = neis_v.size();
	if (deg_u < epsilon_ * epsilon_ * deg_v ||
		deg_v < epsilon_ * epsilon_ * deg_u)
	{
		// deg⁡(u) < 𝜖^2 deg⁡(v) OR deg⁡(v) < 𝜖^2 deg⁡(u) => σ(u, v) < 𝜖
		similarities_[u][v] = similarities_[v][u] = -1;
	}
	else
	{
		ComputeSimilarity(u, v);
	}
	return similarities_[u][v];
#endif
}

void Graph::CheckCore(Vertex u)
{
	std::vector<Vertex> neis = graph_[u] + u; // structural neighborhoods of u

	// if ed(u) < μ then u is not a core vertex, of if sd(u) ≥ μ then u is a core vertex.
	// Otherwise, sd(u) < μ ≤ ed(u), and we need to compute structural similarities between
	// u ans its neighbors to determine whether u is a core vertex.
	if (effective_degree_[u] >= miu_ && similar_degree_[u] < miu_)
	{
		effective_degree_[u] = graph_[u].size() + 1; similar_degree_[u] = 0; // reinitialize ed(u) and sd(u)
		for (Vertex v: neis)
		{
			// For each vertex v ∈ N[u], we first compute the structural similarity between u and v,
			// and update sd(u) or ed(u) accordingly.
			float sim = ApproximateSimilarity(u, v);
			if (sim >= epsilon_) similar_degree_[u]++;
			else effective_degree_[u]--;
			// we also update sd(v) or ed(v) if v has not been explored.
			if (!visited_[v])
			{
				if (sim >= epsilon_) similar_degree_[v]++;
				else effective_degree_[v]--;
			}
			// The computational process is terminated as long as we achieve our goal.
			if (effective_degree_[u] < miu_ || similar_degree_[u] >= miu_) break;
		}
	}
	visited_[u] = true;
}

void Graph::ClusterCore(Vertex u)
{
	std::vector<Vertex> neis = graph_[u] + u; // structural neighborhoods of u
	for (Vertex v : neis)
	{
		bool computed = (GetSimilarity(u, v) != 0);
		if (computed)
		{
			if (u != v && similar_degree_[v] >= miu_ && // v is a core vertex
				GetSimilarity(u, v) >= epsilon_) // v is structural-similar to u
			{
				set_.Union(u, v); // assign v to the same cluster as u
			}
		}
		else
		{
			if (set_.Find(u) != set_.Find(v) && // u ans v have not been assigned to the same cluster yet
				effective_degree_[v] >= miu_) // if ed(v) < μ then v is NOT a core vertex
			{
				float sim = ApproximateSimilarity(u, v);
				if (!visited_[v])
				{
					if (sim >= epsilon_) similar_degree_[v]++;
					else effective_degree_[v]--;
				}
				if (similar_degree_[v] >= miu_ && sim >= epsilon_)
				{
					set_.Union(u, v);
				}
			}
		}
	}
}

void Graph::GetCoreClusters()
{
	int *roots = set_.GetRoots();
	std::vector<Vertex> subset;
	for (int x = 0; x < set_.GetSize(); x++)
	{
		if (core_[x])
		{
			int root = set_.Find(x);
			assert(root >= 0 && root < set_.GetSize());
			core_clusters_[root].push_back(x);
		}
	}
}

std::vector<std::vector<Vertex>> Graph::ClusterNoncore()
{
	std::vector<std::vector<Vertex>> clusters;

	for (auto it = core_clusters_.begin(); it != core_clusters_.end(); it++)
	{
		std::vector<Vertex>& subset = it->second;
		for (unsigned int i = 0; i < subset.size(); i++)
		{
			Vertex u = subset[i];
			for (Vertex v : graph_[u])
			{
				if (similar_degree_[v] < miu_ && !linear_search(subset, v))
				{
					float sim = ApproximateSimilarity(u, v);
					if (sim >= epsilon_) subset.push_back(v);
				}
			}
		}
		clusters.push_back(subset);
	}
	return clusters;
}

