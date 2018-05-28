#pragma once

template <typename T>
class Pile
{
private:
	T* tab;
	int top;
	int maxSize;
	static const int MAX_PILE = 100;

public:
	// constructors
	Pile(int max = MAX_PILE);
	Pile(const Pile&);

	// destructor
	~Pile();
	
	// modifiers
	void push(const T&);
	T pop();

	// selectors
	bool isEmpty() const;

	int getSize() const;
	int getMaxSize() const;

	T& getTop() const;

	// operators
	const Pile<T>& operator= (const Pile<T>);
};

//--------------------------------------------------------------------------------

template<typename T>
inline Pile<T>::Pile(int max)
{
	tab = new T[max];
	top = -1;
	maxSize = max;
}

template<typename T>
inline Pile<T>::Pile(const Pile& p)
{
	tab = new T[p.maxSize];
	maxSize = p.maxSize;

	for (int i = 0; i < maxSize; i++)
		tab[i] = p.tab[i];

	top = p.top;
}

template<typename T>
inline Pile<T>::~Pile()
{
	delete[] tab;
}

template<typename T>
inline void Pile<T>::push(const T & e)
{
	if ((top + 1) < maxSize) {
		top += 1;
		tab[top] = e;
	}
	else
		cout << "ERROR : stack is full\n";
}

template<typename T>
inline T Pile<T>::pop()
{
	if (!isEmpty())
		return tab[top--];
	else
		cout << "ERROR : stack is empty\n";
}

template<typename T>
inline bool Pile<T>::isEmpty() const
{
	return (top == -1);
}

template<typename T>
inline int Pile<T>::getSize() const
{
	return (this->top+1);
}

template<typename T>
inline int Pile<T>::getMaxSize() const
{
	return this->maxSize;
}

template<typename T>
inline T& Pile<T>::getTop() const
{
	return tab[this->top];
}

template<typename T>
inline const Pile<T>& Pile<T>::operator=(const Pile<T>)
{
	if (tab != 0) delete[] tab;
	tab = new T[p.maxSize];
	
	maxSize = p.maxSize;
	for (int i = 0; i < maxSize; i++)
		tab[i] = p.tab[i];
	top = p.top;
	
	return (*this);
}
