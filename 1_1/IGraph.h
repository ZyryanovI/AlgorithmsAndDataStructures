#ifndef _I_Graph_
#define _I_Graph_

#include <vector>

class IGraph {
public:
	virtual ~IGraph() {}

	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
	virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;

};



#endif // _I_Graph_
