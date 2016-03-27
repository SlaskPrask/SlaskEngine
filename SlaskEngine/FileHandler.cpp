#include "FileHandler.h"



FileHandler* FileHandler::instance()
{
	static FileHandler filehandler;
	return &filehandler;
}

void FileHandler::init()
{

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
