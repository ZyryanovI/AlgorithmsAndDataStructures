#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <queue>
#include <cmath>

class Graph {
public:
	Graph(int new_size)
	{
		size = new_size;
		buffer.assign(size, std::vector<double>(size, -1));
	}

	void AddEdge(int from, int to, double weight)
	{
		buffer[from][to] = weight;
	}

	int GetSize()
	{
		return size;
	}

	double GetWeight(int from, int to)
	{
		return buffer[from][to];
	}

	void GetPrev(int vertex, std::vector<int> &vect)
	{
		vect.clear();
		for (int i = 0; i < size; i++)
		{
			if (buffer[i][vertex] != -1)
			{
				vect.push_back(i);
			}
		}
	}

private:
	int size;
	std::vector<std::vector<double>> buffer;
};

bool Floyd_Bellman(Graph &graph)
{
	for (int i = 0; i < graph.GetSize(); ++i)
	{
		std::vector<double> ways(graph.GetSize(), -1);
		ways[i] = 1;
		std::vector<int> vertices(graph.GetSize());

		std::vector<bool> used(graph.GetSize(), false);

		for (int j = 0; j < graph.GetSize() -1; ++j)
		{
			for (int k = 0; k < graph.GetSize(); ++k)
			{
				if (!used[k]) /////
				{
					graph.GetPrev(k, vertices);
					used[k] = true; ////
					for (int u : vertices)
					{
						if ((ways[u] != -1) && (ways[k] < ways[u] * graph.GetWeight(u, k)))
						{
							ways[k] = ways[u] * graph.GetWeight(u, k);
						}
					}
				}
			}
		}

		for (int j = 0; j < graph.GetSize(); ++j)
		{
			graph.GetPrev(j, vertices);
			for (int u : vertices)
			{
				if ((ways[u] != -1) && (ways[j] < ways[u] * graph.GetWeight(u, j)))
				{
					return true;
				}
			}
		}
		return false;
	}


}





int main()
{
	int n = 0;
	std::cin >> n;
	Graph graph(n);
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			if (i == j)
			{
				continue;
			}
			double x;
			std::cin >> x;
			graph.AddEdge(i, j, x);
		}
	}
	
	if (Floyd_Bellman(graph))
	{
		std::cout << "YES";
	}
	else
	{
		std::cout << "NO";
	}

	return 0;
}