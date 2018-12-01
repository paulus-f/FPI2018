#pragma once
#include "Log.h"

#define ID_MAXSIZE 255 
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
	enum IDDATATYPE { INT = 1, STR = 2, FL = 3, BL = 4 };
	enum IDTYPE {V = 1, F = 2, L = 3, P = 4};
	enum SCOPE { G = 1, LF = 2, LB = 3, FUN = 4, LIT = 5, ERROR = 6};

	struct Entry 
	{
		int idxfirstLE;
		int countlex = -1;
		char id[ID_MAXSIZE];
		IDDATATYPE iddatatype; // тип данных в ИД 
		IDTYPE idtype; // тип ИД
		SCOPE scope; // область видимости
		union 
		{
			struct
			{
				int len;
				char str[TI_STR_MAXSIZE];
			}vstr; // значение строки

			float vfl; // значение float
			bool vbool; // значение bool
			int vint; // значение int 
		}value;
	};


	struct IdTable
	{
		int maxsize;
		int size;
		int head = 0;
		Entry* table;
	};

	//void retIDlit(IdTable &idTable, LT::LexTable &lexTable, int numLT, char* out);
	void retIDlit(IT::Entry &idTable, char* out);
	void addFun(IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType);
	int getAmountPar(IdTable &idTable, int num);
	void addVarOrPar(IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType, bool flagPar, int Cul, int Num);
	bool isFun(IdTable  &idTable, LT::Entry lexEntry);
	int getIDLIT(IdTable &idtable, IDDATATYPE type, IT::Entry itentry);
	void retIDwithScope(IdTable &idTable, LT::LexTable& lexTable, int numLT, char* out);
	void retNameFun(IdTable &idTable, LT::LexTable& lexTable, int numLT, char* out);


	bool isExist(LT::LexTable& LtTable, IdTable& idTable, char* buff);


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

	SCOPE retScope(LT::LexTable lexTable, bool global);

	void Delete(IdTable &idtable);
}
