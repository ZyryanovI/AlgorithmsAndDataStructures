#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>
#include "Graph.h"


typedef std::pair<int, int> dot;

// graph is connected graph where vertices are dots with integral coordinates
// generated with Gaussian distribution (dispersion 100, expected value (0,0))
// and edges are distances between this dots
void generateDots(unsigned seed, Graph & graph);
