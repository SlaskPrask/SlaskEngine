#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "LogHandler.h"

class File
{
private:

	std::string crypt(std::string str);
	int key(bool reset);

	std::string data;
	
	bool saveToFile(std::string file, std::string str);

	std::vector<std::string> entry;

public:
	File();
	~File();
	
	void save(std::string file, bool encrypted);
	bool load(std::string file, bool encrypted);
	
	void add(std::string str);
	void add(const char* str);
	void add(int val);

	void clearVector();
	void clearData();
	
	void set(int i, int val);
	void set(int i, std::string val);
	
	std::string get(int i);
	int getint(int i);
	
};

