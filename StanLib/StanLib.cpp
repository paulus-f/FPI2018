// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// StanLib.pch будет использоваться в качестве предкомпилированного заголовка
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"
#include <iostream>
#include <math.h>

extern "C"
{
	char* _stdcall inputfpi(char * str)
	{
		setlocale(LC_ALL, "Russian");
		std::cin >> str;
		return str;
	}

	void _stdcall outputstrfpi(char * str)
	{
		setlocale(LC_ALL, "Russian");
		std::cout << str << std::endl;
	}

	void _stdcall outputflfpi(float flnum)
	{
		std::cout << flnum << std::endl;
	}

	void _stdcall outputintfpi(int intnum)
	{
		std::cout << intnum << std::endl;
	}

	int _stdcall strlenfpi(char *string)
	{
		return strlen(string);
	}

	int _stdcall strfind(char *string, char *substring)
	{	
		char *ptrstrstr = strstr(string, substring);
		if (ptrstrstr == NULL) return -1;
		return strlen(string)-strlen(ptrstrstr)-1;
	}

	float _stdcall msin(float num)
	{
		return sin(num);
	}

	float _stdcall mcos(float num)
	{
		return cos(num);
	}

	float _stdcall mtan(float num)
	{
		return tan(num);
	}

	float _stdcall mctan(float num)
	{
		return 1 / tan(num);
	}

	float _stdcall mln(float num)
	{
		return log(num);
	}

	int _stdcall mabs(int num)
	{
		if (num >= 0) return num;
		if (num < 0) return -num;
		return num;
	}

	float _stdcall msqr(int num)
	{
		return sqrt(num);
	}
}
