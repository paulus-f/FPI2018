#include "stdafx.h"
#include "IT.h"
#include "Error.h"
#include <iostream>
#include "LT.h"
#include <iomanip>
#include <sstream>
#include <fstream>

namespace IT {
	int getIDLIT(IT::IdTable& idtable, IDDATATYPE type, IT::Entry itentry)
	{
		for (int i = 0, j =0; i < idtable.head; i++)
		{
			if (!strcmp(idtable.table[i].id, itentry.id)) return j;
			if (idtable.table[i].iddatatype ==  itentry.iddatatype && idtable.table[i].idtype == IDTYPE::L) j++;
		}
		return -1;
	}

	void retIDwithScope(IdTable& idTable, LT::LexTable& lexTable, int numLT, char *out)
	{
		
		if (numLT < lexTable.head)
		{
			int i = lexTable.table[numLT].idxTI;

			if (idTable.table[i].scope == SCOPE::G) strcpy(out, idTable.table[i].id);
			else if (idTable.table[i].scope == SCOPE::LB)
			{
				for (int j = i; j >= 0; j--)
				{
					if (lexTable.table[idTable.table[j].idxfirstLE - 1].lexema[GETLEX] == LEX_FUNCTION || lexTable.table[idTable.table[j].idxfirstLE].lexema[GETLEX] == LEX_MAIN)
					{
						char buff[300];
						strcpy(buff, "lb_foo__");
						strcat(buff, idTable.table[j].id);
						strcat(buff, idTable.table[i].id);
						strcpy(out, buff);
						return;
					}
				}
			}
			else
			{
				for (int j = i; j >= 0; j--)
				{
					if (lexTable.table[idTable.table[j].idxfirstLE - 1].lexema[GETLEX] == LEX_FUNCTION || lexTable.table[idTable.table[j].idxfirstLE].lexema[GETLEX] == LEX_MAIN)
					{
						char buff[300];
						strcpy(buff, "foo__");
						strcat(buff, idTable.table[j].id);
						strcat(buff, idTable.table[i].id);
						strcpy(out, buff);
						return;
					}
				}
			}
		}		
	}
	void retNameFun(IdTable & idTable, LT::LexTable & lexTable, int numLT, char * out)
	{
		strcpy(out, "foo__");
		strcat(out, idTable.table[lexTable.table[numLT].idxTI].id);
	}
	void retIDlit(IT::Entry &idTable, char* out)
	{

		char buffnum[30];
		char bufftype[30];;

		switch (idTable.iddatatype)
		{
		case IDDATATYPE::FL:
			strcpy(bufftype, "FLLIT");
			_itoa(idTable.countlex, buffnum, 10);
			strcat(bufftype, buffnum);
			strcpy(out, bufftype);
			return;
		case IDDATATYPE::BL:
			strcpy(bufftype, "BLLIT");
			_itoa(idTable.countlex, buffnum, 10);
			strcat(bufftype, buffnum);
			strcpy(out, bufftype);
			return;
		case IDDATATYPE::INT:
			strcpy(bufftype, "INTLIT");
			_itoa(idTable.countlex, buffnum, 10);
			strcat(bufftype, buffnum);
			strcpy(out, bufftype);
			return;
		case IDDATATYPE::STR:
			strcpy(bufftype, "STRLIT");
			_itoa(idTable.countlex, buffnum, 10);
			strcat(bufftype, buffnum);
			strcpy(out, bufftype);
			return;
		}
	}
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

