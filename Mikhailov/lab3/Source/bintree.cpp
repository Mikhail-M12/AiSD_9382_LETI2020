#include "bintree.h"
#include "api.h"

BinTree::BinTree(){
    Head = new Node;
    Head->data = "";
    Current = Head;
}

// Node* BinTree::createTree(QStringList tokens){
Node* BinTree::createTree(std::vector<std::string> tokens){
    std::cout<<"-_-_-_-_-Next step-_-_-_-_-\n";
    Node* finalNode = new Node;
    if(tokens.size()==2) return finalNode;
    int i =1;
    std::string ltree = "";
    std::string rtree = "";

    finalNode->data = tokens[i++];
    int index_i = i;    /* Индекс открывающей скобки левого поддерева */
    if(tokens[i] == "("){
        auto openBrackets = 1;
        auto closeBrackets = 0;

        while (openBrackets != closeBrackets) {
            i++;
            if (tokens[i] == "("){
                openBrackets++;
            }
            else if (tokens[i] == ")"){
                closeBrackets++;
            }

        }

        for (;index_i<=i; index_i++){
            ltree.append(tokens[index_i]);
        }
        std::cout<<"Открытые скобки: "<<openBrackets<<'\n'
                 <<"Закрытые скобки: "<<closeBrackets<<'\n';
        std::cout<<"Вниз (лево): "<<tokens[index_i]<<'\n';
        finalNode->left = createTree(mySplit(ltree));

        i++;

        if (tokens[i] == ")"){      /* Если правого поддерева нет (достигнут конец строки после структуры левого поддерева*/
            return finalNode;
        }

        int index_j = i;    /* Индекс открывающей скобки левого поддерева */
        if(tokens[i] == "("){
            auto openBrackets = 1;
            auto closeBrackets = 0;

            while (openBrackets != closeBrackets) {
                i++;
                if (tokens[i] == "("){
                    openBrackets++;
                }
                else if (tokens[i] == ")"){
                    closeBrackets++;
                }


            }

            for (;index_j<=i; index_j++){
                rtree.append(tokens[index_j]);
            }
            std::cout<<"Открытые скобки: "<<openBrackets<<'\n'
                     <<"Закрытые скобки: "<<closeBrackets<<'\n';

            std::cout<<"Вниз (право): "<<tokens[index_j]<<'\n';
            finalNode->right = createTree(mySplit(rtree));
        }


    }
    std::cout<<"Вверх \n";
    return finalNode;
}
int BinTree::max_depth(Node *hd){
    std::cout<<"-_-_-_-_-Уровень ниже-_-_-_-_-\n";
    if((hd == NULL) || (hd->data == "^")) {
        std::cout<<"Вверх, глубина: 0\n";
        return 0;
    }
    else{
        std::cout<<"Вниз (лево)\n";
        int lDepth = max_depth(hd->left);
        std::cout<<"Вниз (право)\n";
        int rDepth = max_depth(hd->right);
        std::cout<<"Глубина левого:"<<lDepth<<"\n"
                 <<"Глубина правого:"<<rDepth<<"\n";
        if (lDepth > rDepth) {
            std::cout<<"Вверх, глубина: "<<lDepth+1<<"\n";
            return(lDepth + 1);
        }
        else {
            std::cout<<"Вверх, глубина: "<<rDepth+1<<"\n";
            return(rDepth + 1);
        }
    }

}
int BinTree::getFullWeight(Node *hd, int now){
    if (hd==nullptr){
        std::cout<<"Вверх: 0\n";
        return 0;
    }
    else {
        std::cout<<"Вниз (лево)\n";
        int l =getFullWeight(hd->left,now + 1);
        std::cout<<"Вниз (право)\n";
        int r =getFullWeight(hd->right,now + 1);
        now +=l+r ;


        std::cout<<"Вверх: "<<now<<"\tБыло: "<<now-l-r<<"\tЛево: "<<l<<"\tПраво: "<<r<<"\n";
        return now;

    }
}