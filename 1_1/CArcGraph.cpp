#include "CArcGraph.h"

CArcGraph::CArcGraph(int verticeNumber): size(verticeNumber)
{}

CArcGraph::CArcGraph(const IGraph* igraph) //доделать
{
	size = igraph->VerticesCount();
	for (int i = 0; i < size; ++i)
	{
		std::vector<int> cur_vect;
		igraph->GetNextVertices(i, cur_vect);
		for (int j = 0; j < cur_vect.size(); ++j)
		{
			MyPair cur_pair(i, cur_vect[j]);
			buffer.push_back(cur_pair);
		}
	}

}

CArcGraph::~CArcGraph()
{}

void CArcGraph::AddEdge(int from, int to)
{
	MyPair cur_pair(from, to);
	buffer.push_back(cur_pair);
}


int CArcGraph::VerticesCount() const
{
	return size;
}

void CArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (buffer[i].from == vertex)
		{
			vertices.push_back(buffer[i].to);
		}
	}

}

void CArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
	vertices.clear();
	for (int i = 0; i < buffer.size(); ++i)
	{
		if (buffer[i].to == vertex)
		{
			vertices.push_back(buffer[i].from);
		}
	}

}