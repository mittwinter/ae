#ifndef __VECTOR_SF_H
#define __VECTOR_SF_H

#include <cstdlib>
#include <cstring>


template < typename T >
class vec_array {
private:
	size_t capacity;
	size_t size;
	T *field;

public:
	vec_array()
			: capacity(1)
			, size(0)
			, field(new T[1]) {
	}

	virtual ~vec_array() {
		delete[] field;
		field = 0;
	}

	void push_back(const T &t) {
		if (size >= capacity) {
			T *new_field = new T[2 * capacity];
			for (size_t i = 0; i < size; ++i) {
				new_field[i] = field[i];
			}
			delete[] field;
			field = new_field;
			capacity *= 2;
		}

		field[size] = t;
		++size;
	}
};

template < typename T >
class vec_alloc {
private:
	size_t capacity;
	size_t size;
	T *field;

public:
	vec_alloc()
			: capacity(1)
			, size(0)
			, field(static_cast < T * > (malloc(sizeof(T)))) {
	}

	virtual ~vec_alloc() {
		free(field);
		field = 0;
	}

	void push_back(const T &t) {
		if (size >= capacity) {
			capacity *= 2;
			T *new_field = static_cast < T * > (malloc(capacity * sizeof(T)));
			memcpy(new_field, field, size * sizeof(T));
			free(field);
			field = new_field;
		}

		field[size] = t;
		++size;
	}
};

template < typename T >
class vec_realloc {
private:
	size_t capacity;
	size_t size;
	T *field;

public:
	vec_realloc()
			: capacity(1)
			, size(0)
			, field(static_cast < T * > (malloc(sizeof(T)))) {
	}

	virtual ~vec_realloc() {
		free(field);
		field = 0;
	}

	void push_back(const T &t) {
		if (size >= capacity) {
			capacity *= 2;
			field = static_cast < T * > (realloc(field, sizeof(T) * capacity));
		}

		field[size] = t;
		++size;
	}
};

#endif
