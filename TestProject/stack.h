#pragma once
struct StackElem {
    int value;
    StackElem* next;
};


class Stack
{
private:
    int length;
    StackElem* first;
public:
    Stack()
    {
        length = 0;
        first = nullptr;
    }
    ~Stack()
    {
        clear();
    }

    void push(int value)
    {
        StackElem* elem = new StackElem();
        elem->value = value;
        elem->next = first;
        first = elem;
        length++;
    }
    int pop()
    {
        int value = first->value;
        StackElem* elem = first;
        first = first->next;
        delete elem;
        length--;
        return value;
    }
    int clear()
    {
        while (first != nullptr) {
            StackElem* current = first;
            first = first->next;
            delete current;
        }
        length = 0;
        return 0;
    }
    int* toArray()
    {
        int* arr = new int[length];
        StackElem* ptr = first;
        for (int i = 0; i < length; i++, ptr = ptr->next) {
            arr[i] = ptr->value;
        }
        return arr;
    }
    int getLength()
    {
        return length;
    }

    void sortByPointers()
    {
        push(0);
        StackElem* t = nullptr, * t1, * r;
        if (first->next->next == nullptr) return;
        do {
            for (t1 = first; t1->next->next != t; t1 = t1->next)
                if (t1->next->value > t1->next->next->value) {
                    r = t1->next->next;
                    t1->next->next = r->next;
                    r->next = t1->next;
                    t1->next = r;
                }
            t = t1->next;
        } while (first->next->next != t);
        pop();
    }
    void sortByValues()
    {
        StackElem* t = nullptr, * t1;
        int r;
        do {
            for (t1 = first; t1->next != t; t1 = t1->next)
                if (t1->value > t1->next->value) {
                    r = t1->value;
                    t1->value = t1->next->value;
                    t1->next->value = r;
                }
            t = t1;
        } while (first->next != t);
    }

    void swapValues(StackElem* a, StackElem* b)
    {
        if (a != nullptr && b != nullptr) {
            int temp = a->value;
            a->value = b->value;
            b->value = temp;
        }
    }
};