	int getAmountPar(IdTable & idTable, int num)
	{
		int count = 0;
		for (int i = num+1;; i++)
		{
			if (idTable.table[i].idtype == IT::P) count++;
			if (idTable.table[i].idtype != IT::P) break;
		}
		return count;
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
		indType.idxfirstLE = lexTable.head - 1;
		if (!strcmp(buffType, INTEGER))
		{
			indType.iddatatype = IT::INT;
			indType.value.vint = 0;
		}
		else if (!strcmp(buffType, STRING))
		{
			indType.iddatatype = IT::STR;
			indType.value.vstr.str[0] = '\0';
			indType.value.vstr.len = 0;
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
		if (isExist(lexTable, idTable, buff) && indType.idtype != IT::P) throw ERROR_THROW_IN(108, Cul, Num);
		indType.scope = IT::retScope(lexTable, checkGlobal);
		IT::Add(idTable, indType);
	}
	
	bool IT::isExist(LT::LexTable& LtTable, IdTable& idTable, char* buff)
	{
		bool isGlobal = false;
		if (buff[0] == '$') isGlobal = true;
		for (int i = idTable.head-1; i >= 0; i--)
		{
			if (!isGlobal && (LtTable.table[idTable.table[i].idxfirstLE-1].lexema[GETLEX] == 'f' || LtTable.table[idTable.table[i].idxfirstLE].lexema[GETLEX] == 'm')) return false;
			if (!strcmp(idTable.table[i].id, buff)) return true;
		}
		return false;
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

	IT::SCOPE retScope(LT::LexTable lexTable, bool isGlobal)
	{
		if (isGlobal)
		{
			return SCOPE::G;
		}

		bool leftbr = false;

		for (int i = lexTable.head; i >= 0; --i)
		{
			if (lexTable.table[i].lexema[GETLEX] == LEFTBRACET) leftbr = true;
			if (lexTable.table[i].lexema[GETLEX] == RIGHTBRACELET)
			{
				i = breakBlock(lexTable, i-1) - 1;
				if (lexTable.table[i+1].lexema[GETLEX] == LEX_ALIAS) i++;
			}
			if (leftbr && (lexTable.table[i].lexema[GETLEX] == LEX_FOR || lexTable.table[i].lexema[GETLEX] == LEX_ALIAS || lexTable.table[i].lexema[GETLEX] == LEX_BRANCH || lexTable.table[i].lexema[GETLEX] == LEX_CYCLE))
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

	int IT::IsId(IdTable  &idTable, LT::LexTable &lexTable, char *id)
	{
		bool exit = false;
		bool isFun = false;
		int posI;
		
		// check fun and gl
		for (int i = 0; i < idTable.head; i++)
		{
			if (lexTable.table[idTable.table[i].idxfirstLE].lexema[GETLEX] == 'm') break;
			
			if (id[0] == '$' && !strcmp(idTable.table[i].id, id))
			{
				posI = i;
				isFun = true;
				exit = true;
				break;
			}
			if (idTable.table[i].idtype == IDTYPE::F && !strcmp(idTable.table[i].id, id))
			{
				posI = i;
				isFun = true;
				exit = true;
				break;
			}
		}
		if (!isFun)
		{
			for (int i = idTable.head - 1; i >= 0; i--)
			{
				if (lexTable.table[idTable.table[i].idxfirstLE - 1].lexema[GETLEX] == 'f' || lexTable.table[idTable.table[i].idxfirstLE].lexema[GETLEX] == 'm') break;
				if (!strcmp(idTable.table[i].id, id))
				{
					if (idTable.table[i].idtype == IDTYPE::F) continue;
					posI = i;
					exit = true;
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

		*log.stream << "������� ���������������" << std::endl;
		*log.stream << std::setfill('-') << std::setw(120) << '-' << std::endl;
		*log.stream << "   �" << " | " << "�������������" << " | " << "��� ������" << " | " << "��� ��������������" << " | " <<"������ � ��" << " | " << " ������� ���������  " << " | " << "��������    " << std::endl;
		*log.stream << std::setw(120) << '-' << std::endl;
		for (i = 0; i < idTable.head; i++)
		{
			*log.stream << std::setfill('0') << std::setw(4) << std::right << i << " | ";
			*log.stream << std::setfill(' ') << std::setw(13) << std::left << idTable.table[i].id << " | ";
			switch (idTable.table[i].iddatatype)
			{
			case INT: *log.stream << std::setw(10) << std::left;
				*log.stream << "integer" << " | "; break;
			case FL: *log.stream << std::setw(10) << std::left;
				*log.stream << "float" << " | "; break;
			case BL: *log.stream << std::setw(10) << std::left;
				*log.stream << "bool" << " | "; break;
			case STR: *log.stream << std::setw(10) << std::left;
				*log.stream << "string" << " | "; break;
			default: *log.stream << std::setw(10) << std::left << "unknown" << " | "; break;
			}
			switch (idTable.table[i].idtype)
			{
			case V: *log.stream << std::setw(18) << std::left << "����������" << " | "; break;
			case F: *log.stream << std::setw(18) << std::left << "�������" << " | "; break;
			case P: *log.stream << std::setw(18) << std::left << "��������" << " | "; break;
			case L: *log.stream << std::setw(18) << std::left << "�������" << " | "; break;
				numberOP++;
				break;
			default: *log.stream << std::setw(18) << std::left << "unknown" << " | "; break;
			}
			*log.stream << std::setw(11) << std::left << idTable.table[i].idxfirstLE << " | ";
			switch (idTable.table[i].scope)
			{
			case LF: *log.stream << std::setw(20) << std::left << "� ��������� �������" << " | "; break;
			case G: *log.stream << std::setw(20) << std::left << "����������" << " | "; break;
			case LB: *log.stream << std::setw(20) << std::left << "� �����" << " | "; break;
			case FUN: *log.stream << std::setw(20) << std::left << "-" << " | "; break;
			case LIT: *log.stream << std::setw(20) << std::left << "-" << " | "; break;
				break;
			default: *log.stream << std::setw(20) << std::left << "unknown" << " | "; break;
			}
			//std::cout << std::setw(11) << std::left << idTable.table[i].idxfirstLE << " | ";
			if (idTable.table[i].iddatatype == INT && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				*log.stream << std::setw(18) << std::left << idTable.table[i].value.vint;
			else if (idTable.table[i].iddatatype == STR && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				*log.stream << "[" << (int)idTable.table[i].value.vstr.len << "] \"" << idTable.table[i].value.vstr.str << "\"";
			else if (idTable.table[i].iddatatype == FL && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				*log.stream << std::setw(18) << std::left << idTable.table[i].value.vfl;
			else if (idTable.table[i].iddatatype == BL && (idTable.table[i].idtype == V || idTable.table[i].idtype == L))
				*log.stream << std::setw(18) << std::left << idTable.table[i].value.vbool;
			else
				*log.stream << "-";
			*log.stream << std::endl;
		}
		*log.stream << std::setfill('-') << std::setw(120) << '-' << std::endl;
		*log.stream << "���������� ���������������: " << i - numberOP << std::endl;
		*log.stream << std::setw(120) << '-' << std::endl;
	}

	void IT::Delete(IdTable & idtable)
	{
		delete idtable.table;
	}
}