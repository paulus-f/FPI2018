#pragma once
#include "LT.h"
#include "IT.h"
namespace SL {
	//enum IDDATATYPE { INT = 1, STR = 2, FL = 3, BL = 4 };
	struct parmFun
	{
		int trigonmetry[1] = { 3 };
		int mln[1] = { 3 };
		int msqr[1] = { 1 };
		int mabs[1] = { 1 };
		int strlen[1] = { 2 };
		int srtfind[2] = { 2 , 2 };
	};

	bool funStandLib(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, int numLine);
}

