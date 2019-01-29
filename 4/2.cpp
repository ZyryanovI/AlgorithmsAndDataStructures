#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <iomanip>


class Tree_Of_Segments {
public:
	Tree_Of_Segments()
	{}

	Tree_Of_Segments(std::vector<int>& vect, int new_capacity)
	{
		capacity = new_capacity;

		size = 1 << (int)ceil(log2(vect.size()));

		buffer.assign(2 * size - 1, std::pair<int, int>(0, 0));

		for (int i = 0; i < vect.size(); ++i)
		{
			buffer[buffer.size() / 2 + i].first = vect[i];
		}

		for (long long int i = buffer.size() / 2 - 1; i >= 0; --i)
		{
			buffer[i].first = std::max(buffer[2 * i + 1].first, buffer[2 * i + 2].first);
		}
	}

	int Get_Max_On_Segment(int node, int left, int right, int a, int b)
	{
		if ((left > right) || (a > b))
		{
			return 0;
		}
		else
		{
			if ((a == left) && (b == right))
			{
				return buffer[node].first + buffer[node].second;
			}
			else
			{
				int middle = (left + right) / 2;
				int left_max = Get_Max_On_Segment(2 * node + 1, left, middle, a, std::min(b, middle));
				int right_max = Get_Max_On_Segment(2 * node + 2, middle + 1, right, std::max(a, middle + 1), b);

				return std::max(left_max, right_max) + buffer[node].second;
			}
		}


	}

	bool Check(int a, int b, int number)
	{
		if (Get_Max_On_Segment(0, 0, size - 1, a, b) + number > capacity)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void IncreaseSegment(int node, int left, int right, int a, int b, int d)
	{
		if ((a > b) || (left > right))
		{
			return;
		}
		else
		{
			if ((a == left) && (b == right))
			{
				buffer[node].second += d;
				return;
			}
			else {

				int middle = (left + right) / 2;

				IncreaseSegment(2 * node + 1, left, middle, a, std::min(b, middle), d);
				IncreaseSegment(2 * node + 2, middle + 1, right, std::max(a, middle + 1), b, d);

				buffer[node].first = std::max(buffer[node * 2 + 1].first + buffer[node * 2 + 1].second, buffer[node * 2 + 2].first + buffer[node * 2 + 2].second);
			}

		}
	}

	void PreIncreaseSegment(int a, int b, int d)
	{
		IncreaseSegment(0, 0, size - 1, a, b, d);
	}



private:
	int size; // Number of tree leafs
	std::vector<std::pair<int, int>> buffer;
	int capacity;
};








int main()
{
	int n = 0;
	std::cin >> n;
	std::vector<int> tickets(n - 1);
	for (int i = 0; i < tickets.size(); ++i)
	{
		std::cin >> tickets[i];
	}

	int capacity;
	std::cin >> capacity;

	Tree_Of_Segments tree(tickets, capacity);

	int m;
	std::cin >> m;
	std::vector<std::vector<int>> vect(m, std::vector<int>(3));
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cin >> vect[i][j];
		}
	}

	for (int i = 0; i < m; ++i)
	{
		if (tree.Check(vect[i][0], vect[i][1] - 1, vect[i][2]))
		{
			std::cout << i << " ";
		}
		else {
			tree.PreIncreaseSegment(vect[i][0], vect[i][1] - 1, vect[i][2]);
			//tree.IncreaseSegment(0, 0, vect.size() - 1, vect[i][0], vect[i][1] - 1, vect[i][2]);
		}
	}


	return 0;
}