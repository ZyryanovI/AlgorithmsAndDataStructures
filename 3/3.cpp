#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

class Graph {
public:

	Graph()
	{}

	Graph(int new_size)
	{
		size = new_size;
		buffer.assign(size, std::vector<int>(size, 0));
	}

	void Add_Edge(int from, int to, int weight)
	{
		buffer[from][to] += weight;
	}

	int Get_Size()
	{
		return size;
	}

	void Get_Reletives(int vertex, std::vector<std::pair<int, int>> &vertises)
	{
		vertises.clear();
		for (int i = 0; i < size; ++i)
		{
			if (buffer[vertex][i] != 0)
			{
				vertises.push_back(std::make_pair(i, buffer[vertex][i]));
			}
		}
	}


private:
	int size;
	std::vector<std::vector<int> > buffer;


};

int Increase_Flow(Graph &graph, int start, int finish)
{
	const int INF = 2147483646;
	std::vector<std::pair<int, int> > parents(graph.Get_Size(), std::pair<int, int>(INF, INF));
	
	parents[start].first = start;
	parents[start].second = 0;

	std::queue<int> queue_for_bfs;
	queue_for_bfs.push(start);
	while (!queue_for_bfs.empty())
	{
		int cur = queue_for_bfs.front();
		queue_for_bfs.pop();
		if (cur == finish)
		{
			break;
		}
		std::vector<std::pair<int, int> > reletives;
		graph.Get_Reletives(cur, reletives);
		for (std::pair<int, int> & edge : reletives)
		{
			if (parents[edge.first].first == INF)
			{
				parents[edge.first].first = cur;
				parents[edge.first].second = edge.second;
				queue_for_bfs.push(edge.first);
			}
		}

	}

	if (parents[finish].first == INF)
	{
		return 0;
	}
	else
	{
		int delta = INF;
		int cur = finish;
		while (cur != start)
		{
			if (parents[cur].second < delta)
			{
				delta = parents[cur].second;
			}
			cur = parents[cur].first;
		}

		cur = finish;
		while (cur != start)
		{
			graph.Add_Edge(parents[cur].first, cur, (-1)*delta); ////
			graph.Add_Edge(cur, parents[cur].first, delta);
			cur = parents[cur].first;
		}

		return delta;
	}


}

int Find_Max_Flow(Graph &graph, int start, int finish)
{
	int delta = Increase_Flow(graph, start, finish);
	int flow = 0;


	while (delta != 0)
	{
		flow += delta;
		delta = Increase_Flow(graph, start, finish);
	}

	return flow;
}






int main()
{
	int n;
	int m;
	std::cin >> n >> m;

	Graph graph(n);

	for (int i = 0; i < m; ++i)
	{
		int start;
		int finish;
		int weight;
		std::cin >> start >> finish >> weight;
		--start;
		--finish;
		graph.Add_Edge(start, finish, weight);
	}

	std::cout << Find_Max_Flow(graph, 0, n-1);



	return 0;
}
