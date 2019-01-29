#include <iostream>
#include <vector>

bool FindStok(std::vector<std::vector<int>>& vect)
{
	int size = vect.size();
	std::vector<bool> if_can_be_stok(size, true);

	for (int i = 0; i < size; ++i)
	{
		if (!if_can_be_stok[i])
		{
			continue;
		}
		else {
			int j = (i + 1) % size; //чтобы переходить дальше по циклу
			while (i != j)
			{
				if (vect[i][j] == 1)
				{
					if_can_be_stok[i] = false; //т.к. выходит ребро из i в j
					break;
				}
				else {
					if_can_be_stok[j] = false; //т.к. в j не приходит ребро
					++j;
					j %= size;
				}
			}
			if (i == j)
			{
				for (int k = 0; k < size; ++k)
				{
					if ((vect[k][i] == 0) && (k != i))
					{
						if_can_be_stok[i] = false; //не из всех вершин в эту
						break;
					}
					else
					{
						continue;
					}
				}
				if (if_can_be_stok[i] == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}




int main()
{
	int n;
	std::cin >> n;
	std::vector<std::vector<int> > vect(n, std::vector<int>(n, 0));
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cin >> vect[i][j];
		}
	}
	if (FindStok(vect))
	{
		std::cout << "Yes";
	}
	else
	{
		std::cout << "No";
	}


	return 0;
}