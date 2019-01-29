#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(int vertice)
{
	size = vertice;
	buffer.resize(size);
	for (int i = 0; i < size; ++i)
	{
		buffer[i].resize(size);
	}
}

CMatrixGraph::CMatrixGraph(const IGraph* igraph): size(igraph->VerticesCount())
{
	buffer.resize(size);
	for (int i = 0; i < size; ++i)
	{
		buffer[i].resize(size);
	}
	for (int i = 0; i <size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			buffer[i][j] = false;
		}
	}

	for (int i = 0; i < size; ++i)
	{
		std::vector<int> vect;
		igraph->GetNextVertices(i, vect);

		for (int j=0; j<vect.size(); ++i)
		{
			buffer[i][vect[j]] = true;
		}
	}
}

CMatrixGraph::~CMatrixGraph()
{}

void CMatrixGraph::AddEdge(int from, int to)
{
	if (from < size && to < size) { //////////////
		buffer[from][to] = true;
	}
}

int CMatrixGraph::VerticesCount() const
{
	return size;
}

void CMatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	if (vertex < size) {  ////////////
		for (int j = 0; j < size; ++j)
		{
			if (buffer[vertex][j])
			{
				vertices.push_back(j);
			}
		}
	}
}

void CMatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	if (vertex < size) {  ////////////////
		for (int i = 0; i < size; ++i)
		{
			if (buffer[i][vertex])
			{
				vertices.push_back(i);
			}
		}
	}

}