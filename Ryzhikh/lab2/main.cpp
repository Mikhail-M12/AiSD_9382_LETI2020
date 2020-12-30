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


void drop(std::string& str, int n) {
    if (str.length() >= n) {//���� ������ ������ ��� �����
        str = str.substr(n);//�������� ������ �������
    }
}

short readNum(string& str) {
    string number = "";

    while (isdigit(str[0])) {//���� ����� ��������� � �������
        number += str[0];
        drop(str, 1);// �������� �� ������ ������
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
Side* createNewSide(string& input);
BinKor* createNewBinKor(string& input) {
    BinKor* bin_kor = new BinKor;
    drop(input, 1);// �������� �������� ������
    bin_kor->left = createNewSide(input);
    drop(input, 1);// �������� �������� ������
    bin_kor->right = createNewSide(input);
    drop(input, 1);// �������� �������� ������
    return bin_kor;
}

Side* createNewSide(string& input) {// ������� �������
    Side* side = new Side;
    drop(input, 1);// �������� �������� ������
    side->length = readNum(input);
    drop(input, 1);// �������� �������� ������
    side->isWeight = (input[0] != '(');
    if (side->isWeight) {
        side->data.weight = readNum(input);
    }
    else {
        side->data.bin_kor = createNewBinKor(input);
    }
    drop(input, 1);// �������� �� ������ ������
    return side;
}


void freeBinKor(BinKor* bin_kor) {
    if (bin_kor != nullptr) {// ���� ��������� ��  BinKor
        if (bin_kor->right->isWeight == 0) {// ���� �� ����
            freeBinKor(bin_kor->right->data.bin_kor);// �������� ����������� �������
            delete bin_kor->right;// ����������� �������
        }
        else {
            delete bin_kor->right;// ����������� �������
        }
        if (bin_kor->left->isWeight == 0) {// ���� �� ����
            freeBinKor(bin_kor->left->data.bin_kor);// �������� ����������� �������
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

void printBinKor(BinKor* bin_kor, int n)
{
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << '\t';
    std::cout << "Left side: ";
    if (bin_kor->left->isWeight)
        std::cout << '(' << bin_kor->left->length << ' ' << bin_kor->left->data.weight << ')' << std::endl;
    else
    {
        std::cout << '(' << bin_kor->left->length << " (...))" << std::endl;
        printBinKor(bin_kor->left->data.bin_kor, n+1);
    }
    std::cout << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << '\t';
    std::cout << "Right side: ";
    if (bin_kor->right->isWeight)
        std::cout << '(' << bin_kor->right->length << ' ' << bin_kor->right->data.weight << ')' << std::endl;
    else
    {
        std::cout << '(' << bin_kor->right->length << " (...))" << std::endl;
        printBinKor(bin_kor->right->data.bin_kor, n+1);
    }
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
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
    bin_kor = createNewBinKor(input);
    std::cout << std::endl;
    std::cout << "��������� �������� ������� ����� ������� ��������� ���������, ����� ������\n���� ���� == �������� ���������, �� ��������� (...) � � ������� �������� ���������� ��� ����� � ������ �������\n������ == ������� ������������ ������� ��������� ���������\n";
    printBinKor(bin_kor, 0);
    std::cout << std::endl << "_______________________________________" << "\n\n";
    int res = W(bin_kor, indent);
    std::cout << '\n' << "Weight of all weights: " << res << '\n';
    freeBinKor(bin_kor);// ���������� ������
    return 0;
}
