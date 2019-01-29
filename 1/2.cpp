#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

struct Vertex {
	bool visited;
	int depth;
	int parent;
	Vertex()
	{
		visited = false;
		depth = 0;
	}
};

class Graph {
public:

	Graph()
	{}
	Graph(int n)
	{
		size = n;
		buffer.resize(size);
	}
	~Graph()
	{}

	void AddEdge(int from, int to) {
		buffer[from].insert(to);
		buffer[to].insert(from);
	}

	int VerticesCount()
	{
		return size;
	}

	void GetNextVertices(int vertex, std::vector<int>& vect)
	{
		vect.clear();
		for (int i : buffer[vertex])
		{
			vect.push_back(i);
		}

	}

	int MyBFS(int vertex)
	{
		std::queue<int> q_for_bfs;
		q_for_bfs.push(vertex);
		std::vector<Vertex> vertices(size);
		vertices[vertex].visited = true;

		while (!q_for_bfs.empty())
		{
			int cur_vert = q_for_bfs.front();
			q_for_bfs.pop();
			std::vector<int> children_vect;
			GetNextVertices(cur_vert, children_vect);

			for (int i : children_vect)
			{
				if (!vertices[i].visited)
				{
					vertices[i].visited = true;
					vertices[i].parent = cur_vert;
					vertices[i].depth = vertices[cur_vert].depth + 1;
					q_for_bfs.push(i);

				}
				else {
					if ((vertices[i].visited)&&((i != vertices[cur_vert].parent)))
					{
						return vertices[i].depth + vertices[cur_vert].depth+1;
					}
				}
			}

		}
		return size + 1;
	}

	int FindMinCycle()
	{
		int mincycle = size + 1;
		for (int i = 0; i < size; ++i)
		{
			int cur_cycle = MyBFS(i);
			if (mincycle >= cur_cycle)
			{
				mincycle = cur_cycle;
			}
		}
		return mincycle;
	}



private:
	int size;
	std::vector<std::unordered_set<int> > buffer;
};



int main()
{
	int n;
	int m;
	std::cin >> n >> m;
	Graph graph(n);
	int first_vert;
	int second_vert;
	for (int i = 0; i < m; ++i)
	{
		std::cin >> first_vert >> second_vert;
		graph.AddEdge(first_vert, second_vert);
	}
	if (graph.FindMinCycle() == graph.VerticesCount() + 1)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << graph.FindMinCycle();
	}


	return 0;
}
