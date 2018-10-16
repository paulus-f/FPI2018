#pragma once
#include "Log.h"
#define ID_MAXSIZE 5 
#define SIZEBUFFDEC 6
#define TI_MAXSIZE 1024
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define INT_NULL 0xffffffff
#define STR_NULL ??????????
#define TI_STR_MAXSIZE 255


namespace LT {
	struct Entry;
	struct LexTable;
}

namespace IT
{
	enum IDDATATYPE {INT = 1, STR = 2};
	enum IDTYPE {V = 1, F = 2, L = 3, P = 4};

	struct Entry 
	{
		int idxfirstLE;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype;
		IDTYPE idtype;
		union 
		{
			int vint; 
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];
			} vstr[TI_STR_MAXSIZE];
		}value;
	};

	struct IdTable
	{
		int maxsize;
		int size;
		int head = 0;
		Entry* table;
	};

	void addFun(IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType);

	void addVarOrPar(IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType, bool flagPar, int Cul, int Num);

	bool isFun(IdTable  &idTable, LT::Entry lexEntry);

	IdTable Create(
		int size
	);

	void Add(
		IdTable& idtable,
		Entry entry
	);

	Entry GetEntry(
		IdTable& idtable,
		int n
	);

	int IsId(
		IdTable& idTable, LT::LexTable &lexTable,
		char id[ID_MAXSIZE]
	);
	void logIT(IdTable& idTable, Log::LOG log);

	void Delete(IdTable &idtable);
}
