/*
 * Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_RESIZABLEARRAY_H_
#define _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_RESIZABLEARRAY_H_

#include <iostream>

template <typename T>
class ResizableArray {
 private:
    int defaultCapacity = 3000;
    int expandFactor = 2;
    int numElements;
    int maxCapacity;
    T *data;

 public:
    // Constructor
    ResizableArray() {
        numElements = 0;
        maxCapacity = defaultCapacity;
        data = new T[maxCapacity];
    }
    // Another constructor
    explicit ResizableArray(int initialCapacity) {
        numElements = 0;
        maxCapacity = initialCapacity;
        data = new T[maxCapacity];
    }
    // Another constructor
    explicit ResizableArray(int initialCapacity, int defaultFactor) {
        numElements = 0;
        maxCapacity = initialCapacity;
        expandFactor = defaultFactor;
        data = new T[maxCapacity];
    }
    // Destructor
    ~ResizableArray() {
		if (this->data != nullptr) {
			delete[] this->data;
		}
    }
    void addLast(T element) {
        if (numElements == maxCapacity) {
			T *data2 = new T[maxCapacity*expandFactor];
			for (int i = 0; i < maxCapacity; i++) {
				data2[i] = data[i];
			}
			delete[] data;
			maxCapacity = maxCapacity*expandFactor;
			data = data2;
		}
		data[numElements++] = element;
    }
    void addFirst(T element) {
		if (numElements == maxCapacity) {
			maxCapacity = maxCapacity*expandFactor;
		}
		T *data2 = new T[maxCapacity];
		data2[0] = element;
		for (int i = 1; i < numElements+1; i++) {
			data2[i] = data[i-1];
		}
		delete[] data;
		data = data2;
		numElements++;
    }
    T removeLast() {
        if (numElements != 0) {
			numElements--;
		}
        return data[numElements];
    }
    T removeFirst() {
        for (int i = 1; i < numElements; i++) {
				data[i-1] = data[i];
		}
		numElements--;
        return data[numElements];
    }
    bool isEmpty() {
        if (numElements != 0) {
			return false;
		}
        return true;
    }
    int size() {
        return numElements;
    }

    // Getters & Setters
    T *getData() {
        return data;
    }

	T getLast() {
		if (numElements != 0) {
			return data[numElements-1];
		}
		return 0;
	}

	T getElem(int pos) {
		return data[pos];
	}
	void setElem(T element, int pos) {
		data[pos] = element;
	}
};

#endif  // _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_RESIZABLEARRAY_H_
