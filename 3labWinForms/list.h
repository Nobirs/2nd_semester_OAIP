#pragma once
#include <iostream>
#include <fstream>

#include "Node.h"



void swapPointers(Node* p1, Node* p2) {
    Node* temp = p1;
    p1 = p2;
    p2 = temp;
}


class LinkedList {
public:
    Node* head;
    Node* tail;
    int length;

public:
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->length = 0;
    }

    ~LinkedList() {
        while (head != nullptr)
            pop_front();
    }

    Node* push_front(int data) {
        Node* ptr = new Node(data);

        ptr->next = head;
        if (head != nullptr)
            head->prev = ptr;
        if (tail == nullptr)
            tail = ptr;
        head = ptr;
        length++;
        return ptr;
    }


    Node* push_back(int data) {
        Node* ptr = new Node(data);

        ptr->prev = tail;
        if (tail != nullptr)
            tail->next = ptr;
        if (head == nullptr)
            head = ptr;
        tail = ptr;
        length++;
        return ptr;
    }

    Node* pop_front() {
        if (head == nullptr) return nullptr;

        Node* ptr = head->next;
        if (ptr != nullptr)
            ptr->prev = nullptr;
        else
            tail = nullptr;

        Node* result = new Node(head);
        delete head;
        head = ptr;
        length--;
        return result;
    }


    Node* pop_back() {
        if (tail == nullptr) return nullptr;

        Node* ptr = tail->prev;
        if (ptr != nullptr)
            ptr->next = nullptr;
        else
            head = nullptr;

        Node* result = new Node(tail);
        delete tail;
        tail = ptr;
        length--;
        return result;
    }

    Node* getAt(int index) {
        Node* ptr = head;
        int n = 0;

        while (n != index) {
            if (ptr == nullptr)
                return ptr;
            ptr = ptr->next;
            n++;
        }

        return ptr;
    }


    Node* operator[](int index) {
        return getAt(index);
    }

    Node* insert(int index, int data) {
        Node* right = getAt(index);
        if (right == nullptr)
            return push_back(data);

        Node* left = right->prev;
        if (left == nullptr)
            return push_front(data);

        Node* ptr = new Node(data);

        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;

        length++;

        return ptr;
    }

    void erase(int index) {
        Node* ptr = getAt(index);
        if (ptr == nullptr)
            return;

        if (ptr->prev == nullptr) {
            pop_front();
            return;
        }

        if (ptr->next == nullptr) {
            pop_back();
            return;
        }

        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;

        length--;

        delete ptr;
    }


    void swapMinMax() {
        if (length <= 1) return;
        Node* min = head;
        Node* max = head;
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data < min->data) min = cur;
            if (cur->data > max->data) max = cur;
            cur = cur->next;
        }
        int temp = min->data;
        min->data = max->data;
        max->data = temp;
    }

    void swapNodes(Node* node1, Node* node2) {
        if (node1 == nullptr || node2 == nullptr || node1 == node2) return;

        // Если node1 и node2 соседние
        if (node2->prev == node1) {
            std::swap(node1, node2);
        }
        if (node1->next == node2) {
            // Обновляем ссылки соседей
            if (node1->prev) {
                node1->prev->next = node2;
            }
            if (node2->next) {
                node2->next->prev = node1;
            }
            // Меняем местами узлы
            node1->next = node2->next;
            node2->prev = node1->prev;
            node2->next = node1;
            node1->prev = node2;
        }
        else {
            // Обновляем ссылки соседей
            Node* temp1 = node1->prev;
            Node* temp2 = node1->next;
            Node* temp3 = node2->prev;
            Node* temp4 = node2->next;

            if (temp1) temp1->next = node2;
            if (temp2) temp2->prev = node2;
            if (temp3) temp3->next = node1;
            if (temp4) temp4->prev = node1;

            // Меняем местами узлы
            node1->next = temp4;
            node1->prev = temp3;
            node2->next = temp2;
            node2->prev = temp1;
        }

        // Если один из узлов был головой списка, обновляем голову
        if (node1->prev == nullptr) {
            head = node1;
        }
        else if (node2->prev == nullptr) {
            head = node2;
        }
        if (node1->next == nullptr) {
            tail = node1;
        }
        else if (node2->next == nullptr) {
            tail = node2;
        }
    }
};
