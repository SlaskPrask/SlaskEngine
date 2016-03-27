#include "FileHandler.h"



FileHandler* FileHandler::instance()
{
	static FileHandler filehandler;
	return &filehandler;
}

//remove this thign because it's just testing Kappa
//and should probably make this not a singleton
#include <iostream>
#include <string>
void FileHandler::init()
{
	std::string s="Slask made this thing and i don't know how it works Kappa.";
	std::cout << "Original:  " << s << '\n';
	std::string enc = crypt(s);
	std::cout << "Encrypted: " << enc << '\n';
	std::string dec = crypt(enc);
	std::cout << "Decrypted: " << dec << '\n';
}

std::string FileHandler::crypt(std::string str)
{
	std::string crypted = "";

	key(true);
	for (int temp = 0; temp < str.size(); temp++)
	{
		crypted += str[temp] ^ (int(key(false)) + temp) % 255;
	}

	return crypted;
}


int FileHandler::key(bool reset)
{
	{
		static int id = 0;
		if (reset)
		{
			id = 0;
			return 0;
		}
		else
			id = (id >= 7 ? 0 : id + 1);
		switch (id)
		{
		default:
		case 0:
			return (int)'s';
		case 1:
			return (int)'l';
		case 2:
			return (int)'a';
		case 3:
			return (int)'s';
		case 4:
			return (int)'k';
		case 5:
			return (int)'z';
		case 6:
			return (int)'a';
		case 7:
			return (int)'s';
		}
		return 0;
	}
}

bool FileHandler::save(bool encrypted)
{
	return encrypted;
}

bool FileHandler::load(bool decrypted)
{
	return decrypted;
}

FileHandler::~FileHandler()
{
}
