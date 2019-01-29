#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
#include <cmath>
#include <queue>
const int Mnogo = 429496;

class Graph {
public:
	Graph(int new_size)
	{
		size = new_size;
		//buffer.resize(size);
		buffer.assign(size, std::list<std::pair<int, int> >());
	}

	int GetSize() const
	{
		return size;
	}

	void AddEdge(int from, int to, int weight)
	{
		buffer[to].push_back(std::make_pair(weight, from));
		buffer[from].push_back(std::make_pair(weight, to));

	}

	void GetRelatives(int vertex, std::vector<std::pair<int, int> > &vect) const
	{
		vect.clear();
		for (const std::pair<int, int> &i : buffer[vertex])
		{
			vect.push_back(i);
		}
	}

private:
	int size;
	std::vector<std::list<std::pair<int, int> > > buffer;
};

int Dijkstra(Graph &graph, int start, int finish)
{
	std::vector<int> ways(graph.GetSize(), Mnogo);
	ways[start] = 0;
	std::vector<bool> used(graph.GetSize(), false);
	std::set<std::pair<int, int> > que;
	que.emplace(std::make_pair(0, start));
	
	while (!que.empty())
	{
		int cur = que.begin()->second;
		used[cur] = true;
		que.erase(que.begin());

		std::vector<std::pair<int, int> > children;
		graph.GetRelatives(cur, children);
		for (std::pair<int, int> child : children)
		{
			if (ways[child.second] > ways[cur] + child.first) //
			{
				ways[child.second] = ways[cur] + child.first; //
				que.emplace(std::make_pair(ways[child.second], child.second)); //
			}
		}
	}

	return ways[finish];
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
		graph.AddEdge(start, finish, weight);
	}
	int start;
	int finish;
	std::cin >> start >> finish;

	int res = Dijkstra(graph, start, finish);
	std::cout << res;

	return 0;
}

/*6
9
0 3 1
0 4 2
1 2 7
1 3 2
1 4 3
1 5 3
2 5 3
3 4 4
3 5 6
0 2*/
