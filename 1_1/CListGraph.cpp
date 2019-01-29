#include "CListGraph.h"

CListGraph::CListGraph(int verticeNumber)
{
	size = verticeNumber;
	in.resize(verticeNumber);
	out.resize(verticeNumber);

}

CListGraph::CListGraph(const IGraph* igraph)
{
	size = igraph->VerticesCount();
	in.resize(igraph->VerticesCount());
	out.resize(igraph->VerticesCount());
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

CListGraph::~CListGraph()
{}

void CListGraph::AddEdge(int from, int to)
{
	in[to].push_back(from);
	out[from].push_back(to);
}

int CListGraph::VerticesCount() const
{
	return size;
}

void CListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const //все следующие вершины запихать в данный массив
{
	vertices.clear();
	for (int i : out[vertex])
	{
		vertices.push_back(i);
	}

}

void CListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	for (int i : in[vertex])
	{
		vertices.push_back(i);
	}
}