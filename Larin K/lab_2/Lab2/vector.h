#pragma once

#include <cassert>
#include <cinttypes>
#include <initializer_list>
#include <algorithm>

namespace lab {

	template <typename T>
	class vector;

	template <typename T> bool operator==(const vector<T>&, const vector<T>&);
	template <typename T> bool operator!=(const vector<T>&, const vector<T>&);
	template <typename T> vector<T> operator+(vector<T>, const vector<T>&);
	template <typename T> vector<T> operator-(vector<T>, const vector<T>&);
	template <typename T> vector<T> operator*(const T&, vector<T>);
	template <typename T> vector<T> operator*(vector<T>, const T&);
	template <typename T> vector<T> operator/(vector<T>, const T&);


	template <typename T>
	class vector
	{
	public:
		vector();
		vector(size_t, const T & = T());
		vector(std::initializer_list<T>);
		vector(const vector&);
		vector(vector&&) noexcept;

		~vector();

		vector& operator=(const vector&);
		vector& operator=(vector&&) noexcept;

		T& operator[](size_t);
		const T& operator[](size_t) const;

		template <typename U>
		void push_back(U&&);
		void pop_back();

		void resize(size_t);
		void reserve(size_t);
		void clear();

		size_t size() const;

		friend bool operator== <>(const vector&, const vector&);
		friend bool operator!= <>(const vector&, const vector&);

		friend vector operator+ <>(vector, const vector&);
		friend vector operator- <>(vector, const vector&);
		friend vector operator* <>(const T&, vector);
		friend vector operator* <>(vector, const T&);
		friend vector operator/ <>(vector, const T&);

		vector& operator+=(const vector&);
		vector& operator-=(const vector&);
		vector& operator*=(const T&);
		vector& operator/=(const T&);

		vector operator-() const;

		T* begin();
		const T* begin() const;
		T* end();
		const T* end() const;

		T& front();
		const T& front() const;
		T& back();
		const T& back() const;

	protected:
		size_t _capacity, _size;
		T* _data;
	};

	template <typename T>
	vector<T>::vector()
		: _capacity(0)
		, _size(0)
		, _data(nullptr)
	{}

	template <typename T>
	vector<T>::vector(const vector& right)
		: _capacity(right._size)
		, _size(right._size)
		, _data(static_cast<T*>(operator new(right._size * sizeof(T))))
	{
		for (size_t i = 0; i < this->_size; i++)
		{
			new (this->_data + i) T(right[i]);
		}
	}

	template <typename T>
	vector<T>::vector(vector&& right) noexcept
		: _capacity(right._capacity)
		, _size(right._size)
		, _data(right._data)
	{
		right._capacity = 0;
		right._size = 0;
		right._data = nullptr;
	}

	template <typename T>
	vector<T>::vector(size_t size, const T& val)
		: _capacity(size)
		, _size(size)
		, _data(static_cast<T*>(operator new(size * sizeof(T))))
	{
		for (size_t i = 0; i < this->_size; i++)
		{
			new (this->_data + i) T(val);
		}
	}

	template <typename T>
	vector<T>::vector(std::initializer_list<T> iList)
		: _capacity(iList.size())
		, _size(iList.size())
		, _data(static_cast<T*>(operator new(iList.size() * sizeof(T))))
	{
		size_t i = 0;
		for (auto& val : iList)
		{
			new (this->_data + i) T(val);
			i++;
		}
	}



	template <typename T>
	vector<T>::~vector()
	{
		this->clear();
	}



#pragma warning(push)
#pragma warning(disable:6385)
#pragma warning(disable:6386)
	template <typename T>
	vector<T>& vector<T>::operator=(const vector<T>& right)
	{
		if (this == &right) {
			return *this;
		}

		if (this->_capacity < right._size)
		{
			this->clear();

			this->_capacity = right._size;
			this->_data = static_cast<T*>(operator new(this->_capacity * sizeof(T)));
		}

		for (size_t i = 0; i < this->_size && i < right._size; i++)
		{
			this->_data[i] = right._data[i];
		}
		for (size_t i = right._size; i < this->_size; i++)
		{
			this->_data[i].~T();
		}
		for (size_t i = this->_size; i < right._size; i++)
		{
			new (this->_data + i) T(right[i]);
		}

		this->_size = right._size;

		return *this;
	}
#pragma warning(pop)

	template <typename T>
	vector<T>& vector<T>::operator=(vector<T>&& right) noexcept
	{
		if (this == &right) {
			return *this;
		}

		this->clear();

		this->_capacity = right._capacity;
		this->_size = right._size;
		this->_data = right._data;

		right._capacity = 0;
		right._size = 0;
		right._data = nullptr;

		return *this;
	}



	template <typename T>
	T& vector<T>::operator[](size_t index)
	{
		assert(index < this->_size);
		return this->_data[index];
	}

	template <typename T>
	const T& vector<T>::operator[](size_t index) const
	{
		return const_cast<vector<T>&>(*this)[index];
	}



