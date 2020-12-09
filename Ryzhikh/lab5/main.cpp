#include <iostream>
#include "file.h"
#include "decoding.h"
#include <locale>
#include <Windows.h>

std::vector<BinaryTree*> createBTVector(std::wstring message)//������� ������� ��������
{
	std::vector<BinaryTree*> elements;
	bool metka;
	for (auto i : message)
	{
		metka = true;
		for (int j = 0; j < elements.size(); j++)
		{
			if (i == elements[j]->getRoot()[0])
			{
				elements[j]->setNum(elements[j]->getNum() + 1);
				metka = false;
				break;
			}
		}
		if (metka)
		{
			std::wstring wstr = L"";
			wstr += i;
			elements.push_back(new BinaryTree(wstr, 1));
		}
	}
	std::sort(elements.begin(), elements.end(), [](BinaryTree* i, BinaryTree* j)
		{
			if (i->getNum() != j->getNum())
			{
				return i->getNum() > j->getNum();
			}
			else
			{
				return i->getRoot() < j->getRoot();
			}
		});
	return elements;
}
void printInfo(BinaryTree* btHuff, BinaryTree* btSF)//�������� ���� ��������
{
	std::wcout << L"���� ��������, �������������� ������� ��������:" << std::endl;
	btHuff->printCods();
	std::wcout << std::endl << L"���� ��������, �������������� ������� �����������" << std::endl;
	btSF->printCods();
}
void startCoding(std::wstring message, std::wstring
	& cMessage1, std::wstring& cMessage2, BinaryTree** btHuff, BinaryTree** btSF)
{
	std::vector<BinaryTree*> elements1 = createBTVector(message);
	std::vector<BinaryTree*> elements2;
		for (auto i : elements1)elements2.push_back(new BinaryTree(i->getRoot(), i -> getNum()));
	*btHuff = createBinaryTreeHuff(elements1);
	*btSF = createBinaryTreeSF(new
		BinaryTree(elements2), elements2);
	printInfo(*btHuff, *btSF);
	std::vector<std::pair<std::wstring, std::wstring>>
		vecCods1, vecCods2;
	(*btHuff)->getCods(vecCods1, L"");
	(*btSF)->getCods(vecCods2, L"");
	for (auto i : message)
	{
		for (int j = 0; j < vecCods1.size(); j++)
		{
			if (i == vecCods1[j].first[0])
			{
				cMessage1 += vecCods1[j].second;
			}
			if (i == vecCods2[j].first[0])
			{
				cMessage2 += vecCods2[j].second;
			}
		}
	}
	std::wcout << L"\n��������� �������������� ������� ��������:" << cMessage1
		<< std::endl;
	std::wcout << L"����� ���������, ��������������� ������� ��������:"<<cMessage1.length()<<std::endl;
		std::wcout << L"\n��������� �������������� ������� �����������:" << cMessage2 << std::endl;
	std::wcout << L"����� ���������, ��������������� ������� �����������:" << cMessage2.length() << std::endl;
	for (auto i : elements2)
		delete i;
}
void frequency(std::wstring message)//����� ������ �������� �������
{
	std::vector<BinaryTree*> elements = createBTVector(message);
	std::sort(elements.begin(), elements.end(), [](BinaryTree* i, BinaryTree* j)
		{
			if (i->getNum() != j->getNum())
				return i->getNum() > j->getNum();
			else
				return i->getRoot() < j->getRoot();
		});
	std::wcout << L"������� �������� � ������: \n";
	for (auto i : elements)
	{
		std::wcout << i->getRoot() << L"(" << i->getNum() << L") ";
	}
	std::wcout << L"\n";
}
int main()
{
	//SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	//SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
	system("chcp 1251");
	std::locale system("");//��� ���������
	std::locale::global(system);//��� ���������
	//SetConsoleCP(1251);// ��������� ������� �������� win-cp 1251 � ����� �����
	//SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������
	std::wcout << L"� ��� �� ������ �������� (f - file, c - console, ��������� - quit)" << '\n';
	std::wstring message;
	wchar_t c;
	std::wcin >> c;
	switch (c)
	{
	case 'f':
	{
		std::wcout << L"������� �������� �����" << '\n';
		std::wstring input;
		std::wcin.ignore();
		std::getline(std::wcin, input);
		//std::wcin >> input;
		File file(input);
		file.readFile(message);
		break;
	}
	case 'c':
		std::wcout << L"������� ������" << '\n';
		std::wcin.ignore();
		std::getline(std::wcin, message);
		break;
	default:
		return 0;
	}
	std::wcout << L"������� ������ : " << message << '\n' << '\n';
	frequency(message);
		std::wstring codeHuff, codeSF;
	BinaryTree* btHuff, * btSF;
	startCoding(message, codeHuff, codeSF, &btHuff, &btSF);
	std::wcout << L"\n���������, �������������� ������� ��������:"<<decoding(btHuff,codeHuff)<<std::endl;
		std::wcout << L"\n���������, �������������� ������� �����������:"<<decoding(btSF,codeSF)<<std::endl;
		destroy(btHuff);
	destroy(btSF);
	return 0;
}
