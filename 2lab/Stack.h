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
	Stack();
	~Stack();

	void push(int value);
	int pop();
	int clear();
	int* toArray();
	int getLength();

	void sortByPointers();
	void sortByValues();

	StackElem* findMin();
	StackElem* findMax();
	void swapValues(StackElem* a, StackElem* b);
};

