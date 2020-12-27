#include<iostream>
#include<string>
#include<fstream>

class Node{ // Элемент списка
	public:
		char key;
		Node* next;
		Node* child;
		Node(char key = '\0', Node* next = nullptr, Node* child = nullptr){
			this->key = key;
			this->next = next;
			this->child = child;
		}
};

bool areIdentical(Node* node1, Node* node2){ // Проверяет, являются ли два списка идентичными
	std::cout<<"areIdentical() call for "<<node1->key<<" "<<node2->key<<'\n';
	if (node1->key != node2->key) return false;
	if (node1->child != nullptr && node2->child != nullptr){
		if (node1->child->next != nullptr && node2->child->next != nullptr) return areIdentical(node1->child, node2->child) & areIdentical(node1->child->next, node2->child->next);
		else return areIdentical(node1->child, node2->child);
	}
	return true;
}

void simplifyNode(Node* node){ // Упрощение списка
	std::cout<<"simplifyNode() call for "<<node->key<<'\n';
	if (node->key == '&'){
		if (node->child->key == '0' || node->child->next->key == '0'){
			node->key   = '0';
			node->child = nullptr;
			return;
		}
		if (node->child->key == '1'){
			node->key = node->child->next->key;
			node->child = node->child->next->child;
			return;
		}
		if (node->child->next->key == '1'){
			node->key = node->child->key;
			node->child = node->child->child;
			return;
		}
		if (areIdentical(node->child, node->child->next)){
			node->key = node->child->key;
			node->child = node->child->child;
			return;
		}
		if (node->child->key == '!' && node->child->next->key == '!'){
			node->key = '|';
			node->child->key = node->child->child->key;
			node->child->next->key = node->child->next->child->key;
			node->child->child = node->child->child->child;
			node->child->next->child = node->child->next->child->child;
			return;
		}
		if (node->child->key == '!'){
			if (node->child->next != nullptr && node->child->child != nullptr)
			if (areIdentical(node->child->next, node->child->child)){
				node->key = '0';
				node->child = nullptr;
			}
			return;
		}
		if (node->child->next->key == '!'){
			if (node->child->next->child != nullptr && node->child != nullptr)
			if (areIdentical(node->child->next->child, node->child)){
				node->key = '0';
				node->child = nullptr;
			}
			return;
		}
	}
	if (node->key == '|'){
		if (node->child->key == '1' || node->child->next->key == '1'){
			node->key   = '1';
			node->child = nullptr;
			return;
		}
		if (node->child->key == '0'){
			node->key = node->child->next->key;
			node->child = node->child->next->child;
			return;
		}
		if (node->child->next->key == '0'){
			node->key = node->child->key;
			node->child = node->child->child;
			return;
		}
		if (areIdentical(node->child, node->child->next)){
			node->key = node->child->key;
			node->child = node->child->child;
			return;
		}
		if (node->child->key == '!' && node->child->next->key == '!'){
			node->key = '&';
			node->child->key = node->child->child->key;
			node->child->next->key = node->child->next->child->key;
			node->child->child = node->child->child->child;
			node->child->next->child = node->child->next->child->child;
			return;
		}
		if (node->child->key == '!'){
			if (node->child->next != nullptr && node->child->child != nullptr)
			if (areIdentical(node->child->next, node->child->child)){
				node->key = '1';
				node->child = nullptr;
			}
			return;
		}
		if (node->child->next->key == '!'){
			if (node->child->next->child != nullptr && node->child != nullptr)
			if (areIdentical(node->child->next->child, node->child)){
				node->key = '1';
				node->child = nullptr;
			}
			return;
		}
	}
	if (node->key == '!'){
		if (node->child->key == '0'){
			node->key   = '1';
			node->child = nullptr;
			return;
		}
		if (node->child->key == '1'){
			node->key   = '0';
			node->child = nullptr;
			return;
		}
		if (node->child->key == '!'){
			node->key   = node->child->child->key;
			node->child = node->child->child->child;
			return;
		}
	}
}

void simplifyExpression(Node* head){ // Упрощение всего выражения(обход списка в глубину)
	std::cout<<"simplifyExpression() call for node "<<head->key<<'\n';
	if (head->child != nullptr) {
		simplifyExpression(head->child);
		if (head->child->next != nullptr) simplifyExpression(head->child->next);
	}
	simplifyNode(head);
}

bool isCorrectExpression(std::string expr){ // Проверяет, является ли введённое выражение корректным
	std::cout<<"isCorrectExpression() call\n";
	if (expr.length() < 5) return false;
	int open = 0;
	for (int i = 0; i < expr.length(); i++){
		if (expr[i] >= '2' && expr[i] <= '9') return false;
		if ((expr[i+1] != '&' && expr[i+1] != '|' && expr[i+1] != '!') && expr[i] == '(') return false;
		if (expr[i] == '(') open++;
		if (expr[i] == ')') open--;
	}
	if (open > 0) return false;
	return true;
}

int exprToList(std::string expr, Node* head, int i = 0){ // Преобразует выражение в иерархический список
	while (expr[i] == ' '){
		i++;
	}
	if (expr[i] == '('){
		head->key = expr[++i];
		head->child = new Node();
		i = exprToList(expr, head->child, i + 1);
		if (head->key == '|' || head->key == '&'){
			head->child->next = new Node();
			i = exprToList(expr, head->child->next, i);
		}
	}
	else if (isalpha(expr[i])){
		head->key = expr[i];
		head->child = nullptr;
	}
	else if (isdigit(expr[i])){
		head->key = expr[i];
		head->child = nullptr;
	}
	return i + 1;
}

void printList(Node* head){ // Печатает список на экран
	if (head->key == '&' || head->key == '|' || head->key == '!'){
		std::cout<<"("<<head->key<<" ";
		printList(head->child);
		if (head->child->next != nullptr){
			std::cout<<" ";
			printList(head->child->next);
		}
		std::cout<<")";
	}
	else{
		std::cout<<head->key;
	}
}

void process(std::string expr){ // Обработка введённого выражения
	int c = isCorrectExpression(expr);
	if (!c) {
		std::cout<<"Incorrect expression format.\n";
		return;
	}
	
	Node* head = new Node();
	
	exprToList(expr, head);
	
	std::cout<<"You've inserted the next expression: ";
	printList(head);
	std::cout<<'\n';
	
	simplifyExpression(head);
	std::cout<<"Simplified expression:\n";
	printList(head);
	std::cout<<'\n';
	
	delete head;
}

int func(){
	int a;
	std::string expr;
	
	std::cout<<"Choose input option(0 - file input, 1 - console input):\n";
	std::cin>>a;
	if (a){
		std::cin.ignore();
		std::getline(std::cin, expr);
		process(expr);
		return 0;
	}
	
	std::ifstream f("tests.txt");
	if (!f){
		std::cout<<"Couldn't open file!\n";
		return 1;
	}
	
	while (!f.eof()){
		std::getline(f, expr);
		process(expr);
		std::cout<<"--------------------------------\n";
	}
	return 0;
}

int main(){
	try{
		func();
	}
	catch(...){
		std::cout<<"An unexpected error occurred.\n";
	}
	return 0;
}
