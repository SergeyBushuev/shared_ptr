#include "stdlib.h"
#include <iostream>

template <class T>
class Shared_ptr
{
public:
	Shared_ptr() noexcept;
	Shared_ptr(T* pointer); /*strong*/
	Shared_ptr(const Shared_ptr<T>& src) noexcept;
	Shared_ptr(Shared_ptr<T>&& src) noexcept;
	Shared_ptr<T> operator= (Shared_ptr<T>& other); /*strong*/
	Shared_ptr<T>& operator= (Shared_ptr<T>&& other); /*strong*/
	~Shared_ptr() noexcept; 
	
	bool unique() const noexcept;
	size_t use_count() const noexcept;
	T* get() const noexcept;
	operator bool() noexcept;
	void reset() noexcept;
	T* operator ->() const; /*strong*/
	T& operator *() const;  /*strong*/
        void swap(Shared_ptr<T>&) noexcept;
private:
	T* ptr;
	size_t* count;
};

template <typename T, class ...Args>
auto make_shared(Args && ...args) -> Shared_ptr<T>
{
	return Shared_ptr<T>(new T(std::forward<Args>(args)...));
}

template <class T>
noexcept Shared_ptr<T>::Shared_ptr() : ptr(nullptr), count(nullptr)
{}

template <class T>
noexcept Shared_ptr<T>::Shared_ptr(T* pointer) : ptr(pointer), count(new size_t(1))
{}

template <class T>
noexcept Shared_ptr<T>::Shared_ptr(const Shared_ptr<T>& src) : ptr(src.ptr), count(src.count)
{
	if (src.ptr != nullptr)
	{
	    ++(*count);
	}
}

template <typename T>
noexcept Shared_ptr<T>::Shared_ptr(Shared_ptr<T>&& src) : ptr(src.ptr), count(src.count)
{
	src.ptr = nullptr;
	src.count = nullptr;
}

template <class T>
noexcept Shared_ptr<T> Shared_ptr<T>::operator= (Shared_ptr<T>& other)
{
	if (this != &other)
	{
		Shared_ptr(other).swap(*this);
	}
	return *this;
}

template <typename T>
noexcept Shared_ptr<T>& Shared_ptr<T>::operator = (Shared_ptr<T>&& other)
{
	if (this != &other) this->swap(other); 
	return *this;
}

template <class T>
noexcept Shared_ptr<T>::~Shared_ptr(){
	if (count) {
		if (*count == 1) {
			delete count;
			delete ptr;
		}
		else --(*count);
	}
}

template <class T>
noexcept bool Shared_ptr<T>::unique() const
{
	if (count == nullptr)
		return (false);
	return (*count == 1);
}

template <class T>
noexcept size_t Shared_ptr<T>::use_count() const
{
	if (count == nullptr)
		return 0;
	else
		return *count;
}

template <class T>
noexcept T* Shared_ptr<T>::get() const
{
	return ptr;
}

template <class T>
noexcept Shared_ptr<T>::operator bool()
{
	return (this->get() != nullptr);
}

template <class T>
noexcept void Shared_ptr<T>::reset()
{
	this->swap(Shared_ptr());
}

template <class T>
noexcept T* Shared_ptr<T>::operator ->() const 
{
	if (ptr == nullptr) 
	{
	   throw ("nullptr");
	}
	return ptr;
}

template <class T>
noexcept T& Shared_ptr<T>::operator *() const
{
	if (ptr == nullptr) 
	{
           throw ("nullptr");
	}
	return *ptr;
}

template <class T>
noexcept void Shared_ptr<T>::swap(Shared_ptr<T>& other)
{
	std::swap(ptr, other.ptr);
	std::swap(count, other.count);
}
