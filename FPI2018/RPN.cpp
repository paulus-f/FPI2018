#include "stdafx.h"
#include "LT.h"
#include <vector>
#include "Error.h"
#include <iostream>

namespace Polska
{
	int checkPrior(char sym)
	{
		switch (sym)
		{
		case LEFTHESIS: case RIGHTHESIS: return 1;
		case PLUS: case MINUS: return 2;
		case DIRSLASH: case STAR: return 3;
		default: return -1;
		}
	}

	bool PolishNotation(int posLexTable, LT::LexTable lexTable, IT::IdTable idTable)
	{
		std::vector<LT::Entry> vectOper;
		int count = 0;
		for (int i = posLexTable; lexTable.table[i].lexema[GETLEX] != SEMICOLON; ++i)
		{
			count++;
			if (i >= lexTable.head) ERROR_THROW(999)// going out of the array
		}

		LT::LexTable tempVarLexTable;
		tempVarLexTable.table = new LT::Entry[count];


		int countThesis = 0;
		for (int i = posLexTable, j = 0; lexTable.table[i].lexema[GETLEX] != SEMICOLON; ++i, ++j)
		{
			tempVarLexTable.table[j] = lexTable.table[i];
			if (tempVarLexTable.table[j].lexema[GETLEX] == LEFTHESIS) countThesis++;
			else if (tempVarLexTable.table[j].lexema[GETLEX] == RIGHTHESIS) countThesis--;
		}
		if (countThesis) return false;

		bool beginVar = true;
		int posLT = posLexTable;
		char valChar;

		for (int i = 0; i<count; i++)
		{
			valChar = tempVarLexTable.table[i].lexema[GETLEX];
			switch (tempVarLexTable.table[i].lexema[GETLEX]) 
			{
			case LEFTHESIS:
				vectOper.push_back(tempVarLexTable.table[i]);
				break;
			case RIGHTHESIS:
				while (vectOper.back().lexema[GETLEX] != LEFTHESIS)
				{
					lexTable.table[posLT++] = vectOper.back();
					vectOper.pop_back();
					//valChar = vectOper.back().lexema[GETLEX];
				}
				vectOper.pop_back();
				break;
			case LEX_OPERATION: 
				if(vectOper.empty() || vectOper[0].lexema[GETLEX] == LEFTHESIS)
				{
					vectOper.push_back(tempVarLexTable.table[i]);
				}
				else
				{
					while (!vectOper.empty() && checkPrior(vectOper.back().operation) >= checkPrior(tempVarLexTable.table[i].operation))
					{
						lexTable.table[posLT++] = vectOper.back();
						vectOper.pop_back();
					}
					vectOper.push_back(tempVarLexTable.table[i]);
				}
			break;
			case LEX_ID: case LEX_LITERAL: case EQUAL:
				if(IT::isFun(idTable, tempVarLexTable.table[i]))
				{
					LT::Entry entryFun = tempVarLexTable.table[i];
					entryFun.lexema[GETLEX] = '@';
					int cnt = 0;

					i++;
					while(tempVarLexTable.table[i].lexema[GETLEX] != RIGHTHESIS)
					{
						if(tempVarLexTable.table[i].lexema[GETLEX] == LEX_ID || tempVarLexTable.table[i].lexema[GETLEX] == LEX_LITERAL)
						{
							cnt++;
							lexTable.table[posLT++] = tempVarLexTable.table[i];
						}
						i++;
					}
					entryFun.amountArg = cnt;
					lexTable.table[posLT++] = entryFun;
				}
				else
				{
					lexTable.table[posLT++] = tempVarLexTable.table[i];
				}
				break;
			default: return false;
			}
			
			if (i + 1 == count)
			{
				while (!vectOper.empty())
				{
					if (vectOper.back().lexema[GETLEX] == LEFTHESIS || vectOper.back().lexema[GETLEX] == RIGHTHESIS)

						vectOper.pop_back();
					else 
					{
						lexTable.table[posLT++] = vectOper.back();
						vectOper.pop_back();
					}
				}
				break;
			}
		}

		for (int i = posLT; lexTable.table[i].lexema[GETLEX] != SEMICOLON; ++i)
		{
			lexTable.table[posLT++] = LT::retLex('^', -1, -1);
		}

		delete tempVarLexTable.table;
		return true;
	}
	//јлгоритм построени€ :
	//-исходна€ строка : выражение;
	//-результирующа€ строка : польска€ запись;
	//-стек: пустой;
	//-исходна€ строка просматриваетс€ слева направо;
	//-операнды перенос€тс€ в результирующую строку в пор€дке их
	//	следовани€;
	//-операци€ записываетс€ в стек, если стек пуст или в вершине стека лежит
	//	отрывающа€ скобка;
	//-операци€ выталкивает все операции с большим или равным
	//	приоритетом в результирующую строку;
	//-отрывающа€ скобка помещаетс€ в стек;
	//-закрывающа€ скобка выталкивает все операции до открывающей
	//	скобки, после чего обе скобки уничтожаютс€;
	//-по концу разбора исходной строки все операции, оставшиес€ в стеке,
	//	выталкиваютс€ в результирующую строку.

	bool doRPNinLexTable(LT::LexTable lexTable, IT::IdTable idTable)
	{
		for (int i = 0; i < lexTable.head; ++i)
		{
			if (lexTable.table[i].lexema[GETLEX] == LEX_EQUAL && lexTable.table[i - 1].lexema[GETLEX] == LEX_ID)
			{
				if (!PolishNotation(i - 1, lexTable, idTable)) return false;
				continue;
			}
			/*if (lexTable.table[i - 1].lexema[GETLEX] == LEX_RETURN && lexTable.table[i].lexema[GETLEX] == LEX_ID)
			{
				if (!PolishNotation(i, lexTable, idTable)) return false;
				continue;
			}*/
		}
		return true;
	}
}
