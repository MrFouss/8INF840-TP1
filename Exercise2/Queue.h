#include <stdexcept>
#include <assert.h>

// (pop)head -> ... -> ... -> tail(push)

template <typename T>
class Queue {
public:
	Queue() : head(NULL), tail(NULL), size(0) {}

	Queue(const Queue& other) {
		Queue();
		this->copy(other);
	}

	~Queue() {
		clear();
	}

	// modifiers

	void push(const T & data) {
		QueueElement* newElem = new QueueElement(data);
		if (isEmpty()) {
			head = newElem;
		}
		else {
			tail->next = newElem;
		}
		tail = newElem;
		this->size++;
	}

	T pop() {
		assert(!isEmpty());

		QueueElement* top = head;

		if (head == tail) {
			tail = NULL;
		}
		this->head = this->head->next;

		top->next = NULL;
		T data = top->data;
		delete top;

		this->size--;

		return data;
	}

	// accessors

	bool isEmpty() const {
		return this->size == 0;
	}

	// operators

	int getSize() const {
		return this->size;
	}

	const T& getHead() const {
		assert(!isEmpty());
		return head->data;
	}
	const T& getTail() const {
		assert(!isEmpty());
		return tail->data;
	}

	// override operators

	const Queue<T>& operator = (const Queue<T>& other) {
		this->copy(other);
		return (*this);
	}

	template <typename U>
	friend std::ostream& operator<<(std::ostream&, const Queue<U>&);

private:

	class QueueElement {
	public:
		QueueElement(const T& data, QueueElement* next = NULL) : data(data), next(next) {}
		~QueueElement() = default;

		T data;
		QueueElement* next;
	};

	void clear() {
		while (!isEmpty()) {
			pop();
		}
	}

	void copy(const Queue& src) {
		clear();
		QueueElement* curr = src.head;
		while (curr != NULL) {
			push(curr->data);
			curr = curr->next;
		}
	}

	QueueElement* head;
	QueueElement* tail;
	int size;
};


template<typename U>
std::ostream & operator<<(std::ostream & os, const Queue<U>& queue) {
	Queue<U>::QueueElement* curr = queue.head;

	os << "{";

	if (!queue.isEmpty()) {
		while (curr->next != NULL) {
			os << curr->data << " ; ";

			curr = curr->next;
		}
		os << curr->data;
	}

	os << "}" << std::endl;

	return os;
}