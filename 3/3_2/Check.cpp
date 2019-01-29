#include "Check.h"

TestResults::TestResults(bool success, time_t time, double ansBF, double ansMST, double error) :
	success(success),
	time(time),
	ansBF(ansBF),
	ansMST(ansMST),
	error(error) {
	
}



TestResults && runTests(const std::vector<unsigned> & seeds, const std::vector<unsigned> & ns, double criteria)
{
	// Number of successful tests
	unsigned s = 0;
	// Number of failed tests
	unsigned f = 0;
	// Total time
	time_t timer = 0;
	// Avg MST answer
	double avgMST = 0;
	// Avg BF answer
	double avgBF = 0;
	// Standard deviation
	double stDeviation = 0;
	// Running test for every seed and number of dots
	for (unsigned seed : seeds) {
		for (unsigned n : ns) {
			TestResults results = runTest(seed, n, criteria);
			if (results.success)
				s++;
			else
				f++;
			timer += results.time;
			avgMST += results.ansMST;
			avgBF += results.ansBF;
			stDeviation += results.error;
		}
	}
	avgMST /= f + s;
	avgBF /= f + s;
	stDeviation = sqrt(stDeviation) / (f + s);
	// Printing summary
	std::cout << std::setw(42) << "============Testing summary============\n= "
		<< std::setw(8) << s << std::setw(32) << " tests passed =\n= "
		<< std::setw(8) << f << std::setw(32) << " tests failed =\n= "
		<< std::setw(8) << s + f << std::setw(32) << " tests total =\n= "
		<< std::setw(8) << timer + 1 << std::setw(32) << " ttl time =\n= "
		<< std::setw(8) << std::fixed << std::setprecision(3)
		<< (float)(timer + 1) / (s + f) << std::setw(32) << " avg time =\n= "
		<< std::setw(8) << avgBF << std::setw(32) << " AVG BF answer =\n= "
		<< std::setw(8) << avgMST << std::setw(32) << " AVG MST answer =\n= "
		<< std::setw(8) << stDeviation << std::setw(32) << "  Standard deviation =\n= "
		<< std::setw(8) << stDeviation / 100 << std::setw(30) << "Normalized st. deviation =\n";

	if (f == 0)
		std::cout << std::setw(40) << "----------Testing  successful----------\n";
	else
		std::cout << std::setw(40) << "------------Testing  failed------------\n";

	return std::move(TestResults(f == 0, timer, avgBF, avgMST, stDeviation));
}



TestResults && runTests(unsigned maxSeed, unsigned maxN, double criteria)
{
	std::vector<unsigned> seeds;
	for (unsigned i = 0; i <= maxSeed; i++)
		seeds.push_back(i);
	std::vector<unsigned> ns;
	for (unsigned i = 2; i <= maxN; i++)
		ns.push_back(i);
	return runTests(seeds, ns, criteria);
}



TestResults && runTests(const std::vector<unsigned> & seeds, unsigned maxN, double criteria)
{
	std::vector<unsigned> ns;
	for (unsigned i = 2; i <= maxN; i++)
		ns.push_back(i);
	return runTests(seeds, ns, criteria);
}



TestResults && runTests(unsigned maxSeed, const std::vector<unsigned> & ns, double criteria)
{
	std::vector<unsigned> seeds;
	for (unsigned i = 0; i <= maxSeed; i++)
		seeds.push_back(i);
	return runTests(seeds, ns, criteria);
}




TestResults && runTest(unsigned seed, unsigned n, double criteria)
{
	// Initializing graph
	Graph graph(n);
	generateDots(seed, graph);

	// Running test
	time_t timer = -time(NULL);
	MinTourLenBF minTourLenBF;
	MinTourLenMST minTourLenMST;
	double bf = minTourLenBF(graph);
	double mst = minTourLenMST(graph);
	timer += time(NULL);

	// Printing test results
	if (1 <= mst / bf && mst / bf <= criteria)
		std::cout << "[SUCCESS]";
	else
		std::cout << "[FAILURE]";
	double err = fabs(mst - bf) / bf * 100;
	std::cout << std::fixed << std::setprecision(2)
		<< " BF Answer: " << bf << " <-> MST Answer: " << mst
		<< "\n[ " << (int)((100 - err >= 0) ? (100 - err) : (0)) << "% ]"
		<< "TIME: " << timer
		<< ", ERR: " << fabs(mst - bf)
		<< " // SEED: " << seed
		<< ", N: " << n << "\n\n";

	return std::move(TestResults(1 <= mst / bf && mst / bf <= criteria, timer, bf, mst, fabs(mst - bf)));
}