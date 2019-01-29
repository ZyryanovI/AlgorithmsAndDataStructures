#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <stack>
#include <ctime>

const int INF = 2147483646;

class Edge {
public:

	Edge()
	{
		weight = 0;
		from = 0;
		to = 0;
	}

	Edge(int new_from, int new_to, int new_weight) 
	{
		from = new_from;
		to = new_to;
		weight = new_weight;
	}

	int Get_Weight() const
	{
		return weight;
	}

	int Get_From() const
	{
		return from;
	}

	int Get_To() const
	{
		return to;
	}


	void Set_Weight(int new_weight)
	{
		weight = new_weight;
	}

	void Set_From(int new_from)
	{
		from = new_from;
	}

	void Set_To(int new_to)
	{
		to = new_to;
	}
private:
	int weight;
	int from;
	int to;

};



class BorovkaAlgorithm {
public:
	BorovkaAlgorithm()
	{}

	BorovkaAlgorithm(int new_v_number, std::vector<Edge> & new_edges)
	{
		vertex_number = new_v_number;
		edge_number = new_edges.size();
		edges = new_edges;
		cur_components_number = new_v_number;
		rank.assign(new_v_number, 0);
		parents.resize(new_v_number);
		for (int i = 0; i < new_v_number; ++i)
		{
			parents[i] = i;
		}
	}

	int FindComponentParent(int vertex, std::vector<int> &parents) 
	{
		int parent = parents[vertex];
		int cur_vertex = vertex;

		while (parent != cur_vertex)
		{
			cur_vertex = parent;
			parent = parents[cur_vertex];
		}
		return cur_vertex;
		
	}

	void Make_In_One_Component(int vertex1, int vertex2)
	{
		std::vector<int> parent_vertex(2);
		parent_vertex[0] = FindComponentParent(vertex1, parents);
		parent_vertex[1] = FindComponentParent(vertex2, parents);

		if (parent_vertex[0] == parent_vertex[1])
		{
			return;
		}


		if (rank[parent_vertex[0]] < rank[parent_vertex[1]]) {
			std::swap(parent_vertex[0], parent_vertex[1]);
		}

		parents[parent_vertex[1]] = parent_vertex[0];

		if (rank[parent_vertex[0]] == rank[parent_vertex[1]])
		{
			++rank[parent_vertex[0]];
		}

	}



	int Find_MST_Size()
	{
		int result = 0;

		while (cur_components_number != 1)
		{
			std::vector<int> cur_buffer(vertex_number, -1);
			for (int i = 0; i < edge_number; ++i)
			{
				Edge cur_edge = edges[i];
				std::vector<int> vertexes(2);
				vertexes[0] = FindComponentParent(cur_edge.Get_From(), parents);
				vertexes[1] = FindComponentParent(cur_edge.Get_To(), parents);
				if (vertexes[0] == vertexes[1])
				{
					continue;
				}

				for (int j = 0; j < 2; ++j)
				{
					if ((cur_buffer[vertexes[j]] == -1) || (cur_edge.Get_Weight() < edges[cur_buffer[vertexes[j]]].Get_Weight()))
					{
						cur_buffer[vertexes[j]] = i;
					}
				}

			}

			int decrease_number_of_components = 0;

			for (int i = 0; i < vertex_number; ++i)
			{
				if (cur_buffer[i] == -1)
				{
					continue;
				}
				else {
					Edge cur_edge = edges[cur_buffer[i]];
					std::vector<int> componentes(2);
					componentes[0] = FindComponentParent(cur_edge.Get_From(), parents);
					componentes[1] = FindComponentParent(cur_edge.Get_To(), parents);
					if (componentes[0] == componentes[1])
					{
						continue;
					}

					result += cur_edge.Get_Weight();
					++decrease_number_of_components;
					Make_In_One_Component(componentes[0], componentes[1]);
				}


			}

			cur_components_number -= decrease_number_of_components;

		}

		return result;

	}






private:
	std::vector<Edge> MST;
	int vertex_number;
	int edge_number;
	int cur_components_number;
	std::vector<Edge> edges;
	std::vector<int> parents;
	std::vector<int> rank;
};


//***************************************************************************







int main()
{
	int n;
	int m;
	std::cin >> n >> m;
	std::vector<Edge> buffer;
	for (int i = 0; i < m; ++i)
	{
		int from;
		int to;
		int weight;
		std::cin >> from >> to >> weight;
		--from;
		--to;
		Edge new_edge(from, to, weight); 
		buffer.push_back(new_edge);
	}

	BorovkaAlgorithm alg(n, buffer);
	std::cout << alg.Find_MST_Size();


	return 0;
}

