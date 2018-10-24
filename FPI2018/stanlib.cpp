#include "stdafx.h"
#include "LT.h"
#include "Error.h"

namespace  SL
{
	bool funStrlen(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine)
	{
		bool flagParametr = false;
		LT::Entry lexEntry; 
		lexEntry = LT::retLex(LEX_ID, numLine, idTable.head);
		flagParametr = true;
		IT::addFun(idTable, lexTable, lexEntry, buff, buffType);
		return flagParametr;
	}
	
	bool funSubstr(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine)
	{
		bool flagParametr = false;
		LT::Entry lexEntry;
		lexEntry = LT::retLex(LEX_ID, numLine, idTable.head);
		flagParametr = true;
		IT::addFun(idTable, lexTable, lexEntry, buff, buffType);
		return flagParametr;
	}
}
