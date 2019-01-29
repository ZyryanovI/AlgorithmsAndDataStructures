#include "IGraph.h"
#include <list>



class CListGraph: public IGraph {
public:

	CListGraph(int verticeNumber);
	CListGraph(const IGraph* igraph);
	~CListGraph();

	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:

	int size;
	std::vector<std::list<int>> in; //есть €чейки дл€ каждой вершины - список тех, которые вход€т
	std::vector<std::list<int>> out; //есть €чейки дл€ каждой вершины - список тех, которые выход€т

};






