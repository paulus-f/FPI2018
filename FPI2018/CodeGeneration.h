#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include <fstream>
#include <vector>
namespace CG
{
	enum typeBlock
	{
		w = 1,
		ut = 2,
		f = 3,
		i = 4,
		ul = 5
	};

	struct LabelStructFPI
	{
		std::string _namestruct;
		int _posstruct;
		typeBlock _tbstruct;

		LabelStructFPI(){};

		LabelStructFPI(std::string name, int pos, typeBlock tb)
		{
			_namestruct = name;
			_posstruct = pos;
			_tbstruct = tb;
		}
	};

	void StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void addLiterals(IT::IdTable& idTable, Log::LOG log );
	void addData(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void protImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	int  releaseFun(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int pos, char *idfun);
	////void mainImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int numMain, char *idfun);
	//*int isExpression(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//int isInit(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//int branchIf(LT::LexTable& lexTable, IT::IdTable& idTable, int num, char *idfun);
	//int branchUnless(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//int cycleWhile(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//int cycleUntil(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//int cycleFor(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
	//*/int genProce(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun);
}