#include "file.h"
File::File(std::wstring file)
{
	fInput = new std::wifstream; //создание объекта wifstream
	try
	{
		fInput->open(file);
		//открытие файла
		if (!fInput->is_open())
			throw 1;
	}
	catch (int)
	{
		std::cerr << "Не удалось открыть файл!\n";
		exit(0);
	}
}
File::~File()
{
	if (fInput->is_open())
		fInput->close();//закрытие файла
	if (fInput != nullptr)
		delete fInput;
}
void File::readFile(std::wstring& message)//считывание строк сфайла
{
	std::getline(*fInput, message);
	//*fInput >> message;
}