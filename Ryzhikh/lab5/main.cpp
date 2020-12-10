#include <iostream>
#include "file.h"
#include "decoding.h"
#include <locale>
#include <Windows.h>

std::vector<BinaryTree*> createBTVector(std::wstring message)//вернуть вектора деревьев
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
void printInfo(BinaryTree* btHuff, BinaryTree* btSF)//выписать коды символов
{
	std::wcout << L"Коды символов, закодированных методом Хаффмана:" << std::endl;
	btHuff->printCods();
	std::wcout << std::endl << L"Коды символов, закодированных методом ФаноШеннона" << std::endl;
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
	std::wcout << L"\nСообщение закодированное методом Хаффмана:" << cMessage1
		<< std::endl;
	std::wcout << L"Длина сообщения, закодированного методом Хаффмана:"<<cMessage1.length()<<std::endl;
		std::wcout << L"\nСообщение закодированное методом ФаноШеннона:" << cMessage2 << std::endl;
	std::wcout << L"Длина сообщение, закодированного методом ФаноШеннона:" << cMessage2.length() << std::endl;
	for (auto i : elements2)
		delete i;
}
void frequency(std::wstring message)//вывод частот символов встроке
{
	std::vector<BinaryTree*> elements = createBTVector(message);
	std::sort(elements.begin(), elements.end(), [](BinaryTree* i, BinaryTree* j)
		{
			if (i->getNum() != j->getNum())
				return i->getNum() > j->getNum();
			else
				return i->getRoot() < j->getRoot();
		});
	std::wcout << L"Частоты символов в строке: \n";
	for (auto i : elements)
	{
		std::wcout << i->getRoot() << L"(" << i->getNum() << L") ";
	}
	std::wcout << L"\n";
}
int main()
{
	system("chcp 1251");
	std::locale system("");//для кириллицы
	std::locale::global(system);//для кириллицы
	std::wcout << L"С чем вы хотите работать (f - file, c - console, остальное - quit)" << '\n';
	std::wstring message;
	wchar_t c;
	std::wcin >> c;
	switch (c)
	{
	case 'f':
	{
		std::wcout << L"Введите название файла" << '\n';
		std::wstring input;
		std::wcin.ignore();
		std::getline(std::wcin, input);
		File file(input);
		file.readFile(message);
		break;
	}
	case 'c':
		std::wcout << L"Введите строку" << '\n';
		std::wcin.ignore();
		std::getline(std::wcin, message);
		break;
	default:
		return 0;
	}
	if (message.length() == 0)
		return 0;
	std::wcout << L"Входная строка : " << message << '\n' << '\n';
	frequency(message);
		std::wstring codeHuff, codeSF;
	BinaryTree* btHuff, * btSF;
	startCoding(message, codeHuff, codeSF, &btHuff, &btSF);
	std::wcout << L"\nСообщение, декодированное методом Хаффмана:"<<decoding(btHuff,codeHuff)<<std::endl;
		std::wcout << L"\nСообщение, декодированное методом ФаноШеннона:"<<decoding(btSF,codeSF)<<std::endl;
		destroy(btHuff);
	destroy(btSF);
	return 0;
}
