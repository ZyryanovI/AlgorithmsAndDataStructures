#include "IGraph.h"


class CMatrixGraph: public IGraph {
public:
	CMatrixGraph(int vertice);
	CMatrixGraph(const IGraph* igraph);
	~CMatrixGraph();

	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;



private:
	int size;
	std::vector<std::vector<bool> > buffer;


};