// Uebung.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Vector.h"
#include "Operators.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int k = 5;
	double l = 3.14;

	double a_data[] = { 2, 3, 5, 9 };
	double b_data[] = { 1, 0, 0, 1 };
	double c_data[] = { 3, 0, 2, 5 };
	double d_data[4];
	Vector<double> A(a_data,4);
	Vector<double> B(b_data,4);
	Vector<double> C(c_data,4);
	Vector<double> D(d_data,4);

	D = A + (B + C) - A;
	D.print();

	D = A - B - C;
	D.print();

	D = k*(A+B);
	D = A*k;
	D.print();

	double x = A**B;
	
	return 0;
}

