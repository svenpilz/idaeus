#ifndef INCLUDE_LIBCXX_SHARED_PTR_H
#define INCLUDE_LIBCXX_SHARED_PTR_H

#include <cstddef>
#include <cassert>

namespace std {

template <typename T>
class shared_ptr {
public:
	shared_ptr() noexcept : _references(NULL), _data(NULL) {};
	
	explicit shared_ptr (T* p) : _references(new int), _data(p)  {
		(*_references)++;
		printf("c%d ", *_references);
	}

	shared_ptr (const shared_ptr<T>& x) noexcept : _references(x._references), _data(x._data) {
		(*_references)++;
		printf("d%d ", *_references);
	}
	
	~shared_ptr() {
		if (_references != NULL) {
			assert(_data != NULL);
			assert(*_references > 0);
		
			if (--(*_references) == 0) {
				delete _data;
				delete _references;
				_data = NULL;
				_references = NULL;
			}
		}
	}
	
	T* get() const noexcept {
		return _data;
	}
	
	T& operator*() const noexcept {
		assert(_data != NULL);
		return *_data;
	}
	
	T* operator->() const noexcept {
		return get();
	}
	
protected:
	int* _references;
	T* _data;
};

}

#endif
