#include <iostream>
// #include <string>
class Logging{
private:
	bool isLogRunning_;
public:
	void start(){
		isLogRunning_ = true;
	}

	void end(){
		isLogRunning_ = false;
	}

	template<class T>
	static void print(const T &text, bool isActive=true){	
		if(isActive){
			std::cout << text << std::endl;
		}
	}
};