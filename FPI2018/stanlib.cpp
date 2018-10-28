#include "stdafx.h"
#include "LT.h"
#include "Error.h"




namespace  SL
{

	bool funStandLib(LT::LexTable& lexTable, IT::IdTable& idTable, char* buff, int numLine)
	{
		std::string typeFun;
		bool flagParametr = false;
		LT::Entry lexEntry;
		lexEntry = LT::retLex(LEX_ID, numLine, idTable.head);
		flagParametr = true;
		if (!strcmp(buff, MLN) || !strcmp(buff, MSIN) || !strcmp(buff, MCOS) || !strcmp(buff, MTAN) || !strcmp(buff, MCTAN) || !strcmp(buff, MSQR))
		{
			typeFun = "fl";
		}
		if (!strcmp(buff,STRLEN) || !strcmp(buff, STRFIND) || !strcmp(buff,MABS))
		{
			typeFun = "int";
		}
		IT::addFun(idTable, lexTable, lexEntry, buff, (char*)typeFun.c_str());
		return flagParametr;
	}

}