	template <typename T>
	template <typename U>
	void vector<T>::push_back(U&& val)
	{
		if (this->_size == this->_capacity) {
			this->reserve(this->_capacity * 2 + 1);
		}

		new (this->_data + this->_size) T(std::forward<U>(val));
		this->_size++;
	}

	template <typename T>
	void vector<T>::pop_back()
	{
		assert(this->_size != 0);

		this->_size--;
		this->_data[this->_size].~T();
	}



	template <typename T>
	void vector<T>::reserve(size_t capacity)
	{
		if (this->_capacity < capacity) {
			this->_capacity = capacity;
			T* tmp = static_cast<T*>(operator new(this->_capacity * sizeof(T)));

			for (size_t i = 0; i < this->_size; i++)
			{
				new (tmp + i) T(std::move(this->_data[i]));
				this->_data[i].~T();
			}

			operator delete(this->_data);

			this->_data = tmp;
		}
	}

	template <typename T>
	void vector<T>::resize(size_t size)
	{
		if (size <= this->_size) {
			for (size_t i = size; i < this->_size; i++)
			{
				this->_data[i].~T();
			}
		}
		else {
			if (this->_capacity < size) {
				this->reserve(size);
			}

			for (size_t i = this->_size; i < size; i++)
			{
				new (this->_data + i) T();
			}
		}

		this->_size = size;
	}

	template <typename T>
	void vector<T>::clear()
	{
		for (size_t i = 0; i < this->_size; i++)
		{
			this->_data[i].~T();
		}
		operator delete(this->_data);

		this->_data = nullptr;
		this->_capacity = 0;
		this->_size = 0;
	}

	template <typename T>
	size_t vector<T>::size() const
	{
		return this->_size;
	}



	template <typename T>
	bool operator==(const vector<T>& left, const vector<T>& right)
	{
		if (&left == &right) {
			return true;
		}
		if (left._size != right._size) {
			return false;
		}

		for (size_t i = 0; i < left._size; i++)
		{
			if (left._data[i] != right._data[i]) {
				return false;
			}
		}

		return true;
	}

	template <typename T>
	bool operator!=(const vector<T>& left, const vector<T>& right)
	{
		return !(left == right);
	}



	template <typename T>
	vector<T> vector<T>::operator-() const
	{
		vector<T> tmp;
		tmp.reserve(this->_size);

		for (size_t i = 0; i < this->_size; i++)
		{
			tmp.push_back(-this->_data[i]);
		}

		return tmp;
	}

	template <typename T>
	vector<T>& vector<T>::operator+=(const vector& right)
	{
		assert(right._size == this->_size);

		for (size_t i = 0; i < this->_size; i++)
		{
			this->_data[i] += right._data[i];
		}

		return *this;
	}

	template <typename T>
	vector<T>& vector<T>::operator-=(const vector& right)
	{
		assert(right._size == this->_size);

		for (size_t i = 0; i < this->_size; i++)
		{
			this->_data[i] -= right._data[i];
		}

		return *this;
	}

	template <typename T>
	vector<T>& vector<T>::operator*=(const T& right)
	{
		for (size_t i = 0; i < this->_size; i++)
		{
			this->_data[i] *= right;
		}

		return *this;
	}

	template <typename T>
	vector<T>& vector<T>::operator/=(const T& right)
	{
		for (size_t i = 0; i < this->_size; i++)
		{
			this->_data[i] /= right;
		}

		return *this;
	}



	template <typename T>
	vector<T> operator+(vector<T> left, const vector<T>& right)
	{
		left += right;

		return left;
	}

	template <typename T>
	vector<T> operator-(vector<T> left, const vector<T>& right)
	{
		left -= right;

		return left;
	}

	template <typename T>
	vector<T> operator*(vector<T> left, const T& right)
	{
		left *= right;

		return left;
	}

	template <typename T>
	vector<T> operator*(const T& left, vector<T> right)
	{
		return std::move(right) * left;
	}

	template <typename T>
	vector<T> operator/(vector<T> left, const T& right)
	{
		left /= right;

		return left;
	}



	template <typename T>
	T* vector<T>::begin()
	{
		return this->_data;
	}

	template <typename T>
	const T* vector<T>::begin() const
	{
		return this->_data;
	}

	template <typename T>
	T* vector<T>::end()
	{
		return this->_data + this->_size;
	}

	template <typename T>
	const T* vector<T>::end() const
	{
		return this->_data + this->_size;
	}



	template <typename T>
	T& vector<T>::front()
	{
		assert(this->_size != 0);
		return this->_data[0];
	}

	template <typename T>
	const T& vector<T>::front() const
	{
		return const_cast<vector<T>&>(*this).front();
	}

	template <typename T>
	T& vector<T>::back()
	{
		assert(this->_size != 0);
		return this->_data[this->_size - 1];
	}

	template <typename T>
	const T& vector<T>::back() const
	{
		return const_cast<vector<T>&>(*this).back();
	}

}
