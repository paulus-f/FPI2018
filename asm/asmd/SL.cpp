#include "stdafx.h"
extern "C"
{
	int __stdcall getmax(int * arr, int size)
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

	int __stdcall getmin(int * arr, int size)
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
}