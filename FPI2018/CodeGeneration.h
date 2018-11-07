#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include <fstream>

namespace CG
{
	void StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void branchIf(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void addLiterals(IT::IdTable& idTable, Log::LOG log);
	void addData(IT::IdTable& idTable, Log::LOG log);
	int  protImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void mainImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int numMain);
	void isExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void isInit(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void branchUnless(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void cycleWhile(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void cycleUntil(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void cycleFor(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
	void genProce(LT::LexTable& lexTable, IT::IdTable& idTable, int num);
}