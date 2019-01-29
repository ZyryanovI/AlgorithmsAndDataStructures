#pragma once

#include <iomanip>
#include <cmath>
#include <ctime>
#include "Graph.h"
#include "Dots.h"
#include "BruteForce_Way.h"
#include "MST_Way.h"

// Container for test results
struct TestResults {
	TestResults(bool success,
		time_t time,
		double ansBF,
		double ansMST,
		double error);

	// True if test was passed
	bool success;
	// Time of testing in seconds
	time_t time;
	// Brute force answer
	double ansBF;
	// MST answer
	double ansMST;
	// Error
	double error;
};

// Runs test for every seed in seeds and every number of dots in ns
// Criteria is maximal ratio of MST answer to BF answer
TestResults && runTests(const std::vector<unsigned> & seeds,
	const std::vector<unsigned> & ns,
	double criteria);

// Runs test for every seed in [0..maxSeed]
// and every number of dots im n [2..maxN]
// Criteria is maximal permissible ratio of MST answer to BF answer
TestResults && runTests(unsigned maxSeed = 100,
	unsigned maxN = 10,
	double criteria = 2);

TestResults && runTests(const std::vector<unsigned> & seeds,
	unsigned maxN,
	double criteria = 2);

TestResults && runTests(unsigned maxSeed,
	const std::vector<unsigned> & ns,
	double criteria = 2);

// Runs test with specific seed and number of dots (n)
// Criteria is maximal ratio of MST answer to BF answer
TestResults && runTest(unsigned seed, unsigned n, double criteria);
