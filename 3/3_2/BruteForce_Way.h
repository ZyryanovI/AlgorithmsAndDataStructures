#pragma once

#include "Graph.h"

// Function object for Brute Force solution
class MinTourLenBF {
public:
	// Returns length of exact minimal traveling salesman tour
	double operator()(const Graph & graph);

private:
	// Recursive function for getting all possible tours
	void permutations(unsigned depth);

	// Gets length of tour stored in tour
	double getTourLen();

	// Pointer to original graph
	Graph const * graph_;
	// Number of dots
	unsigned n_;
	// Stores tour without 0 vertex
	std::vector<unsigned> tour_;
	// Stores length of min tour
	double minTour_;
};