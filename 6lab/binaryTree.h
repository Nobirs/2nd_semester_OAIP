#pragma once
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;


struct Node {
    int key;
    string data;
    Node* left;
    Node* right;

    Node(int k, const string& d) : key(k), data(d), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertHelper(Node* node, int key, const string& data) {
        if (node == nullptr) {
            return new Node(key, data);
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key, data);
        }
        else if (key > node->key) {
            node->right = insertHelper(node->right, key, data);
        }
        else if (key == node->key)
        {
            node->data = data;
            return node;
        }

        return node;
    }

    void printInOrder(Node* node) {
        if (node != nullptr) {
            printInOrder(node->left);
            cout << "Key: " << node->key << ", Data: " << node->data << endl;
            printInOrder(node->right);
        }
    }

    void printPreOrder(Node* node) {
        if (node != nullptr) {
            cout << "Key: " << node->key << ", Data: " << node->data << endl;
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }

    void printPostOrder(Node* node) {
        if (node != nullptr) {
            printPostOrder(node->left);
            printPostOrder(node->right);
            cout << "Key: " << node->key << ", Data: " << node->data << endl;
        }
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNodeHelper(Node* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteNodeHelper(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNodeHelper(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMinNode(node->right);
            node->key = temp->key;
            node->data = temp->data;
            node->right = deleteNodeHelper(node->right, temp->key);
        }

        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int key, const string& data) {
        root = insertHelper(root, key, data);
    }

    void printInOrder() {
        cout << "In-order traversal:" << endl;
        printInOrder(root);
    }

    void printPreOrder() {
        cout << "Pre-order traversal:" << endl;
        printPreOrder(root);
    }

    void printPostOrder() {
        cout << "Post-order traversal:" << endl;
        printPostOrder(root);
    }

    void remove(int key) {
        root = deleteNodeHelper(root, key);
    }

    Node* findHelper(Node* node, int key) {
        if (node == nullptr || node->key == key) {
            return node;
        }

        if (key < node->key) {
            return findHelper(node->left, key);
        }
        else {
            return findHelper(node->right, key);
        }
    }

    Node* find(int key) {
        return findHelper(root, key);
    }

    vector<Node*> inorderTraversalHelper(Node* node) {
        std::vector<Node*> result;

        if (node != nullptr) {
            std::vector<Node*> leftSubtree = inorderTraversalHelper(node->left);
            result.insert(result.end(), leftSubtree.begin(), leftSubtree.end());

            result.push_back(node);

            std::vector<Node*> rightSubtree = inorderTraversalHelper(node->right);
            result.insert(result.end(), rightSubtree.begin(), rightSubtree.end());
        }

        return result;
    }

    vector<Node*> inorderTraversal() {
        return inorderTraversalHelper(root);
    }

    void clearHelper(Node* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

    void clear() {
        clearHelper(root);
        root = nullptr;
    }


    void removeRightMax()
    {
        if (root->left == nullptr)
        {
            cout << "В левой ветви нет узлов" << endl;
            return;
        }
        Node* node = root->left;
        Node* prev = node;
        while (node->right != nullptr)
        {
            prev = node;
            node = node->right;
        }
        clearHelper(node);
        prev->right = nullptr;
        cout << "Задание  Удалить из левой ветви дерева узел с максимальным значением ключа и все связанные с ним узлы выполнено." << endl;
    }
};


