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
void startCoding(std::wstring message, std::wstring& cMessage1, std::wstring& cMessage2, BinaryTree** btHuff, BinaryTree** btSF)
{
	std::vector<BinaryTree*> elements1 = createBTVector(message);
	std::vector<BinaryTree*> elements2;
	for (auto i : elements1)elements2.push_back(new BinaryTree(i->getRoot(), i -> getNum()));
	*btHuff = createBinaryTreeHuff(elements1);
	*btSF = createBinaryTreeSF(new BinaryTree(elements2), elements2);
	printInfo(*btHuff, *btSF);
	std::vector<std::pair<std::wstring, std::wstring>> vecCods1, vecCods2;
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
	std::wcout << L"\nСообщение закодированное методом Хаффмана:" << cMessage1 << std::endl;
	std::wcout << L"Длина сообщения, закодированного методом Хаффмана:"<<cMessage1.length()<<std::endl;
	std::wcout << L"\nСообщение закодированное методом ФаноШеннона:" << cMessage2 << std::endl;
	std::wcout << L"Длина сообщение, закодированного методом ФаноШеннона:" << cMessage2.length() << std::endl;
	for (auto i : elements2)
		delete i;
}


std::wstring frequency(std::wstring message)//вывод частот символов встроке
{
	std::wstring answer = L"";
	std::vector<BinaryTree*> elements = createBTVector(message);
	std::sort(elements.begin(), elements.end(), [](BinaryTree* i, BinaryTree* j)
		{
			if (i->getNum() != j->getNum())
				return i->getNum() > j->getNum();
			else
				return i->getRoot() < j->getRoot();
		}
	);
	std::wcout << L"Частоты символов в строке: \n";
	for (auto i : elements)
	{
		answer += i->getRoot() + L"(" + std::to_wstring(i->getNum()) + L") ";
		std::wcout << i->getRoot() << L"(" << i->getNum() << L") ";
	}
	std::wcout << L"\n";
	return answer;
}


std::wstring randomString()
{
	std::wstring str = L"";
	int x;
	int len = 15;
	char a[45] =
	{
	'q','w','e','r','t','y','u','i','o','p','[',']','a','s','d',
	'f','g','h','j','k','l','z','x','c','v','b','n','m','!','@',
	'#','$','%','&','1','2','3','4','5','6','7','8','9','0','?'
	};
	for (int i = 0; i < len; i++)
	{
		x = rand() % 45;
		str += a[x];
	}
	return str;
}

int wstrcmp(const std::wstring strl, const std::wstring strr) {
	std::wstring str1 = strl;
	std::wstring str2 = strr;
	for (int i = 0; i < str1.length(); i++) {
		if (str1[i] == ' ' || str1[i] == '\n' || str1[i] == '\0') {
			str1.erase(i, 1);
			i--;
		}
	}
	for (int i = 0; i < str2.length(); i++) {
		if (str2[i] == ' ' || str2[i] == '\n' || str2[i] == '\0') {
			str2.erase(i, 1);
			i--;
		}
	}
	if (!str1.compare(str2)) {
		std::wcout << L"Ответ правильный!\n";
		return 1;
	}
	else {
		std::wcout << L"Ответ неправильный :с\n";
		return 0;
	}
}

void questions(std::wstring str, std::wstring* answers) {
	int count = 0;
	std::wcout << L"Дана строка:" << str << std::endl;
	std::wcout << L"Задание №1\n";
	std::wcout << L"Найдите количество вхождений каждого символа и запишите в виде <символ>(<количество_вхождений>)\n";
	std::wcout << L"Порядок записи: Сначала записываются символы с большим количеством вхождений, затем, если количество\n";
	std::wcout << L"одинаково, порядок записи будет такой: Сначала знаки, затем цифры (в порядке возрастания), затем\n";
	std::wcout << L"буквы (сначала заглавные, затем строчные, по алфавиту)\n";
	std::wstring answ;
	std::getline(std::wcin, answ);
	count += wstrcmp(answ, answers[0]);
	std::wcout << L"\n\n\nЗадание №2\n";
	std::wcout << L"Найдите коды символов при кодировании методом Хаффмана и запишите их.\n";
	std::wcout << L"(символы записываются в том же порядке, что и в задании №1)\n";
	std::getline(std::wcin, answ);
	count += wstrcmp(answ, answers[1]);
	std::wcout << L"\n\n\nЗадание №3\n";
	std::wcout << L"Найдите коды символов при кодировании методом Фанно-Шеннона и запишите их.\n";
	std::wcout << L"(символы записываются в том же порядке, что и в задании №1)\n";
	std::getline(std::wcin, answ);
	count += wstrcmp(answ, answers[2]);
	std::wcout << L"\n\n\nЗадание №4\n";
	std::wcout << L"Запишите строку " << str << L" , закодированную методом Хаффмана\n";
	std::getline(std::wcin, answ);
	count += wstrcmp(answ, answers[3]);
	std::wcout << L"\n\n\nЗадание №5\n";
	std::wcout << L"Запишите строку " << str << L" , закодированную методом Фанно-Шеннона\n";
	std::getline(std::wcin, answ);
	count += wstrcmp(answ, answers[4]);
	std::wcout << L"\n\n\nВаш результат: " << count << L"/5";
}


int main()
{
	system("chcp 1251");
	std::locale system("");//для кириллицы
	std::locale::global(system);//для кириллицы
	std::wcout << L"С чем вы хотите работать (f - file, c - console, r - random string, остальное - quit)" << '\n';
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
	case 'r':
		message = randomString();
		std::wcin.ignore();
		break;
	default:
		return 0;
	}
	if (message.length() == 0)
		return 0;
	std::wcout << L"Входная строка : " << message << '\n' << '\n';
	std::wstring answer;
	answer = frequency(message);
	answer += L'\n';
	std::wstring codeHuff, codeSF;
	BinaryTree* btHuff, * btSF;
	startCoding(message, codeHuff, codeSF, &btHuff, &btSF);
	std::wcout << L"\nСообщение, декодированное методом Хаффмана:"<<decoding(btHuff,codeHuff)<<std::endl;
	std::wcout << L"\nСообщение, декодированное методом ФаноШеннона:"<<decoding(btSF,codeSF)<<std::endl;
	std::system("cls");
	std::wofstream file("answers.txt");
	codeHuff += L'\n';
	codeSF += L'\n';
	file << answer << btHuff->getCods() << btSF->getCods() << codeHuff << codeSF;
	file.close();
	std::wstring answers[5];
	answers[0] = answer;
	answers[1] = btHuff->getCods();
	answers[2] = btSF->getCods();
	answers[3] = codeHuff;
	answers[4] = codeSF;
	questions(message, answers);
	destroy(btHuff);
	destroy(btSF);
	return 0;
}
