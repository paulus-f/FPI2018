#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include <fstream>

namespace CG
{
	void StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void branchIf(LT::LexTable& lexTable, IT::IdTable& idTable, int num, char *idfun);
	void addLiterals(IT::IdTable& idTable, Log::LOG log );
	void addData(IT::IdTable& idTable, Log::LOG log);
	int  protImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	int  releaseFun(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int pos, char *idfun);
	void mainImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int numMain, char *idfun);
	void isExpression(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void isInit(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void branchUnless(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void cycleWhile(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void cycleUntil(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void cycleFor(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	void genProce(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
}