#pragma once

#include <iostream>
#include <assert.h>

// A FIFO (First In First Out) data structure implementation
// (pop)head -> ... -> ... -> tail(push)

template <typename T>
class Queue {

public:

	// CONSTRUCTORS

	Queue(int size = 10) :
		head(0),
		tail(-1),
		size(size)
	{
		assert(size > 0);
		data = new T[size];
	}

	Queue(const Queue& other) :
		head(0),
		tail(-1),
		size(0),
		data(0)
	{
		this->copy(other);
	}

	// DESTRUCTOR

	~Queue() {
		delete[] data;
	}

	// MODIFIERS

	// a copy of data is made to store it in the queue
	void push(const T & element) {
		if (isFull()) {
			extendArray();
		}
		data[(++tail)%size] = element;
	}

	T pop() {
		assert(!isEmpty());
		capHeadAndTail();
		return data[(head++)%size];
	}

	void clear() {
		head = tail + 1;
	}

	// ACCESSORS

	bool isEmpty() const {
		return head > tail;
	}

	bool isFull() const {
		return getElementNbr() == size;
	}

	int getElementNbr() const {
		return tail - head + 1;
	}

	int getSize() const {
		return size;
	}

	const T& getHead() const {
		assert(!isEmpty());
		return data[head%size];
	}
	const T& getTail() const {
		assert(!isEmpty());
		return data[tail%size];
	}

	// OPERATORS

	const Queue<T>& operator = (const Queue<T>& other) {
		this->copy(other);
		return (*this);
	}

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Queue<U>&);

private:

	// UTILS

	void copy(const Queue& src) {
		if (data != 0) {
			delete[] data;
		}

		size = src.size;
		head = src.head;
		tail = src.tail;
		data = new T[src.size];

		for (int i = 0; i < src.size; ++i) {
			data[i] = src.data[i];
		}
	}

	// when the array needs to be extended
	// the size is doubled
	void extendArray() {
		T* newData = new T[size * 2]; 
		for (int i = head; i <= tail; ++i) {
			newData[i - head] = data[i%size];
		}
		head = 0;
		tail = size-1;
		size *= 2;
		delete[] data;
		data = newData;
	}

	// avoid overflows by caping head and tail under size*2
	// this maintains the properties of head and tail described below
	void capHeadAndTail() {
		if (isEmpty()) {
			head = 0;
			tail = -1;
		}
		else {
			head %= size;
			tail %= size;
			if (tail < head) {
				tail + size;
			}
		}
	}

	// FIELDS

	T* data;

	// the indices of the head and tail elements
	// if empty : head = tail+1
	// if not empty : head <= tail and tail - head < size
	int head;
	int tail;

	// the size of the data array
	int size;
};

// OSTREAM OPERATOR

template<typename U>
std::ostream & operator<<(std::ostream & os, const Queue<U>& queue) {

	os << "{";

	if (!queue.isEmpty()) {
		for (int i = queue.head; i < queue.tail; i++) {
			os << queue.data[i%queue.size] << ",";
		}
		os << queue.data[queue.tail%queue.size];
	}

	os << "}" << std::endl;

	return os;
}