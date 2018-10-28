#include "stdafx.h"
#include "SemanticAnalysis.h"
#include "stanlib.h"
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
			if (lexTable.table[i+1].lexema[GETLEX] == LEX_EQUAL)
			{
				if (!checkType(i, lexTable, idTable))
				{
					errorSem = true;
					errarr[errhead++] = ERROR_THROW_IN(703, lexTable.table[i].sn, -1);
					break;
				}
			}
				
			if (lexTable.table[i - 1].lexema[GETLEX] == LEX_FUNCTION && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::F)
			{
				if (!Semantic::checkFun(i, lexTable, idTable))
				{
					errorSem = true;
					errarr[errhead++] = ERROR_THROW_IN(704, lexTable.table[i].sn, -1);
				}
			}
		break;
		case LEX_BRANCH: 
			if (!Semantic::checkBranch(i, lexTable, idTable))
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_CYCLE: 
			if (!Semantic::checkCycle(i, lexTable, idTable))
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_FOR: 
			if (!Semantic::checkCycle(i, lexTable, idTable))
			{
				errorSem = true;
				errarr[errhead++] = ERROR_THROW_IN(701, lexTable.table[i].sn, -1);
			}
			break;
		case LEX_FUNCTION: 
			if (!Semantic::checkSegFun(i, lexTable, idTable))
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
bool Semantic::checkFun(int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	IT::Entry itentry = IT::GetEntry(idTable, lexTable.table[numLT].idxTI);
	if (itentry.id == MLN    || itentry.id == MSIN    || itentry.id == MCOS || itentry.id == MTAN   || itentry.id == MCTAN)  
	{ 
		return checkStandlib(SL::parmFun().trigonmetry, numLT, lexTable, idTable)? true: false;
	}
	else if(itentry.id == MSQR) 
	{
		return checkStandlib(SL::parmFun().msqr, numLT, lexTable, idTable) ? true : false;
	}
	else if(itentry.id == STRLEN)
	{
		return checkStandlib(SL::parmFun().strlen, numLT, lexTable, idTable) ? true : false;
	}
	else if (itentry.id == STRFIND)
	{
		return checkStandlib(SL::parmFun().srtfind, numLT, lexTable, idTable) ? true : false;

	}
	else if (itentry.id == MABS)
	{
		return checkStandlib(SL::parmFun().mabs, numLT, lexTable, idTable) ? true : false;
	}
	else
	{
		int count = 0;
		int arrParm[10/*maxparm*/];
		//count the parameters
		for (int i = itentry.idxfirstLE; lexTable.table[i].lexema[GETLEX] != LEX_RIGHTHESIS ; i++)
		{
			if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
			{
				arrParm[count++] = idTable.table[lexTable.table[i].idxTI].iddatatype;
			}
			if (i >= lexTable.head) throw ERROR_THROW(999)// going out of the array
		}

		int *parmFun = new int[count];
		for (int i = 0; i < count; i++)
		{
			parmFun[i] = arrParm[i];
		}

		if (checkStandlib(SL::parmFun().mabs, numLT, lexTable, idTable))
		{
			delete parmFun;
			return true;
		}
		else
		{
			delete parmFun;
			return false;
		}
	}
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

bool Semantic::checkType(int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	IT::IDDATATYPE typeId = idTable.table[lexTable.table[numLT + 1].idxTI].iddatatype;
	for (int i = numLT; lexTable.table[i].lexema[GETLEX] != SEMICOLON; ++i)
	{
		if (typeId != idTable.table[lexTable.table[i].idxTI].iddatatype) return false;
		if (i >= lexTable.head) throw ERROR_THROW(999)// going out of the array
	}
	return true;
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

bool Semantic::checkStandlib(int type[], int numLT, LT::LexTable lexTable, IT::IdTable idTable)
{
	int countParm = 0;
	for (int i = numLT; lexTable.table[i].lexema[GETLEX] != RIGHTHESIS; i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
		{
			if (!IT::GetEntry(idTable, lexTable.table[i].idxTI).iddatatype == type[countParm++])
			{
				return false;
			}
		}
		if (countParm >= sizeof(type) / sizeof(int)) return false;
		if (i >= lexTable.head) throw ERROR_THROW(999)// going out of the array
	}
	return true;
}
