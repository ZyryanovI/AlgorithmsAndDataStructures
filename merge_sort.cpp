#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
template<typename T>
void MyMerge(T* vect1, T* vect2, int vect1_size, int vect2_size, T* vect_result)
{
	int i = 0, j = 0;
	while (i<vect1_size && j<vect2_size)
	{
		if (vect1[i] <= vect2[j])
		{
			vect_result[i + j] = vect1[i];
			i++;
		}
		else {
			vect_result[i + j] = vect2[j];
			j++;
		}
	}

	if (i<vect1_size)
	{
		while (i<vect1_size)
		{
			vect_result[i + j] = vect1[i];
			i++;
		}
	}
	if (j<vect2_size)
	{
		while (j<vect2_size)
		{
			vect_result[i + j] = vect2[j];
			j++;
		}
	}
}

template<typename T1>
void MyMergeSort(T1 *vect, int vsize)
{
	if (vsize <= 1)
	{
		return;
	}
	int first_part_size = vsize / 2;
	int second_part_size = vsize - first_part_size;
	MyMergeSort(vect, first_part_size);
	MyMergeSort(vect + first_part_size, second_part_size);
	T1 *new_vector = new T1[vsize];
	MyMerge(vect, vect + first_part_size, first_part_size, second_part_size, new_vector);
	std::memcpy(vect, new_vector, sizeof(T1)*vsize);
	delete[] new_vector;
}

int main()
{
	int n;
	int k;
	std::cin >> n >> k;
	int current_index = 0;
	int* vect_first_part = new int[k+1];
	int* vect_second_part = new int[k+1];
	int* vect_total = new int[2*(k+1)];

	int i = 0;
	for (; i <= k && i<n; i++)
	{
		std::cin >> vect_first_part[i];
	}
	k = std::min(n, k + 1);
	MyMergeSort(vect_first_part, k);


	if (i == n)
	{
		for (int j = 0; j<n; j++)
		{
			std::cout << vect_first_part[j] << " ";
		}
		delete[] vect_first_part;
		delete[] vect_second_part;
		delete[] vect_total;
		return 0;
	}
	for (int j = 0; j<k && i<n; j++, i++)
	{
		std::cin >> vect_second_part[j];
	}
	int s = std::min(k, n - k);

	MyMergeSort(vect_second_part, s);

	MyMerge(vect_first_part, vect_second_part, k, s, vect_total);
	if (i == n)
	{
		for (int j = 0; j<n; j++)
		{
			std::cout << vect_total[j] << " ";
		}
		delete[] vect_first_part;
		delete[] vect_second_part;
		delete[] vect_total;
		return 0;
	}

	int counters = 1;
	for (int i = 2 * k; i<n; )
	{
		counters++;
		for (int j = 0; j<k; j++)
		{
			std::cout << vect_total[j] << " ";
		}
		memcpy(vect_first_part, vect_total + k, sizeof(int)*k);
		for (int g = 0; g<k && i<n; g++, i++)
		{
			std::cin >> vect_second_part[g];
		}
		MyMergeSort(vect_second_part, std::min(k, n - (k*counters)));
		MyMerge(vect_first_part, vect_second_part, k, std::min(k, n - (k*counters)), vect_total);
	}

	for (int j = 0; j<n - k*(counters - 1); j++) {
		std::cout << vect_total[j] << " ";
	}

	delete[] vect_first_part;
	delete[] vect_second_part;
	delete[] vect_total;

	return 0;
}
