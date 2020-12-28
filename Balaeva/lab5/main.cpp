#include <bits/stdc++.h>

using namespace std;
static int op_count = 0;
static int rot_count = 0;
class Node {
protected:
    int value;
    int height;
    Node *lt;
    Node *rt;
    Node *rotate_right();
    Node *rotate_left();

public:
    Node(int k) : value(k), lt(nullptr), rt(nullptr), height(1) {}
    int get_height();
    int diff_height();
    void update_height();
    Node *balance();
    Node *get_right();
    Node *get_left();
    void set_left(Node *node);
    void set_right(Node *node);
    void set_value(int value);
    int get_value();
};

int Node::get_height() {
    return this ? this->height : 0;
}

int Node::diff_height() {
    return this->rt->get_height() - this->lt->get_height();
}

void Node::update_height() {
    int hl = this->lt->get_height();
    int hr = this->rt->get_height();
    this->height = max(hl, hr) + 1;
}

Node *Node::rotate_right() {
    Node *new_root = this->lt;
    this->lt = new_root->rt;
    new_root->rt = this;
    this->update_height();
    new_root->update_height();
    return new_root;
}

Node *Node::rotate_left() {
    Node *new_root = this->rt;
    this->rt = new_root->lt;
    new_root->lt = this;
    this->update_height();
    new_root->update_height();
    return new_root;
}

Node *Node::balance() {
    rot_count++;
    this->update_height();
    int diff = this->diff_height();
    if (diff == 2) {
        if (this->rt->diff_height() < 0) this->rt = this->rt->rotate_right();
        return this->rotate_left();
    } else if (diff == -2) {
        if (this->lt->diff_height() > 0) this->lt = this->lt->rotate_left();
        return this->rotate_right();
    }
    return this;
}

Node *Node::get_right() {
    return this ? this->rt : nullptr;
}

Node *Node::get_left() {
    return this ? this->lt : nullptr;
}

int Node::get_value() {
    return this ? this->value : 0;
}

void Node::set_left(Node *node) {
    if (this)
        this->lt = node;
}

void Node::set_right(Node *node) {
    if (this)
        this->rt = node;
}

void Node::set_value(int value) {
    if (this)
        this->value = value;
}

class AVL_tree {
public:
    Node *root;
    AVL_tree() : root(nullptr) {};
    AVL_tree(int k);
    void print_tree(Node *node, int level);
    Node *insert_node(Node *node, int value);
    Node *find_min(Node *node);
    Node *remove_min(Node *node);
    Node *remove_node(Node *node, int value);
    Node *lets_insert_node(Node *root, int value);
    Node *lets_remove_node(Node *root, int value);
};

AVL_tree::AVL_tree(int k) {
    cout << "[Created avl tree| root:" << k << "]\n\n";
    this->root = new Node(k);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
    this->print_tree(this->root, 0);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
}

void AVL_tree::print_tree(Node *node, int level) {
    if (node) {
        print_tree(node->get_right(), level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << node->get_value() << endl;
        print_tree(node->get_left(), level + 1);
    }
}

Node *AVL_tree::insert_node(Node *node, int value) {
    op_count++;
    if (node == nullptr) return new Node(value);
    if (value < node->get_value()) {
        node->set_left(insert_node(node->get_left(), value));
    } else if (value > node->get_value()) {
        node->set_right(insert_node(node->get_right(), value));
    }
    return node->balance();
}

Node *AVL_tree::remove_node(Node *node, int value) {
    op_count++;
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->get_value()) {
        node->set_left(remove_min(node->get_left()));
    } else if (value > node->get_value()) {
        node->set_right(remove_min(node->get_right()));
    } else {
        Node *rt = node->get_right();
        Node *lt = node->get_left();
        delete node;
        if (!rt) return lt;
        Node *min = find_min(rt);
        min->set_right(remove_min(rt));
        min->set_left(lt);
        return min->balance();
    }
    return node->balance();
}

Node *AVL_tree::find_min(Node *node) {
    return node->get_left() ? find_min(node->get_left()) : node;
}

Node *AVL_tree::remove_min(Node *node) {
    op_count++;
    if (node->get_left() == nullptr) {
        return node->get_right();
    }
    node->set_left(remove_min(node->get_left()));
    return node->balance();
}

Node *AVL_tree::lets_insert_node(Node *root, int value) {
    cout << "[Insert element:" << value << "]\n\n";
    root = this->insert_node(root, value);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
    this->print_tree(root, 0);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
    return root;
}

Node *AVL_tree::lets_remove_node(Node *root, int value) {
    cout << "[Remove element:" << value << "]\n\n";
    root = this->remove_node(root, value);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
    this->print_tree(root, 0);
    cout << "-!-!-!-!-!-!-!-!-!-!-!-!-" << endl;
    return root;
}

void print_menu() {
    cout << "1.Insert element\n"
            "2.Remove element\n"
            "3.Exit\n\n";
}

AVL_tree *process_user_input(AVL_tree *tree) {
    int f, user_value;
    print_menu();
    cin >> f;
    switch (f) {
        case 1:
            cout << "Enter element: \n";
            cin >> user_value;
            if (tree) {
                tree->root = tree->lets_insert_node(tree->root, user_value);
            } else {
                tree = new AVL_tree(user_value);
            }
            break;
        case 2:
            if (tree) {
                cout << "Enter element: \n";
                cin >> user_value;
                tree->root = tree->lets_remove_node(tree->root, user_value);
            } else cout << "Tree is empty! \n";
            break;
        case 3:
            exit(0);
    }
    return tree;
}

int main() {
    AVL_tree *tree = new AVL_tree();
    while (true) {
        tree = process_user_input(tree);
    }
    return 0;
}