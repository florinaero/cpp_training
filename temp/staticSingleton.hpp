#include <string>
#include <pthread.h>
#include <fstream>

#ifndef STATICSINGLETON_H
#define STATICSINGLETON_H

class staticSingleton{

private:
	staticSingleton();
	~staticSingleton();
	static const char m_path[];
	pthread_rwlock_t m_myLock;
	std::ofstream m_file; 

public:
	static staticSingleton& getInstance();
	void insert(std::string&);
	void open();
	void close();
};

#endif