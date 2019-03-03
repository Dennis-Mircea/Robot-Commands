/*
 * Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_DEQUE_H_
#define _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_DEQUE_H_

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T> *next;
    Node<T> *prev;
    explicit Node(T data) {
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }
};
template <typename T>
class Deque {
 private:
    Node<T> *head;
    Node<T> *tail;
    int numElements;
    Node<T> *goToPos(int pos) {
        int count = 0;
        Node<T> *temp = head;

        while (count != pos) {
            temp = temp->next;
            count++;
        }
        return temp;
    }

 public:
    // Constructor
    Deque() {
        head = nullptr;
        tail = nullptr;
        numElements = 0;
    }
    // Another constructor
    explicit Deque(Node<T> *head) {
        this->head = head;
        while (head != nullptr) {
            numElements++;
            head = head->next;
        }
    }
    // Destructor
    ~Deque() {
        if (head != nullptr) {
				while (head->next != nullptr) {
					head = head->next;
					delete head->prev;
				}
				delete head;
		}
    }
    void push_back(T data) {Node<T> *newElem = new Node<T>(data);
		if (tail == nullptr) {
			head = newElem;
			tail = newElem;
			numElements++;
		} else {
			tail->next = newElem;
			newElem->prev = tail;
			newElem->next = nullptr;
			tail = newElem;
			numElements++;
		}
    }
    void push_front(T data) {
		Node<T>* newElem = new Node<T>(data);
		if (head == nullptr) {
			head = newElem;
			tail = newElem;
			numElements++;
		} else {
			head->prev = newElem;
			newElem->next = head;
			newElem->prev = nullptr;
			head = newElem;
			numElements++;
		}
    }
    T pop_back() {
		T value = tail->data;
		if (tail == nullptr) {
			return 0;
		}
		if (tail != nullptr) {
			if (head->next == nullptr && head->prev == nullptr) {
				numElements--;
				delete tail;
				head = nullptr;
				tail = nullptr;
			} else {
				numElements--;
				tail = tail->prev;
				delete tail->next;
				tail->next = nullptr;
			}
		}
        return value;
    }
    T pop_front() {
        T value = head->data;
		if (head != nullptr) {
			if (head->next == nullptr && head->prev == nullptr) {
				numElements--;
				delete head;
				head = nullptr;
				tail = nullptr;
			} else {
				numElements--;
				head = head->next;
				delete head->prev;
				head->prev = nullptr;
			}
		}
        return value;
    }
    bool empty() {
		if (numElements != 0) {
			return false;
		}
       	return true;
    }
    int size() {
        return numElements;
    }
    // Getters & Setters
    Node<T> *front() {
		if (head != nullptr) {
        	return head;
		}
		return nullptr;
    }
    Node<T> *back() {
        if (head != nullptr) {
        	return head;
		}
		return nullptr;
    }
};

#endif  // _HOME_DENNIS_DESKTOP_TEMA_1_TEMA1_DEQUE_H_
