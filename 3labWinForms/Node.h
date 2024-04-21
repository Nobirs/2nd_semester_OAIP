#pragma once

#include <ostream>

using std::ostream;

struct Node {
    int data;
    Node* prev, * next;

    Node(int data) {
        this->data = data;
        this->prev = nullptr;
        this->next = nullptr;
    }

    Node(Node* from) {
        this->data = from->data;
        this->prev = from->prev;
        this->next = from->next;
    }

    friend ostream& operator<<(ostream& os, Node& n) {
        os << n.data << " ";
        return os;
    }
};