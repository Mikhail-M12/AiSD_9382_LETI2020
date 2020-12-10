#include "decoding.h"
#include <iostream>
std::wstring decoding(BinaryTree * bt, std::wstring message)
//фукцния декодирования сообщение
{
	std::wstring result = L"";
	BinaryTree* root = bt;
	int i = 0;
	while (i <= message.size())
	{
		if (i == message.size())
		{
			result += bt->getRoot();
			break;
		}
		if (message[i] == '0')//если 0, то идем в левое поддерево,если оно есть, если его нет, то добавляем значение корня к результату
		{
		if (bt->getLeft() != nullptr)
		{
		bt = bt->getLeft();
		i++;
		}
		else
		{
		result += bt->getRoot();
		bt = root;
		}
		}
		else//если 1, то идем в правое поддерево, если оно есть,если его нет, то добавляем значение корня к результату
		{
		if (bt->getRight() != nullptr)
		{
		bt = bt->getRight();
		i++;
		}
		else
		{
		result += bt->getRoot();
		bt = root;
		}
		}
	}
	return result;
}