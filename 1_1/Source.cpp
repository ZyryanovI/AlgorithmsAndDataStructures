#include <vector>
#include "IGraph.h"
#include <ctime>
#include "CArcGraph.h"
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include <iostream>


int main()
{
	srand(time(0));

	int n = rand()%100;

	CArcGraph cagraph(n);
	CListGraph clgraph(n);
	CMatrixGraph cmgraph(n);
	CSetGraph csgraph(n);


	CArcGraph new_cagraph(&clgraph);
	CListGraph new_clgraph(&cmgraph);
	CMatrixGraph new_cmgraph(&csgraph);
	CSetGraph new_csgraph(&cagraph);

	std::cout << "sizes of graphs: " << std::endl;
	std::cout << new_cagraph.VerticesCount() << "|" << new_clgraph.VerticesCount() << "|" << new_cmgraph.VerticesCount() << "|" << new_csgraph.VerticesCount() << std::endl;

	for (int i = 0; i < n; ++i)
	{
		int from = rand() % n;
		int to = rand() % n;
		new_cagraph.AddEdge(from, to);
		new_clgraph.AddEdge(from, to);
		new_cmgraph.AddEdge(from, to);
		new_csgraph.AddEdge(from, to);
	}

	std::cout << "For example: " << std::endl;
	int vertex = rand() % n;
	std::vector<int> for_result;
	std::cout << "Next: " << std::endl;
	new_cagraph.GetNextVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_clgraph.GetNextVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_cmgraph.GetNextVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_csgraph.GetNextVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;
	/////////////////////////////////////////////////
	std::cout << "Prev: " << std::endl;

	new_cagraph.GetPrevVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_clgraph.GetPrevVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_cmgraph.GetPrevVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	new_csgraph.GetPrevVertices(vertex, for_result);
	for (int i = 0; i < for_result.size(); ++i)
	{
		std::cout << for_result[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
