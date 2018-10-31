#include "stdafx.h"
#include "IT.h"
#include "Error.h"
#include <iostream>
#include "LT.h"
#include <iomanip>
#include <sstream>

namespace IT {
	void addFun(IT::IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType)
	{
		LT::Add(lexTable, lexEntry);
		IT::Entry indFun;
		indFun.scope = IT::SCOPE::FUN;
		if (!strcmp(buffType, INTEGER))
		{
			indFun.iddatatype = IT::INT;
		}
		else if (!strcmp(buffType, STRING))
		{
			indFun.iddatatype = IT::STR;
		}
		else if (!strcmp(buffType, FLOAT))
		{
			indFun.iddatatype = IT::FL;
		}
		else if (!strcmp(buffType, BOOL))
		{
			indFun.iddatatype = IT::BL;
		}
		else
		{
			throw ERROR_THROW(999);
		}
		indFun.idxfirstLE = lexTable.head - 1;
		strcpy(indFun.id, buff);
		indFun.idtype = IDTYPE::F;
		IT::Add(idTable, indFun);
	}

	void addVarOrPar(IT::IdTable &idTable, LT::LexTable &lexTable, LT::Entry lexEntry, char* buff, char* buffType, bool flagPar, int Cul, int Num)
	{
		IT::Entry indType;
		bool checkGlobal;
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
		else if (!strcmp(buffType, FLOAT))
		{
			indType.iddatatype = IT::FL;
			std::istringstream ss("0.0");
			ss >> indType.value.vfl;
		}
		else if (!strcmp(buffType, BOOL))
		{
			indType.iddatatype = IT::BL;
			indType.value.vbool = false;
		}
		else
		{
			throw ERROR_THROW_IN(117, Num, Cul);
		}
		checkGlobal = buff[0] == '$' ? true : false;
		indType.scope = IT::retScope(lexTable, checkGlobal);
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
			return idtable.table[n];
		}
		else
		{
			throw ERROR_THROW(999); // error
		}
	}

	int breakBlock(LT::LexTable lexTable, int i)
	{
		int line = lexTable.table[i].sn;
		for (;; --i)
		{
			if (lexTable.table[i].lexema[GETLEX] == RIGHTBRACELET)
			{
				i = breakBlock(lexTable, i-1) - 1;
			}
			if (i == 0)
			{
				throw ERROR_THROW_IN(120, line, -1);
			}
			if (lexTable.table[i].lexema[GETLEX] == LEX_FOR || lexTable.table[i].lexema[GETLEX] == LEX_ALIAS || lexTable.table[i].lexema[GETLEX] == LEX_BRANCH || lexTable.table[i].lexema[GETLEX] == LEX_CYCLE) return i;
		}
		return i;
	}

	//int breakBlockLeft(LT::LexTable lexTable, int i)
	//{
	//	int line = lexTable.table[i].sn;
	//	for (;; --i)
	//	{
	//		if (lexTable.table[i].lexema[GETLEX] == LEFTBRACET)
	//		{
	//			i = breakBlockLeft(lexTable, i - 1) - 1;
	//		}
	//		if (i == 0)
	//		{
	//			throw ERROR_THROW_IN(120, line, -1);
	//		}
	//		if (lexTable.table[i].lexema[GETLEX] == LEX_FOR || lexTable.table[i].lexema[GETLEX] == LEX_ALIAS || lexTable.table[i].lexema[GETLEX] == LEX_BRANCH || lexTable.table[i].lexema[GETLEX] == LEX_CYCLE) return i;
	//	}
	//	return i;
	//}

	IT::SCOPE retScope(LT::LexTable lexTable, bool isGlobal)
	{
		if (isGlobal)
		{
			return SCOPE::G;
		}

		for (int i = lexTable.head; i != 0; --i)
		{
			if (lexTable.table[i].lexema[GETLEX] == RIGHTBRACELET)
			{
				i = breakBlock(lexTable, i-1) - 1;
			}
			/*if (lexTable.table[i].lexema[GETLEX] == LEX_FOR || lexTable.table[i].lexema[GETLEX] == LEX_BRANCH || lexTable.table[i].lexema[GETLEX] == LEX_CYCLE || lexTable.table[i].lexema[GETLEX] == LEX_ALIAS)
			{
				continue;
			}*/
			if (lexTable.table[i].lexema[GETLEX] == LEX_FOR || lexTable.table[i].lexema[GETLEX] == LEX_ALIAS || lexTable.table[i].lexema[GETLEX] == LEX_BRANCH || lexTable.table[i].lexema[GETLEX] == LEX_CYCLE)
			{
				return SCOPE::LB;
			}
			if (lexTable.table[i].lexema[GETLEX] == LEX_MAIN || lexTable.table[i].lexema[GETLEX] == LEX_FUNCTION)
			{
				return SCOPE::LF;
			}
		}
		return SCOPE::ERROR;
	}

	bool isFun(IdTable  &idTable, LT::Entry lexEntry)
	{
		if (lexEntry.idxTI == -1) return false;
		return idTable.table[lexEntry.idxTI].idtype == IT::F ? true : false;
	}

	int IT::IsId(IdTable  &idTable, LT::LexTable &lexTable, char id[ID_MAXSIZE])
	{
		int posI;
		bool exit = false;
		//for (int j = lexTable.head - 1; j != 0; j--) 
		for (int j = 0; j < lexTable.head ; j++)
		{
			if (lexTable.table[j].lexema[GETLEX] == LEX_ID)
			{
				for (int i = j; i >= 0; i--)
				{
					if (!strcmp(idTable.table[i].id, id) && lexTable.table[j].idxTI == i)
					{
						posI = i;
						exit = true;
						break;
					}
				}
				if (exit)
				{
					break;
				}
			}
		}
		if (exit)
		{
			switch (idTable.table[posI].scope)
			{
			case SCOPE::G:
				return posI;
				break;
			case SCOPE::LF:
				for (int j = lexTable.head - 1; j != 0; j--)
				{
					if (lexTable.table[j].lexema[GETLEX] == LEX_FUNCTION || lexTable.table[j].lexema[GETLEX] == LEX_MAIN)
					{
						break;
					}
					if (lexTable.table[j].lexema[GETLEX] == RIGHTBRACELET)
					{
						j = breakBlock(lexTable, j - 1) - 1;
					}
					if (lexTable.table[j].lexema[GETLEX] == LEX_ID)
					{
						for (int i = 0; i < idTable.head; i++)
						{
							if (!strcmp(idTable.table[i].id, id) && lexTable.table[j].idxTI == i && idTable.table[i].scope != SCOPE::LB)
							{
								return i;
								break;
							}
						}
					}
				}
				break;
			case SCOPE::LB:
				for (int j = lexTable.head - 1; j != 0; j--)
				{
					if (lexTable.table[j].lexema[GETLEX] == RIGHTBRACELET)
					{
						j = breakBlock(lexTable, j - 1) - 1;
					}
					if (lexTable.table[j].lexema[GETLEX] == LEX_FOR || lexTable.table[j].lexema[GETLEX] == LEX_ALIAS || lexTable.table[j].lexema[GETLEX] == LEX_CYCLE || lexTable.table[j].lexema[GETLEX] == LEX_BRANCH)
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
								break;
							}
						}
					}
				}
				break;
			case SCOPE::FUN:
				return posI;
				break;
			case SCOPE::ERROR:
			case SCOPE::LIT:
				break;
			}
		}
		return TI_NULLIDX; 
	}

	void IT::logIT(IdTable& idTable, Log::LOG log)
	{
		int i, numberOP = 0;
		std::cout << std::endl;
		std::cout << std::setfill('-') << std::setw(120) << '-' << std::endl;
		std::cout << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " <<"Индекс в ТЛ" << " | " << " Область видимости  " << " | " << "Значение    " << std::endl;
		std::cout << std::setw(120) << '-' << std::endl;
		for (i = 0; i < idTable.head; i++)
		{
			std::cout << std::setfill('0') << std::setw(4) << std::right << i << " | ";
			std::cout << std::setfill(' ') << std::setw(13) << std::left << idTable.table[i].id << " | ";
			switch (idTable.table[i].iddatatype)
			{
			case INT: std::cout << std::setw(10) << std::left;
				std::cout << "integer" << " | "; break;
			case FL: std::cout << std::setw(10) << std::left;
				 std::cout << "float" << " | "; break;
			case BL: std::cout << std::setw(10) << std::left;
				std::cout << "bool" << " | "; break;
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
			switch (idTable.table[i].scope)
			{
			case LF: std::cout << std::setw(20) << std::left << "В локальной функции" << " | "; break;
			case G: std::cout << std::setw(20) << std::left << "Глобальная" << " | "; break;
			case LB: std::cout << std::setw(20) << std::left << "В ветке" << " | "; break;
			case FUN: std::cout << std::setw(20) << std::left << "-" << " | "; break;
			case LIT: std::cout << std::setw(20) << std::left << "-" << " | "; break;
				break;
			default: std::cout << std::setw(20) << std::left << "unknown" << " | "; break;
			}
			//std::cout << std::setw(11) << std::left << idTable.table[i].idxfirstLE << " | ";
			if (idTable.table[i].iddatatype == INT && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idTable.table[i].value.vint;
			else if (idTable.table[i].iddatatype == STR && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << "[" << (int)idTable.table[i].value.vstr->len << "] \"" << idTable.table[i].value.vstr->str << "\"";
			else if (idTable.table[i].iddatatype == FL && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idTable.table[i].value.vfl;
			else if (idTable.table[i].iddatatype == BL && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				std::cout << std::setw(18) << std::left << idTable.table[i].value.vbool;
			else
				std::cout << "-";
			std::cout << std::endl;
		}
		std::cout << std::setfill('-') << std::setw(120) << '-' << std::endl;
		std::cout << "Количество идентификаторов: " << i - numberOP << std::endl;
		std::cout << std::setw(120) << '-' << std::endl;
	}

	void IT::Delete(IdTable & idtable)
	{
		delete idtable.table;
	}
}