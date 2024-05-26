#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>


#include "input.h"
#include "binaryTree.h"

using std::string;
using std::vector;

using std::cin;
using std::cout;
using std::endl;




void inputData(BinarySearchTree& tree) {
    int key = inputInt("Key: ");
    string data;

    cout << "Data: ";
    getline(cin, data);

    tree.insert(key, data);
}


void buildBalancedTree(BinarySearchTree& tree, const vector<Node*>& nodes, int start, int end) {
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
    //tree.clear();
    BinarySearchTree newTree;

    // Рекурсивно строим сбалансированное дерево
    buildBalancedTree(newTree, nodes, 0, nodes.size() - 1);
    tree.clear();
    tree = newTree;
}


void findEntry(BinarySearchTree& tree) {
    int key = inputInt("Key to find: ");

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
    cin.ignore();

    tree.remove(key);
}

int printMenu() {
    cout << "**************************************************" << endl;
    cout << "*                   Меню                         *" << endl;
    cout << "**************************************************" << endl;
    cout << "* 1. Input data                                   " << endl;
    cout << "* 2. Balance tree                                 " << endl;
    cout << "* 3. Find entry                                   " << endl;
    cout << "* 4. Delete entry                                 " << endl;
    cout << "* 5. Print tree in-order                          " << endl;
    cout << "* 6. Print tree pre-order                         " << endl;
    cout << "* 7. Print tree post-order                        " << endl;
    cout << "* 8. Task                                         " << endl;
    cout << "* 9. Exit                                         " << endl;
    cout << "**************************************************" << endl;
    int choice = inputInt("Выберите пункт меню: ", 1, 9, true);
    return choice;
}

void task(BinarySearchTree& tree)
{
    tree.removeRightMax();
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    BinarySearchTree tree;


    while (inputYesNo("Do you wanna start program[y/n]?")) {
        bool flag = true;
        while (flag) {
            switch (printMenu()) {
            case 1: inputData(tree); break;
            case 2: balanceTree(tree); break;
            case 3: findEntry(tree); break;
            case 4: deleteEntry(tree); break;
            case 5: tree.printInOrder(); break;
            case 6: tree.printPreOrder(); break;
            case 7: tree.printPostOrder(); break;
            case 8: task(tree); break;
            case 9: flag = false; break;
            default: cout << "Invalid choice. Please try again." << endl; break;
            }
        }
    }

    return 0;
}