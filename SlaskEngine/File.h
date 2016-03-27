#pragma once
#include <iostream>

class File
{
private:

	std::string crypt(std::string str);
	int key(bool reset);

public:
	File();
	~File();

	
	bool save(bool encrypted);
	bool load(bool decrypted);
	
	
};

