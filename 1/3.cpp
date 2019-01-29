#include <iostream>
#include <vector>
#include <list>
#include <queue>
struct Vertex
{
	int depth;
	int ways;
	bool visited;

	Vertex()
	{
		depth = 0;
		ways = 0;
		visited = false;
	}
};

class Graph {
public:
	Graph()
	{}
	Graph(int new_size)
	{
		size = new_size;
		buffer.resize(size);
		buffer.resize(size);
	}
	~Graph()
	{}

	void AddEdge(int from, int to)
	{
		for (int i : buffer[from]) //чтобы без повторений
		{
			if (i == to)
			{
				return;
			}
		}
		buffer[from].push_back(to);
		buffer[to].push_back(from);
	}

	int VerticesCount()
	{
		return size;
	}
	
	void GetNextVertices(int vertex, std::vector<int>& vertices)
	{
		vertices.clear();
		for (int i : buffer[vertex])
		{
			vertices.push_back(i);
		}

	}


	int CountWays(int from, int to)
	{
		std::queue<int> q_for_bfs;
		q_for_bfs.push(from);
		std::vector<Vertex> information_about_ver(size);
		information_about_ver[from].ways = 1;
		while (!q_for_bfs.empty())
		{
			int cur_vertex = q_for_bfs.front();
			q_for_bfs.pop();
			std::vector<int> children;
			GetNextVertices(cur_vertex, children);
				for(int i : children)
				{
					if (!information_about_ver[i].visited)
					{
						information_about_ver[i].visited = true;
						information_about_ver[i].depth = information_about_ver[cur_vertex].depth+1;
						information_about_ver[i].ways = information_about_ver[cur_vertex].ways;
						q_for_bfs.push(i);
					}
					else
					{
						if ((information_about_ver[i].visited) && (information_about_ver[i].depth == information_about_ver[cur_vertex].depth+1)) //если уже были в вершине и новый путь тоже минимальный
						{
							information_about_ver[i].ways += information_about_ver[cur_vertex].ways;
						}
						else
						{
							continue;
						}
					}
				}
		}

		return information_about_ver[to].ways;
	}



private:


	int size;
	std::vector<std::list<int>> buffer;

};



int main()
{
	int vert;
	int n;
	std::cin >> vert >> n;
	Graph graph(vert);
	for (int i = 0; i < n; ++i)
	{
		int first_vert;
		int second_vert;
		std::cin >> first_vert >> second_vert;
		graph.AddEdge(first_vert, second_vert);
	}
	int from;
	int to;
	std::cin >> from >> to;
	std::cout<< graph.CountWays(from, to);

	return 0;
}