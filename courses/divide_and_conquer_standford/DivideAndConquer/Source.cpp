#include "w2_countInversions.hpp"
#include "measTime.h"

int main() {
	std::vector<int> testArr = { 1,3,5,2,4,6,0,-1,-2,-3};
	//std::vector<int> testArr = { 1,3,5,2,4,6};
	//testArr = {3,1,-1,-2};
	CountInversions probl;

	{
		MeasTime timer;
		probl.print("\n__________________Count Inversions Brute Force__________________");
		probl.bruteForce(testArr);

		probl.print("\n__________________Count Inversions__________________");
		probl.countInversion(testArr);
	}
	return 1;
}