#pragma once
#include <iostream>
#include "Operators.h"

template<typename T>
class ScalarProduct;

template <typename Left, typename Op, typename Right, typename T>
struct Oesch
{
	Left m_left;
	Right m_right;

	Oesch( Left t1, Right t2) : m_left(t1), m_right(t2) { }

	T operator[](int i)
	{
		return Op::apply( m_left[i], m_right[i] );
	}
	
	template<class RightSide>
	Oesch<Oesch<Left,Op,Right,T>,Plus<T>,RightSide,T> operator+(RightSide r)
	{
		return Oesch<Oesch<Left,Op,Right,T>,Plus<T>,RightSide,T>(*this,r);
	}

	template<class RightSide>
	Oesch<Oesch<Left,Op,Right,T>,Minus<T>,RightSide,T> operator-(RightSide r)
	{
		return Oesch<Oesch<Left,Op,Right,T>,Minus<T>,RightSide,T>(*this,r);
	}

	template<class LeftSide>
	friend Oesch<ScalarFactor<LeftSide>,Mult<T>,Oesch<Left,Op,Right,T>,T> operator*(LeftSide left,Oesch<Left,Op,Right,T> right)
	{
		return Oesch<ScalarFactor<LeftSide>,Mult<T>,Oesch<Left,Op,Right,T>,T>(ScalarFactor<LeftSide>(left),right);
	}	 
};

template<typename T>
class Vector
{
	T *m_data;
	int m_N;

public:
	Vector(T *data,int size): m_data(data),m_N(size) {}
	Vector(const Vector &v):m_data(v.m_data),m_N(v.m_N) {}
	~Vector(void)
	{
		using namespace std;
		m_data = nullptr;
		cout << "Destructor called" << endl;
	}

	int Size()
	{
		return m_N;
	}
	
	T operator[](int i)
	{
		return m_data[i];
	}
	
	// assign an expression to the array
	template <typename Left, typename Op, typename Right>
	void operator=( Oesch<Left,Op,Right, T> fabio)
	{
		for ( int i = 0; i < m_N; ++i)
			m_data[i] = fabio[i];
	}
	
	template <class Right>
	Oesch<Vector<T>, Plus<T>, Right, T> operator+(Right r)
	{
		return Oesch<Vector<T>, Plus<T>, Right, T>(*this,r);
	}

	template <class Right>
	Oesch<Vector<T>, Minus<T>, Right, T> operator-(Right r)
	{
		return Oesch<Vector<T>, Minus<T>, Right, T>(*this,r);
	}

	template <typename D>
	Oesch<Vector<T>, Mult<T>,ScalarFactor<D>, T> operator*(D r)
	{
		return Oesch<Vector<T>, Mult<T>,ScalarFactor<D>, T>(*this,ScalarFactor<D>(r));
	}

	template <class C,class D>
	friend Oesch<ScalarFactor<C>, Mult<D>,Vector<D>, D> operator*(C left,Vector<D> right)
	{
		return Oesch<ScalarFactor<C>, Mult<D>,Vector<D>, D>(ScalarFactor<C>(left),right);
	}

	template<typename E>
	T operator*(ScalarProduct<E> r)
	{
		return (ScalarProduct<T>(*this) * r);
	}

	ScalarProduct<T> operator*() const
	{
		return ScalarProduct<T>(*this);
	}

	void print() const 
	{
		using namespace std;
		int l = 0; 
		cout << '[';
		
		if (m_N > 0) 
		{
			cout << m_data[l++];
			while(l < m_N) 
				cout << ',' << m_data[l++];
		}
		cout << ']' << endl;	
	}
};


