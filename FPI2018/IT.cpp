#include "stdafx.h"
#include "IT.h"
#include "Error.h"
#include <iostream>
#include "LT.h"
#include <iomanip>
namespace IT {
	void addFun(IT::IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType)
	{
		LT::Add(lexTable, lexEntry);
		IT::Entry indFun;
		indFun.idtype = IT::F;
		indFun.idxfirstLE = lexTable.head;
		strcpy(indFun.id, buff);
		if (!strcmp(buffType, INTEGER))
		{
			indFun.iddatatype = IT::INT;
		}
		else if (!strcmp(buffType, STRING))
		{
			indFun.iddatatype = IT::STR;
		}
		else
		{
			throw ERROR_THROW(999);
		}
		IT::Add(idTable, indFun);
	}

	void addVarOrPar(IT::IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType, bool flagPar, int Cul, int Num)
	{
		IT::Entry indType;
		LT::Add(lexTable, lexEntry);
		strcpy(indType.id, buff);
		if (flagPar)
		{
			indType.idtype = IT::P;
		}
		else
		{
			indType.idtype = IT::V;
		}
		indType.idxfirstLE = lexTable.head;
		if (!strcmp(buffType, INTEGER))
		{
			indType.iddatatype = IT::INT;
			indType.value.vint = 0;
		}
		else if (!strcmp(buffType, STRING))
		{
			indType.iddatatype = IT::STR;
			indType.value.vstr->str[0] = '\0';
			indType.value.vstr->len = 0;
		}
		else
		{
			throw ERROR_THROW_IN(117, Num, Cul);
		}
		IT::Add(idTable, indType);
	}

	IT::IdTable IT::Create(int size)
	{
		IdTable *tempIdTemp = new IdTable;
		tempIdTemp->size = size;
		tempIdTemp->maxsize = TI_MAXSIZE;
		tempIdTemp->table = new Entry[size];
		return *tempIdTemp;
	}

	void IT::Add(IdTable& idtable, Entry entry)
	{
		if (entry.idxfirstLE < idtable.size)
		{
			idtable.table[idtable.head++] = entry;
		}
		else
		{
			throw ERROR_THROW(999); // error
		}
	}

	IT::Entry IT::GetEntry(IdTable & idtable, int n)
	{
		if (n < idtable.size)
		{
			return idtable.table[n - 1];
		}
		else
		{
			throw ERROR_THROW(999); // error
		}
	}

	bool isFun(IdTable  &idTable, LT::Entry lexEntry)
	{
		if (lexEntry.idxTI == -1) return false;
		return idTable.table[lexEntry.idxTI].idtype == IT::F ? true : false;
	}

	int IT::IsId(IdTable  &idTable, LT::LexTable &lexTable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < lexTable.head; i++) // searching ind fun
		{
			if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
			{
				int numIdTable = lexTable.table[i].idxTI;
				if (!strcmp(idTable.table[numIdTable].id, id) && idTable.table[numIdTable].idtype == IT::F)
				{
					return numIdTable;
				}
			}
		}

		for (int j = lexTable.head - 1; j != 0; j--) // searching ind fun
		{
			if (lexTable.table[j].lexema[GETLEX] == LEX_FUNCTION || lexTable.table[j].lexema[GETLEX] == LEX_MAIN)
			{
				break;
			}
			if (lexTable.table[j].lexema[GETLEX] == LEX_ID)
			{
				for (int i = 0; i < idTable.head; i++)
				{
					if (!strcmp(idTable.table[i].id, id) && lexTable.table[j].idxTI == i)
					{
						return i;
					}
				}
			}
		}
		return TI_NULLIDX; // ret -1 when var is not init in space of declar 
	}

	void IT::logIT(IdTable& idTable, Log::LOG log)
	{
		int i, numberOP = 0;
		std::cout << std::endl;
		std::cout << std::setfill('-') << std::setw(87) << '-' << std::endl;
		std::cout << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << std::endl;
		std::cout << std::setw(87) << '-' << std::endl;
		for (i = 0; i < idTable.head; i++)
		{
			std::cout << std::setfill('0') << std::setw(4) << std::right << i << " | ";
			std::cout << std::setfill(' ') << std::setw(13) << std::left << idTable.table[i].id << " | ";
			switch (idTable.table[i].iddatatype)
			{
			case INT: std::cout << std::setw(10) << std::left;
				std::cout << "integer" << " | "; break;
			case STR: std::cout << std::setw(10) << std::left;
				std::cout << "string" << " | "; break;
			default: std::cout << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idTable.table[i].idtype)
			{
			case V: std::cout << std::setw(18) << std::left << "переменная" << " | "; break;
			case F: std::cout << std::setw(18) << std::left << "функция" << " | "; break;
			case P: std::cout << std::setw(18) << std::left << "параметр" << " | "; break;
			case L: std::cout << std::setw(18) << std::left << "литерал" << " | "; break;
				numberOP++;
				break;
			default: std::cout << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			std::cout << std::setw(11) << std::left << idTable.table[i].idxfirstLE << " | ";
			if (idTable.table[i].iddatatype == INT && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idTable.table[i].value.vint;
			else if (idTable.table[i].iddatatype == STR && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << "[" << (int)idTable.table[i].value.vstr->len << "] \"" << idTable.table[i].value.vstr->str << "\"";
			else
				std::cout << "-";
			std::cout << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(87) << '-' << std::endl;
		std::cout << "Количество идентификаторов: " << i - numberOP << std::endl;
		std::cout << std::setw(87) << '-' << std::endl;
	}

	void IT::Delete(IdTable & idtable)
	{
		delete idtable.table;
	}
}