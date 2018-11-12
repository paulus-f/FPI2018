#include "stdafx.h"
extern "C"
{
	int  getmax(int * arr, int size)
	{
		int max = arr[0];
		for (int i = 0; i < size; i++)
		{
			if (max <= arr[i])
			{
				max = arr[i];
			}
		}
		return max;
	}

	char input1()
	{
		char str[255];
		scanf("%s", &str, 255);
		return *str;
	}

	int  output1(char *str)
	{
		printf("%s", str);
		return -1;
	}

	int  getmin(int * arr, int size)
	{
		int min = arr[0];
		for (int i = 0; i < size; i++)
		{
			if (min >= arr[i])
			{
				min = arr[i];
			}
		}
		return min;
	}
};