#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

using std::cin;
using std::cout;
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

        return node;
    }

    void printInOrderHelper(Node* node) {
        if (node != nullptr) {
            printInOrderHelper(node->left);
            cout << "Key: " << node->key << ", Data: " << node->data << endl;
            printInOrderHelper(node->right);
        }
    }

    void printPreOrderHelper(Node* node) {
        if (node != nullptr) {
            cout << "Key: " << node->key << ", Data: " << node->data << endl;
            printPreOrderHelper(node->left);
            printPreOrderHelper(node->right);
        }
    }

    void printPostOrderHelper(Node* node) {
        if (node != nullptr) {
            printPostOrderHelper(node->left);
            printPostOrderHelper(node->right);
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

            // ?????????????????????????????????????????????????????
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
        printInOrderHelper(root);
    }

    void printPreOrder() {
        cout << "Pre-order traversal:" << endl;
        printPreOrderHelper(root);
    }

    void printPostOrder() {
        cout << "Post-order traversal:" << endl;
        printPostOrderHelper(root);
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
};





void inputData(BinarySearchTree& tree) {
    int key;
    string data;

    cout << "Enter key: ";
    cin >> key;

    cin.ignore(); // Очистка буфера после ввода числа

    cout << "Enter data: ";
    getline(cin, data);

    tree.insert(key, data);
}


void buildBalancedTree(BinarySearchTree& tree, const std::vector<Node*>& nodes, int start, int end) {
    if (start > end) {
        return;
    }

    // Находим середину списка узлов
    int mid = (start + end) / 2;

    // Вставляем узел в дерево
    tree.insert(nodes[mid]->key, nodes[mid]->data);

    // Рекурсивно строим сбалансированные левое и правое поддеревья
    buildBalancedTree(tree, nodes, start, mid - 1);
    buildBalancedTree(tree, nodes, mid + 1, end);
}

void balanceTree(BinarySearchTree& tree) {
    // Получаем список всех узлов в дереве
    vector<Node*> nodes = tree.inorderTraversal();

    // Очищаем дерево
    tree.clear();

    // Рекурсивно строим сбалансированное дерево
    buildBalancedTree(tree, nodes, 0, nodes.size() - 1);
}

void addNewEntry(BinarySearchTree& tree) {
    int key;
    string data;

    cout << "Enter key: ";
    cin >> key;

    cin.ignore(); // Очистка буфера после ввода числа

    cout << "Enter data: ";
    getline(cin, data);

    tree.insert(key, data);
}

void findEntry(BinarySearchTree& tree) {
    int key;

    cout << "Enter key to find: ";
    cin >> key;

    Node* foundNode = tree.find(key);

    if (foundNode != nullptr) {
        cout << "Found entry - Key: " << foundNode->key << ", Data: " << foundNode->data << endl;
    }
    else {
        cout << "Entry not found." << endl;
    }
}

void deleteEntry(BinarySearchTree& tree) {
    int key;

    cout << "Enter key to delete: ";
    cin >> key;

    tree.remove(key);
}

void printMenu() {
    cout << "1. Input data" << endl;
    cout << "2. Balance tree" << endl;
    cout << "3. Add new entry" << endl;
    cout << "4. Find entry" << endl;
    cout << "5. Delete entry" << endl;
    cout << "6. Print tree in-order" << endl;
    cout << "7. Print tree pre-order" << endl;
    cout << "8. Print tree post-order" << endl;
    cout << "9. Exit" << endl;
}

int main() {
    BinarySearchTree tree;

    int choice = 0;

    while (choice != 9) {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: inputData(tree); break;
        case 2: balanceTree(tree); break;
        case 3: addNewEntry(tree); break;
        case 4: findEntry(tree); break;
        case 5: deleteEntry(tree); break;
        case 6: tree.printInOrder(); break;
        case 7: tree.printPreOrder(); break;
        case 8: tree.printPostOrder(); break;
        case 9: cout << "Exiting..." << endl; break;
        default: cout << "Invalid choice. Please try again." << endl; break;
        }
    }

    return 0;
}