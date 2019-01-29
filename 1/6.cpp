#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <list>
#include <stack>

class Graph {
public:

	Graph()
	{}

	Graph(int new_size)
	{
		size = new_size;
		in.resize(size);
		out.resize(size);
	}

	Graph(Graph *new_graph)
	{
		size = new_graph->VerticesCount();
		cur_time = 0;
		cur_component = 0;
		vertex_components.assign(size, 0);
		visited.assign(size, false);
		lowest_vertex.assign(size, 0);
		
		in.resize(size);
		out.resize(size);
		for (int i = 0; i < size; ++i)
		{
			std::vector<int> vect;
			new_graph->GetNextVertices(i, vect);
			for (int j : vect)
			{
				AddEdge(i, j);
			}
		}
	}

	~Graph()
	{}

	void AddEdge(int from, int to)
	{
		in[to].push_back(from);
		out[from].push_back(to);
	}

	int VerticesCount() const
	{
		return size;
	}

	void GetNextVertices(int vertex, std::vector<int>& vertices) const
	{
		vertices.clear();
		for (int i : out[vertex])
		{
			vertices.push_back(i);
		}

	}

	void GetPrevVertices(int vertex, std::vector<int>& vertices) const
	{
		vertices.clear();
		for (int i : in[vertex])
		{
			vertices.push_back(i);
		}
	}

	//************************************************

	void DFS(int vertex)
	{
		lowest_vertex[vertex] = cur_time;
		++cur_time;
		stack_for_tarjan.push(vertex);
		visited[vertex] = true;
		bool is_root = true;

		std::vector<int> children;
		GetNextVertices(vertex, children);
		for (int i : children)
		{
			if (visited[i] == false)
			{
				DFS(i);
			}

			//Проверяем наименьшее
			if (lowest_vertex[i] < lowest_vertex[vertex])
			{
				lowest_vertex[vertex] = lowest_vertex[i];
				is_root = false;
			}
		}

		if (is_root == true)
		{
			while (true)
			{
				int x = stack_for_tarjan.top();
				stack_for_tarjan.pop();
				vertex_components[x] = cur_component;
				int ver_count = VerticesCount();
				lowest_vertex[x] = ver_count + 1;
				if (vertex == x)
				{
					break;
				}
			}
			++cur_component;
		}

	}

	Graph Tarjan()
	{
		for (int i = 0; i < VerticesCount(); ++i)
		{
			if (visited[i] == false)
			{
				DFS(i);
			}
		}

		Graph cur_graph(cur_component);
		for (int i = 0; i < VerticesCount(); ++i)
		{
			std::vector<int> vertices;
			GetNextVertices(i, vertices);
				for (int j : vertices)
				{
					if (vertex_components[i] != vertex_components[j])
					{
						cur_graph.AddEdge(vertex_components[j], vertex_components[i]);
					}
				}
		}
		return cur_graph;
	}

private:
	std::vector<std::list<int>> in;
	std::vector<std::list<int>> out;
	int size;
	//*******************************************
	int cur_time;
	int cur_component;
	std::stack<int> stack_for_tarjan;
	std::vector<bool> visited;
	std::vector<int> lowest_vertex;
	std::vector<int> vertex_components;
};







int main()
{
	int n;
	int m;
	std::cin >> n >> m;
	Graph graph(n);

	for (int i = 0; i < m; ++i)
	{
		int first_ver;
		int second_ver;
		std::cin >> first_ver >> second_ver;
		graph.AddEdge(first_ver - 1, second_ver - 1);
	}

	Graph t_graph(&graph);

	Graph t_graph_real = t_graph.Tarjan();

	int without_out = 0;
	int without_in = 0;

	if (t_graph_real.VerticesCount() > 1)
	{
		for (int i = 0; i < t_graph_real.VerticesCount(); ++i)
		{
			std::vector<int> vert;
			t_graph_real.GetNextVertices(i, vert);
			if (vert.size() == 0)
			{
				++without_out;
			}
			t_graph_real.GetPrevVertices(i, vert);
			if (vert.size() == 0)
			{
				++without_in;
			}
		}
	}

	std::cout << std::max(without_in, without_out);
	return 0;
}