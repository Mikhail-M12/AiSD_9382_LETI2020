#include "api.h"
#include<string>

std::string delSpace (std::string rowInput){
    std::string out="";
    for (auto i = 0;i < rowInput.length();i++){
        if (rowInput[i]!=' ' && rowInput[i]!='\n' && rowInput[i]!='\t' )
            out.push_back(rowInput[i]);
    }
    return out;
}

std::vector<std::string> mySplit(std::string rowInput){
    std::string st = delSpace(rowInput);
    auto i = 0;
    std::vector<std::string> out;
    std::string tmp="";
    for(;i<st.length();i++){
        if (st[i] == ')' || st[i] == '(') out.push_back(std::string(1,st[i]));
        else {
            for (; st[i]!=')' && st[i]!='(' ;i++){
                tmp.push_back(st[i]);
            }
            out.push_back(tmp);
            out.push_back(std::string(1,st[i]));
            std::cout<<"tmp: "<<tmp<<'\n';
            tmp.clear();
        }
    }
    for (int i = 0; i < out.size(); i++) {
        std::cout << out.at(i) << ' ';
    }
    std::cout<<std::endl;
    return out;
}


void inputF(){
    std::string data ;
    getline(std::cin, data);
    std::string input = delSpace(data);
    if (input == "") {
        std::cout<<"Error!\n Введите дерево\n";
        return;
    }
    else{
        if (input[0] != '(' || input[input.size() - 1] != ')'){
            std::cout<<"Error!\n Дерево введенно некорректно\n";
            return;
        }
        else{
            BinTree* BT = new  BinTree();
            BT->Head = BT->createTree(mySplit(input));
            std::cout<<"---------------------------------------------------------\n";
            std::cout<<"Глубина дерева: "<<BT->max_depth(BT->Head) - 1<<std::endl;
            std::cout<<"---------------------------------------------------------\n";
            std::cout<<"Внутренний вес: "<<BT->getFullWeight(BT->Head)<<std::endl;
            std::cout<<"---------------------------------------------------------\n";
//            example (6 (5 (4) (9))(5))
        }
    }
}