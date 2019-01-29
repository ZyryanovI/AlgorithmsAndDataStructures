#pragma once

#include "Graph.h"
#include "MST.h"

// Function object for solution using MST
class MinTourLenMST {
public:
	// Returns estimated length of traveling salesman tour
	double operator()(const Graph & graph);

private:
	// Function for finding Euler path in graph
	void DFS(const Graph & mst, unsigned dot);

	// Stores tour found in DFS
	std::vector<unsigned> tour_;
	// Stores used in DFS
	std::vector<bool> used_;
	// Number of vertices
	unsigned n_;
};