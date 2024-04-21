#include "LinkedList.h"

List::List() {
    first = nullptr;
    last = nullptr;
}

bool List::is_empty() {
    return first == nullptr;
}

void List::push_back(int _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;
}


void List::print(ostream& os) {
    if (is_empty()) return;
    os << endl << " ------------------------------- " << endl;
    Node* p = first;
    while (p) {
        os << p->val << " ";
        p = p->next;
    }
    os << endl << " ------------------------------- " << endl;
}

Node* List::find(int _val) {
    Node* p = first;
    while (p && p->val != _val) p = p->next;
    return (p && p->val == _val) ? p : nullptr;
}

Node* List::min()
{
    if (first == last) return nullptr;
    Node* current = first;
    Node* result = first;
    while (current != nullptr) {
        if (current->val < result->val) result = current;
        current = current->next;
    }
    return result;
}

Node* List::max()
{
    if (first == last) return nullptr;
    Node* current = first;
    Node* result = first;
    while (current != nullptr) {
        if (current->val > result->val) result = current;
        current = current->next;
    }
    return result;
}


void List::writeToFile(ofstream& of) {
    if (is_empty()) return;
    of.open("List.txt");
    if (of.is_open()) {
        of << "\n-------------------------------\n";
        Node* p = first;
        while (p) {
            of << p->val << " ";
            p = p->next;
        }
        of << endl << " ------------------------------- " << endl;
    }
    of.close();
}

void List::remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}

void List::remove_last() {
    if (is_empty()) return;
    if (first == last) {
        remove_first();
        return;
    }
    Node* p = first;
    while (p->next != last) p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
}

Node* List::pop()
{
    if (is_empty()) return nullptr;
    if (first == last) {
        Node* p = new Node(0);
        p->val = first->val;
        p->next = first->next;
        delete first;
        first = nullptr;
        last = nullptr;
        return p;
    }
    Node* p = first;
    while (p->next != last) p = p->next;
    p->next = nullptr;
    Node* result = last;
    last = p;
    return result;
}



void List::remove(int _val, ostream& err) {
    if (is_empty()) return;
    if (first->val == _val) {
        remove_first();
        return;
    }
    else if (last->val == _val) {
        remove_last();
        return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != _val) {
        fast = fast->next;
        slow = slow->next;
    }
    if (!fast) {
        err << "This element does not exist" << endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
}

Node* List::operator[](const int index) {
    if (is_empty()) return nullptr;
    Node* p = first;
    for (int i = 0; i < index; i++) {
        p = p->next;
        if (!p) return nullptr;
    }
    return p;
}