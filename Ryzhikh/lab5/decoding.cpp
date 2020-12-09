#include "decoding.h"
#include <iostream>
std::wstring decoding(BinaryTree * bt, std::wstring message)
//������� ������������� ���������
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
		if (message[i] == '0')//���� 0, �� ���� � ����� ���������,���� ��� ����, ���� ��� ���, �� ��������� �������� ����� � ����������
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
		else//���� 1, �� ���� � ������ ���������, ���� ��� ����,���� ��� ���, �� ��������� �������� ����� � ����������
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