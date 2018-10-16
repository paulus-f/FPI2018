#pragma once
#include "LT.h"
#include "IT.h"
namespace SL {
	bool funStrlen(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine);
	bool funSubstr(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine, int Cul, int Num);
}

