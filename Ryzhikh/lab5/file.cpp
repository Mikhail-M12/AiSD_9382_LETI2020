#include "file.h"
File::File(std::wstring file)
{
	fInput = new std::wifstream; //�������� ������� wifstream
	try
	{
		fInput->open(file);
		//�������� �����
		if (!fInput->is_open())
			throw 1;
	}
	catch (int)
	{
		std::cerr << "�� ������� ������� ����!\n";
		exit(0);
	}
}
File::~File()
{
	if (fInput->is_open())
		fInput->close();//�������� �����
	if (fInput != nullptr)
		delete fInput;
}
void File::readFile(std::wstring& message)//���������� ����� ������
{
	std::getline(*fInput, message);
	//*fInput >> message;
}