#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include <iomanip>

typedef std::pair<unsigned, double> pair_ud;
typedef std::pair<double, unsigned> pair_du;

class Graph {
public:
	Graph(unsigned verticesNumber);

	void addEdge(unsigned from, unsigned to, double weight);

	// Vertices - vector of pairs <vertex, weight>
	void getRelated(unsigned vertex, std::vector<pair_ud> &vertices) const;

	unsigned getSize() const;

	double getWeight(unsigned from, unsigned to) const;

	void print();

private:
	unsigned size_;
	std::vector<std::vector<double>> matrix_;
};