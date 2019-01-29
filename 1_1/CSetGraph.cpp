#include "CSetGraph.h"

CSetGraph::CSetGraph(int vertice)
{
	size = vertice;
	in.resize(vertice);
	out.resize(vertice);
}

CSetGraph::CSetGraph(const IGraph* igraph)
{
	size = igraph->VerticesCount();
	in.resize(size);
	out.resize(size);
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> vect;
		igraph->GetNextVertices(i, vect);
		for (int j = 0; j < vect.size(); ++j)
		{
			AddEdge(i, j);
		}
	}
}

CSetGraph::~CSetGraph()
{}

void CSetGraph::AddEdge(int from, int to)
{
	in[to].insert(from);
	out[from].insert(to);
}

int CSetGraph::VerticesCount() const
{
	return size;
}

void CSetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	for (int i : out[vertex])
	{
		vertices.push_back(i);
	}
}

void CSetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	for (int i : in[vertex])
	{
		vertices.push_back(i);
	}
}