#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "LogHandler.h"
#include "Platform.h"
#ifdef UNIX
 #include <sys/types.h>
 #include <dirent.h>
#endif
#ifdef WINDOWS
 #include <io.h>
#endif

class File //undocced
{
private:

	std::string crypt(std::string str);
	int key(bool reset);

	std::string data;
	
	bool saveToFile(std::string file, std::string str);

	std::vector<std::string> entry;
	
	#ifdef WINDOWS
	_finddata32_t data32;
	#endif
	
	std::string emptySave;

public:
	File();
	~File();
	
	inline unsigned int entries()
	{
		return entry.size();
	}

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

	void searchFile(std::vector<std::string>*list, const char* path, const char* type);

	void checkSaves(std::vector<std::string>*list, int amountSaves, const char* path, const char* savename, const char* fileType);
	void createSaves(std::string fileName, std::string fileEnd);

	//void newSave(int sFile, const char* path, const char* savename, const char* fileType);
	//void copySave(int sFile, int cToFile, const char* path, const char* savename, const char* fileType, const char* pName);
	void deleteSave(int sFile, const char* path, const char* savename, const char* fileType);
};

