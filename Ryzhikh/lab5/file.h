#ifndef FILE_H
#define FILE_H
#include <fstream>
#include <iostream>
#include <vector>
#include "binarytree.h"
#include <regex>
class File
{
public:
	File(std::wstring file);
	~File();
	void readFile(std::wstring& message);
private:
	std::wifstream* fInput = nullptr;
};
#endif // FILE_H