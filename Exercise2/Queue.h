#include <stdexcept>

// (pop)head -> ... -> ... -> tail(push)
template <typename T>
class Queue {
public:
	Queue() : head(NULL), tail(NULL), size(0) {}

	//Queue(const Queue&);

	~Queue() {
		while (!isEmpty()) {
			pop();
		}
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
		if (isEmpty()) {
			throw std::runtime_error("Empty queue!");
		}

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

	//int size() const;
	//const T& head() const; //  tête de la file
	//const T& tail() const; // queue de la file

	//// override operators
	//const Queue<T>& operator = (const Queue<T>&) throw (std::bad_alloc);
	template <typename U> friend std::ostream& operator<<(std::ostream&, const Queue<U>&);

private:

	class QueueElement {
	public:
		QueueElement(const T& data, QueueElement* next = NULL) : data(data), next(next) {}
		~QueueElement() = default;

		T data;
		QueueElement* next;
	};

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