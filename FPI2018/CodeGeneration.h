#pragma once
#include "LT.h"
#include "IT.h"
#include "Log.h"
#include <fstream>
#include "Error.h"
#include <vector>
namespace CG
{
	enum typeBlock
	{
		w = 1,
		ut = 2,
		f = 3,
		i = 4,
		ul = 5,
		a = 6
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

	bool isStanLib(char *nameid);
	void StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void addLiterals(IT::IdTable& idTable, Log::LOG log );
	void addData(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	void protImplem(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	int  releaseFun(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int pos, char *idfun);
	void jumpfun(LT::CO co, std::string strlable, Log::LOG log);
	void cmpfun(IT::Entry le, IT::Entry re, char* idname1, char* idname2, LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log);
	int  doExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int numLT, char* idname1, char* idname2, Log::LOG log);

}