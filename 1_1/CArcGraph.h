#include "IGraph.h"



class CArcGraph : public IGraph {
public:

	CArcGraph(int verticeNumber);
	CArcGraph(const IGraph* igraph);
	~CArcGraph();


	virtual void AddEdge(int from, int to) override;

	virtual int VerticesCount() const override;

	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
	int size;
	struct MyPair
	{
		int from;
		int to;
		MyPair(int from_n, int to_n)
		{
			from = from_n;
			to = to_n;
		}
	};
	std::vector<MyPair> buffer;


};