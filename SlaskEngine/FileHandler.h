#pragma once
#include <iostream>

class FileHandler
{
private:

	std::string crypt(std::string str);
	int key(bool reset);

public:
	static FileHandler* instance();
	void init();
	~FileHandler();

	
	bool save(bool encrypted);
	bool load(bool decrypted);
	
	
};

