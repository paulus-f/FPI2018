#include "stdafx.h"
#include "SemanticAnalysis.h"

bool Semantic::startSemantic(LT::LexTable lexTable, IT::IdTable idTable, Log::LOG log)
{
	bool errorSem = false;
	Error::ERROR errarr[100];
	int errhead = 0;

	for (int i = 0; i < lexTable.head; i++)
	{
		switch (lexTable.table[i].lexema[GETLEX])
		{
		case LEX_ID:
			switch (idTable.table[lexTable.table[i].idxTI].idtype)
			{
			case IT::IDTYPE::F:
				if (!Semantic::checkFun(i, lexTable, idTable))
				{
					errorSem = true;
					errarr[errhead++] = ERROR_THROW_IN(705, lexTable.table[i].sn, -1);
				}
				break;
			case IT::IDTYPE::V:
				if (!Semantic::checkId(i, lexTable, idTable));
				{
					errorSem = true;
					errarr[errhead++] = ERROR_THROW_IN(703, lexTable.table[i].sn, -1);
				}
				break;
			case IT::IDTYPE::P:
				if (!Semantic::checkId(i, lexTable, idTable));
				{
					errorSem = true;
					errarr[errhead++] = ERROR_THROW_IN(703, lexTable.table[i].sn, -1);
				}
				break;
			}
			break;
		case LEX_BRANCH: 
			if (!Semantic::checkBranch(i, lexTable, idTable));
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_CYCLE: 
			if (!Semantic::checkCycle(i, lexTable, idTable));
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_FOR: 
			if (!Semantic::checkCycle(i, lexTable, idTable));
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_FUNCTION: 
			if (!Semantic::checkSegFun(i, lexTable, idTable));
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(702, lexTable.table[i].sn, -1);
			}
			break;
		}
	}

	if (errorSem)
	{
		throw Error::getarrayerror(errarr, log, 700, errhead);
		return false;
	}
	else
	{
		return true;
	}
}
///////////////////////////////////////////////////////////////////////////////
bool Semantic::checkId(int numIT, LT::LexTable lexTable, IT::IdTable idTable)
{
	return false;
}
///////////////////////////////////////////////////////////////////////////////
bool Semantic::checkFun(int numIT, LT::LexTable lexTable, IT::IdTable idTable)
{
	return false;
}
/////////////////////////////////////////////////////////////////////////////////
bool Semantic::checkSegFun(int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	IT::IDDATATYPE typefun = idTable.table[lexTable.table[numLT + 1].idxTI].iddatatype;
	for (int i = numLT; lexTable.table[i].lexema[GETLEX] != LEX_MAIN || lexTable.table[i].lexema[GETLEX] != LEX_FUNCTION;i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_RETURN)
		{
			int j = i;
			for (j = i; lexTable.table[i].lexema[GETLEX] != LEX_SEMICOLON; j++)
			{
				if (lexTable.table[i].lexema[GETLEX] == LEX_ID || lexTable.table[i].lexema[GETLEX] == LEX_LITERAL)
				{
					if (!(idTable.table[lexTable.table[i].lexema[GETLEX]].iddatatype == typefun))
						return false;
				}
			}
			i = j;
		}
		if (i + 1 == lexTable.head)
		{
			return false;
		}
	}
	return true;
}

bool Semantic::checkBranch(int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	if (idTable.table[lexTable.table[numLT + 2].idxTI].iddatatype == idTable.table[lexTable.table[numLT + 4].idxTI].iddatatype) return true;
	else return false;
}

bool Semantic::checkCycle(int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	if (lexTable.table[numLT].lexema[GETLEX] == LEX_CYCLE)
	{
		if (idTable.table[lexTable.table[numLT + 2].idxTI].iddatatype == idTable.table[lexTable.table[numLT + 4].idxTI].iddatatype) return true;
		else return false;
	}
	else
	{
		if (idTable.table[lexTable.table[numLT + 6].idxTI].iddatatype == idTable.table[lexTable.table[numLT + 8].idxTI].iddatatype) return true;
		else return false;
	}
}
