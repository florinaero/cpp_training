#include<iostream>
#include <vector>
#include <mutex>
#include <chrono>
#include <thread>
#include <random>
#include <utility>
#include <atomic>

using namespace std;

// mutex myMutex;
typedef unsigned long long ull;

void sumUp(atomic<ull>& sum, const vector<int>& val, ull start, ull end){
	for(int i=start;i<end;i++){
		// lock_guard<mutex> myLock(myMutex);
		sum += val[i];
	}
}

int main(){

	constexpr long long counter = 1000*1000;
	constexpr long long firstBound = counter/4;
	constexpr long long secondBound = counter/2;
	constexpr long long thirdBound = 3*counter/4;

	vector<int> randValues;
	// randValues.reserve(size);

	mt19937 engine;
	uniform_int_distribution<> uniformDist(1,10);
	for(long long i =0;i<counter;i++){
		randValues.push_back(uniformDist(engine));
	}

	atomic<ull> sum(0);
	// ull sum = 0;
	auto start = chrono::system_clock::now();

	thread t1(sumUp, std::ref(sum), std::ref(randValues), 0, firstBound);
	thread t2(sumUp, std::ref(sum), std::ref(randValues), firstBound, secondBound);
	thread t3(sumUp, std::ref(sum), std::ref(randValues), secondBound, thirdBound);
	thread t4(sumUp, std::ref(sum), std::ref(randValues), thirdBound, counter);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	chrono::duration<double> time = chrono::system_clock::now() - start;

	cout << "Time: " << time.count() << "seconds" << endl;
	cout << "Sum = " << sum << endl;
	return 0;
}
