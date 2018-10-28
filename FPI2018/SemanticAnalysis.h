#pragma once
#include "IT.h"
#include "LT.h"
#include "Error.h"
#include "Log.h"

namespace Semantic
{
	bool startSemantic(LT::LexTable lexTable, IT::IdTable idTable, Log::LOG log);
	bool checkId(int numIT, LT::LexTable lexTable, IT::IdTable idTable);
	bool checkFun(int numIT, LT::LexTable lexTable, IT::IdTable idTable);
	bool Semantic::checkSegFun(int numIT, LT::LexTable lexTable, IT::IdTable idTable);
	bool checkBranch(int numIT, LT::LexTable lexTable, IT::IdTable idTable);
	bool checkCycle(int numIT, LT::LexTable lexTable, IT::IdTable idTable);

}