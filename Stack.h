/**
 * Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_STACK_H_
#define _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_STACK_H_

#include <iostream>

template <typename T>
class Stack {
 private:
	int defaultCapacity = 500;
	int expandFactor = 2;
	int numElem;
	int maxCapacity;
	T *data;

 public:
	Stack() {
		numElem = 0;
		maxCapacity = defaultCapacity;
		data = new T[maxCapacity];
	}
	explicit Stack(int initialCapacity) {
		numElem = 0;
        maxCapacity = initialCapacity;
        data = new T[maxCapacity];
    }
	~Stack() {
		if (this->data != nullptr) {
			delete[] this->data;
		}
	}
	void push(T elem) {
		if (numElem == maxCapacity) {
			T *data2 = new T[maxCapacity*expandFactor];
			for (int i = 0; i < maxCapacity; i++) {
				data2[i] = data[i];
			}
			delete[] data;
			maxCapacity = maxCapacity*expandFactor;
			data = data2;
		}
		data[numElem++] = elem;
	}
	T pop() {
		numElem--;
		return data[numElem];
	}
	T peek() {
		return data[numElem-1];
	}
	int size() {
		return numElem;
	}
	bool isEmpty() {
		if (numElem == 0) {
			return true;
		}
		return false;
	}
};

#endif  // _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_STACK_H_
