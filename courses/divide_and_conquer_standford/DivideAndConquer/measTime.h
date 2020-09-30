#pragma once
#include <chrono>
#include <time.h>
#include <iostream>

class MeasTime {
private:
	std::chrono::time_point<std::chrono::steady_clock> m_start;

public:
	MeasTime() {
		 m_start = std::chrono::steady_clock::now();
	}

	~MeasTime() {
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double,std::milli> total = end - m_start;
		std::cout << "Time elapsed: " << total.count() << "ms  " << total.count()*1000 << "us  "<< total.count()/1000/60 << "min " << std::endl;
	}
};
