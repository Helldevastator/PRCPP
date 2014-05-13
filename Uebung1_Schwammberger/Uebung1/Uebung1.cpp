// Uebung1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyString.h"
#include <stdio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	String s0("abc");
	String s1("abd");
	s0.compareTo(s1);
	return 0;
}

