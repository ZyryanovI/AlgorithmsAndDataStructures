#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>

class RMQ {
public:
	RMQ(std::vector<int> &vect)
	{
		sequence = vect;
		size = vect.size();
		table.assign(ceil(log2(size)), std::vector<std::pair<int, int>>(size, std::pair<int, int>(0, 0)));

		// Pre-counting binary logarithms for every index in sequence
		for (int i = 0; i<size + 1; ++i)
		{
			logs_2.push_back(ceil(log2(i)));
		}

		// Initializing 1st row of table with sequence elements
		for (int i = 0; i<size; ++i)
		{
			table[0][i].first = sequence[i];
			table[0][i].second = sequence[i];
		}

		// Initializing other rows of table with first two least elements of segment
		for (int i = 1; i < table.size(); ++i)
		{
			for (int j = 0; j < (size - pow(2, i) + 1); ++j)
			{
				std::pair<int, int> cur_pair = Find_Min_Pair(table[i - 1][j], table[i - 1][j + pow(2, i - 1)]);
				table[i][j].first = cur_pair.first;
				table[i][j].second = cur_pair.second;
			}
		}

	}

	std::pair<int, int> Find_Min_Pair(std::pair<int, int> first_pair, std::pair<int, int> second_pair)
	{
		std::pair<int, int> anser;
		std::vector<int> vect;
		vect.push_back(first_pair.first);
		vect.push_back(first_pair.second);
		vect.push_back(second_pair.first);
		vect.push_back(second_pair.second);

		std::sort(vect.begin(), vect.end());

		anser.first = vect[0];

		for (int i = 1; i<vect.size(); ++i)
		{
			if (vect[i] == vect[0])
			{
				continue;
			}
			else
			{
				anser.second = vect[i];
				break;
			}
		}

		return anser;
	}

	int Find_Second_Stat(int from, int to)
	{
		int k = logs_2[to - from + 1] - 1;

		std::pair<int, int> res_pair = Find_Min_Pair(table[k][from], table[k][to - pow(2, k) + 1]);

		return res_pair.second;

	}

private:
	std::vector<int> sequence;
	int size;

	std::vector<int> logs_2;
	std::vector<std::vector<std::pair<int, int> > > table;

};

int main()
{
	int n;
	int m;
	std::cin >> n >> m;

	std::vector<int> vect(n);

	for (int i = 0; i < n; ++i)
	{
		std::cin >> vect[i];
	}

	RMQ rmq(vect);

	std::vector<std::pair<int, int> > vect_2(m);

	for (int i = 0; i<m; ++i)
	{
		std::cin>>vect_2[i].first>>vect_2[i].second;
	}

	for (int i = 0; i<m; ++i)
	{
		std::cout << rmq.Find_Second_Stat(vect_2[i].first - 1, vect_2[i].second - 1) << std::endl;
	}

	return 0;
}