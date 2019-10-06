#include "staticSingleton.hpp"
#include <iostream>
#include <fstream>
using namespace std;

staticSingleton::staticSingleton(){
	pthread_rwlock_init(&m_myLock,NULL);
	open();
}
staticSingleton::~staticSingleton(){
	std::cout<<"Singleton is destructed!" << std::endl;
	close();
} 

// std::string staticSingleton::m_path = "ulumi";

staticSingleton& staticSingleton::getInstance(){
	static staticSingleton inst;
	return inst;
}

const char staticSingleton::m_path[] = "log.txt";

void staticSingleton::open(){
	m_file.open(m_path);
	cout << "File is open." << endl;
}

void staticSingleton::close(){
	m_file.close();
	cout << "File is closed." << endl;
}

void staticSingleton::insert(std::string& text){

	pthread_rwlock_wrlock(&m_myLock);
	
	m_file << text << endl;

	// std::cout << m_path << std::endl;
	pthread_rwlock_unlock(&m_myLock); 
}