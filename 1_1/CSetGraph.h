#include "IGraph.h"
#include <unordered_set>

class CSetGraph : public IGraph {
public:
	CSetGraph(int vertice);
	CSetGraph(const IGraph* igraph);
	~CSetGraph();

	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;



private:
	int size;

	std::vector<std::unordered_set<int> > in;
	std::vector<std::unordered_set<int> > out;



};