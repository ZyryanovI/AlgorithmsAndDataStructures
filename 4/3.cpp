#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>


class LCA {
public:
	LCA(std::vector<std::vector<long long int> > &parents) : tree(parents),
		size(parents.size()), size_of_parents_table(ceil(log2(size))),
		t_in(size), t_out(size), ancestors_(size, std::vector<long long int>(size_of_parents_table + 1)),
		dfs_time(0)
	{
		DFS(0, 0);
	}

	long long int Find_LCA(std::pair<long long int, long long int> query)
	{

		if (Is_Ancestor(query.first, query.second))
		{
			return query.first;
		}
		if (Is_Ancestor(query.second, query.first))
		{
			return query.second;
		}
		for (int i = size_of_parents_table; i >= 0; --i)
		{
			if (!Is_Ancestor(ancestors_[query.first][i], query.second))
			{
				query.first = ancestors_[query.first][i];
			}
		}

		return ancestors_[query.first][0];
	}

private:

	void DFS(long long int node, long long int parent)
	{
		t_in[node] = dfs_time++;
		ancestors_[node][0] = parent;
		for (int i = 1; i <= size_of_parents_table; ++i)
		{
			ancestors_[node][i] = ancestors_[ancestors_[node][i - 1]][i - 1];
		}
		for (int i = 0; i < tree[node].size(); ++i)
		{
			long long int to = tree[node][i];
			if (to != parent)
			{
				DFS(to, node);
			}
		}
		t_out[node] = dfs_time++;
	}

	bool Is_Ancestor(long long int a, long long int b)
	{
		return (t_in[a] <= t_in[b]) && (t_out[b] <= t_out[a]);
	}

	long long int dfs_time;

	long long int size;

	long long int size_of_parents_table;

	std::vector<std::vector<long long int>> tree;
	std::vector<long long int> t_in; // Time of visiting i-th node
	std::vector<long long int> t_out; // Time of leaving i-th node

	std::vector<std::vector<long long int>> ancestors_;  // Sparse table of ancestors

};

class NewQueryGenerator {
public:
	NewQueryGenerator(long long int a_, long long int b_, long long int x_, long long int y_, long long int z_, long long int n_)
	{
		a = a_;
		b = b_;
		x = x_;
		y = y_;
		z = z_;
		n = n_;
	}

	std::pair<long long int, long long int> Generate(long long int res)
	{
		std::pair<long long int, long long int> anser((a + res) % n, b);
		a = (a*x + b*y + z) % n;
		b = (b*x + a*y + z) % n;
		return anser;
	}

private:
	long long int a;
	long long int b;
	long long int x;
	long long int y;
	long long int z;
	long long int n;
};


int main()
{

	long long int n;
	long long int m;
	std::cin >> n >> m;
	std::vector<std::vector<long long int>> parents(n);
	for (int i = 1; i < n; ++i) {
		long long int x;
		std::cin >> x;
		parents[x].push_back(i);

	}

	long long int a1;
	long long int b1;
	std::cin >> a1 >> b1;
	long long int x;
	long long int y;
	long long int z;
	std::cin >> x >> y >> z;

	NewQueryGenerator newquery(a1, b1, x, y, z, n);

	LCA lca(parents);

	long long int anser = 0;

	long long int cur_res = 0;

	for (int i = 0; i < m; ++i)
	{
		cur_res = lca.Find_LCA(newquery.Generate(cur_res));
		anser += cur_res;
	}
	std::cout << anser;

	return 0;
}