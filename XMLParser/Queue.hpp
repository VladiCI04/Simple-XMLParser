#pragma once
#include <utility>
#include <exception>

template<class T>
class Queue {
private:
	static const short INITIAL_CAPACITY = 4;
	static const short RESIZE_COEF = 2; // the most optimal is between 1.4 and 1.5

	T* data;
	size_t capacity = INITIAL_CAPACITY;
	size_t size = 0;

	size_t get = 0, put = 0;

	void resize();

	void incrementIndexPointer(size_t& indexPointer);

public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(Queue<T>&& other) noexcept;
	Queue<T>& operator=(const Queue& other);
	Queue<T>& operator=(Queue&& other) noexcept;
	~Queue();

	void push(const T& value);
	void push(T&& value);
	void pop();

	const T& peek() const;
	bool isEmpty() const;

private:
	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);
	void free();
};

template<class T>
void Queue<T>::resize() {
	T* newData = new T[capacity * RESIZE_COEF];
	for (size_t i = 0; i < size; i++) {
		newData[i] = data[get];
		incrementIndexPointer(get);
	}

	capacity *= RESIZE_COEF;
	delete[] data;
	data = newData;
	get = 0;
	put = size;
}

template<class T>
void Queue<T>::incrementIndexPointer(size_t& indexPointer) {
	(++indexPointer) %= capacity;
}

template<class T>
Queue<T>::Queue() {
	data = new T[capacity];
}

template<class T>
Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}

template<class T>
Queue<T>::Queue(Queue<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class T>
Queue<T>::~Queue() {
	free();
}

template<class T>
void Queue<T>::push(const T& value) {
	if (size == capacity) {
		resize();
	}

	data[put] = value;
	incrementIndexPointer(put);
	size++;
}

template<class T>
void Queue<T>::push(T&& value) {
	if (size == capacity) {
		resize();
	}

	data[put] = std::move(value);
	incrementIndexPointer(put);
	size++;
}

template<class T>
void Queue<T>::pop() {
	if (isEmpty()) {
		throw std::exception("Queue is empty!");
	}

	incrementIndexPointer(get);
	size--;
}

template<class T>
const T& Queue<T>::peek() const {
	if (isEmpty()) {
		throw std::exception("Queue is empty!");
	}

	return data[get];
}

template<class T>
bool Queue<T>::isEmpty() const {
	return size == 0;
}

template<class T>
void Queue<T>::copyFrom(const Queue<T>& other) {
	get = other.get;
	put = other.put;
	capacity = other.capacity;
	size = other.size;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template<class T>
void Queue<T>::moveFrom(Queue<T>&& other) {
	get = other.get;
	put = other.put;
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	other.data = nullptr;
	other.get = other.put = 0;
	other.size = other.capacity = 0;
}

template<class T>
void Queue<T>::free() {
	delete[] data;
}