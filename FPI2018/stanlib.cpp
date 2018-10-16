#include "stdafx.h"
#include "LT.h"
#include "Error.h"

namespace  SL
{
	bool funStrlen(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine)
	{
		bool flagParametr = false;
		LT::Entry lexEntry;
		int findId = IT::IsId(idTable, lexTable, buff);
		if (findId == TI_NULLIDX)
		{
			// if str is not init 
			lexEntry = LT::retLex(LEX_ID, numLine, idTable.head);
			flagParametr = true;
			IT::addFun(idTable, lexTable, lexEntry, buff, buffType);
		}
		else
		{
			switch (idTable.table[findId].idtype)
			{
			case IT::V:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::F:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::L:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::P:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			default: throw ERROR_THROW(999);
			}
		}
		return flagParametr;
	}
	
	bool funSubstr(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, char* buffType, int numLine)
	{
		bool flagParametr = false;
		LT::Entry lexEntry;
		int findId = IT::IsId(idTable, lexTable, buff);
		if (findId == TI_NULLIDX)
		{
			// if str is not init 
			lexEntry = LT::retLex(LEX_ID, numLine, idTable.head);
			flagParametr = true;
			IT::addFun(idTable, lexTable, lexEntry, buff, buffType);
		}
		else
		{
			switch (idTable.table[findId].idtype)
			{
			case IT::V:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::F:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::L:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			case IT::P:
				lexEntry = LT::retLex(LEX_ID, numLine, findId);
				LT::Add(lexTable, lexEntry);
				break;
			default: throw ERROR_THROW(999);
			}
		}
		return flagParametr;
	}
}
