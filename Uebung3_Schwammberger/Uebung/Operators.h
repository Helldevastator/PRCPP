#pragma once
template<typename T>
class ScalarFactor
{
	T m_data;
public:
	ScalarFactor(T data):m_data(data) {}

	T operator[] (int i)
	{
		return m_data;
	}
};

template<typename T>
class Vector;

template<typename T>
class ScalarProduct
{
	Vector<T> v;
public:
	ScalarProduct(const Vector<T> &c):v(c) {}	

	template<typename D>
	T operator* (ScalarProduct<D> right)
	{
		T sum = 0;
		for(int i = 0; i < v.Size();i++)
			sum += v[i]* right.v[i];

		return sum;
	}
};

template<typename T>
class Plus
{
public:
	static T apply(T Left, T Right)
	{
		return Left + Right;
	}
};

template<typename T>
class Minus
{
public:
	static T apply(T Left, T Right)
	{
		return Left - Right;
	}
};

template<typename T>
class Mult
{
public:
	static T apply(T Left, T Right)
	{
		return Left * Right;
	}
};
