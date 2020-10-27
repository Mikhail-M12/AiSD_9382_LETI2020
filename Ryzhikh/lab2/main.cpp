#include <iostream>
#include <string>
#include <cctype>
#include <typeinfo>
#include <fstream>
using namespace std;

struct BinKor;

//����� ::= (����� ����(������ | ������))
struct Side {
    int length;// ������ �����
    bool isWeight;// true:���� false:������
    union {
        int weight;//����� �����
        BinKor* bin_kor;//������
    } data;
};

//������ ::= (����� �����)
struct BinKor {
    Side* left;// ����� �����
    Side* right;//������ �����
};

void rightPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//������� ������ ���������� ��������
        std::cout << ("\t");
    }
    std::cout << "right weight weights: " << result;//������� ��������� ��������
    std::cout << '\n' << '\n';
}

void leftPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//������� ������ ���������� ��������
        std::cout << ("\t");
    }
    std::cout << "left weight weights: " << result;//������� ��������� ��������
    std::cout << '\n' << '\n';
}

void rightLeftPrint(int indent, int result) {
    for (int i = 0; i < indent; i++) {//������� ������ ���������� ��������
        std::cout << ("\t");
    }
    std::cout << "right + left weights weight: " << result;;//������� ��������� ��������
    std::cout << '\n' << '\n';
}

unsigned int W(BinKor* bin_kor, int indent) {//������� ��� ������ �����
    unsigned int result = 0;

    if (bin_kor->right) {//���� ���� ������ �����
        if (bin_kor->right->isWeight) {
            rightPrint(indent, bin_kor->right->data.weight);// ������� ���������
            result += bin_kor->right->data.weight;
        }
        if (!bin_kor->right->isWeight)//���� ����
            result += W(bin_kor->right->data.bin_kor, indent + 1);
    }
    if (bin_kor->left) {//���� ���� ����� �����
        if (bin_kor->left->isWeight) {
            leftPrint(indent, bin_kor->left->data.weight);// ������� ���������
            result += bin_kor->left->data.weight;
        }
        if (!bin_kor->left->isWeight)//���� ����
        {
            result += W(bin_kor->left->data.bin_kor, indent + 1);
        }
        rightLeftPrint(indent, result);// ������� ���������
    }
    return result;//���������� ���������
}


void Drop(std::string& str, int n) {
    if (str.length() >= n) {//���� ������ ������ ��� �����
        str = str.substr(n);//�������� ������ �������
    }
}

short ReadNum(string& str) {
    string number = "";

    while (isdigit(str[0])) {//���� ����� ��������� � �������
        number += str[0];
        Drop(str, 1);// �������� �� ������ ������
    }
    try {
        string i;
        i = stoi(number);
    }
    catch (const std::invalid_argument&) {
        std::cout << "Wrong input !" << '\n';
        exit(0);
    }
    return stoi(number);//���������� �����
}


// (Side Side)
Side* CreateNewSide(string& input);
BinKor* CreateNewBinKor(string& input) {
    BinKor* bin_kor = new BinKor;
    Drop(input, 1);// �������� �������� ������
    bin_kor->left = CreateNewSide(input);
    Drop(input, 1);// �������� �������� ������
    bin_kor->right = CreateNewSide(input);
    Drop(input, 1);// �������� �������� ������
    return bin_kor;
}

Side* CreateNewSide(string& input) {// ������� �������
    Side* side = new Side;
    Drop(input, 1);// �������� �������� ������
    side->length = ReadNum(input);
    Drop(input, 1);// �������� �������� ������
    side->isWeight = (input[0] != '(');
    if (side->isWeight) {
        side->data.weight = ReadNum(input);
    }
    else {
        side->data.bin_kor = CreateNewBinKor(input);
    }
    Drop(input, 1);// �������� �� ������ ������
    return side;
}


void FreeBinKor(BinKor* bin_kor) {
    if (bin_kor != nullptr) {// ���� ��������� ��  BinKor
        if (bin_kor->right->isWeight == 0) {// ���� �� ����
            FreeBinKor(bin_kor->right->data.bin_kor);// �������� ����������� �������
            delete bin_kor->right;// ����������� �������
        }
        else {
            delete bin_kor->right;// ����������� �������
        }
        if (bin_kor->left->isWeight == 0) {// ���� �� ����
            FreeBinKor(bin_kor->left->data.bin_kor);// �������� ����������� �������
            delete bin_kor->left;// ����������� �������
        }
        else {
            delete bin_kor->left;// ����������� �������
        }
        delete bin_kor;// ����������� BinKor
    }
    else {
        std::cout << "delete" << '\n';
    }
}

int main(int argc, char** argv) {
    std::string input;
    if (argc == 2)
    {
        std::string file = argv[1];
        std::ifstream fin(file);// �������� ���� ��� ������
        if (fin.is_open())
            getline(fin, input);
        else
        {
            std::cout << "Can`t open file" << std::endl;
            return 0;
        }
        fin.close();
    }
    else
    {
        getline(cin, input);
    }
    int indent = 0;// ������
    if (input.length() == 0) {// ���� ����  ����
        std::cout << "Input is empty" << '\n';
        exit(0);
    }
    std::cout << '\n' << "You entered:" << input << '\n' << '\n';
    BinKor* bin_kor = new BinKor;// ������� ��������� �� BinKor
    bin_kor = CreateNewBinKor(input);
    int res = W(bin_kor, indent);
    std::cout << '\n' << "Weight of all weights: " << res << '\n';
    FreeBinKor(bin_kor);// ���������� ������
    return 0;
}
