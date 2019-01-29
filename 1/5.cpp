#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <iomanip>
#include <list>

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

	~Graph()
	{}

	void AddEdge(int from, int to)
	{
		for (int i : out[from])
		{
			if (i == to)
			{
				return;
			}
		}

		in[to].push_back(from);
		out[from].push_back(to);
		out[to].push_front(from);
		in[from].push_front(to);
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

	bool is_way_exist(int from, int to)
	{
		std::queue<int> q_for_bfs;
		q_for_bfs.push(from);
		std::vector<int> used(size, false);
		used[from] = true;
		while (!q_for_bfs.empty())
		{
			int cur_vertex = q_for_bfs.front();
			q_for_bfs.pop();
			std::vector<int> children;
			GetNextVertices(cur_vertex, children);
			for (int i : children)
			{
				if (!used[i])
				{
					used[i] = true;
					q_for_bfs.push(i);
				}
			}
		}
		return used[to];
	}

private:
	int size;
	std::vector<std::list<int> > in;
	std::vector<std::list<int> > out;
};


double Find_Radius(int left_border, int right_border, int radius, std::vector<std::pair<int, int> > &vect)
{
	double left = 0;
	double right = right_border - left_border;
	int n = vect.size();


	while (right - left > 5e-5)
	{

		double new_poz = (left + right) / 2;
		Graph graph(n + 2);

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				double abcissa = std::pow(vect[i].first - vect[j].first, 2);
				double ordinate = std::pow(vect[i].second - vect[j].second, 2);
				if (sqrt(abcissa + ordinate) - 2 * radius < new_poz)
				{
					graph.AddEdge(i, j);
				}
			}
		}
		for (int i = 0; i < n; ++i)
		{
			if (vect[i].first - left_border - radius < new_poz)
			{
				graph.AddEdge(i, n);
			}
			if (right_border - vect[i].first - radius < new_poz)
			{
				graph.AddEdge(i, n + 1);
			}
		}

		if (graph.is_way_exist(n, n + 1))
		{
			right = new_poz;
		}
		else {
			left = new_poz;
		}
	}
	
	return left;
}




int main()
{
	int XL;
	int XR;
	std::cin >> XL >> XR;
	int radius;
	std::cin >> radius;
	int n;
	std::cin >> n;
	std::vector<std::pair<int, int> > vect;
	for (int i = 0; i < n; ++i)
	{
		int first_el;
		int second_el;
		std::cin >> first_el >> second_el;
		vect.push_back(std::make_pair(first_el, second_el));
	}

	std::cout <<std::fixed<< std::setprecision(3) <<Find_Radius(XL, XR, radius, vect);

	return 0;
}