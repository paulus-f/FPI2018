#include "stdafx.h"
#include "LT.h"
#include  "IT.h"
#include "Error.h"
#include <iostream>
#include  <mbstring.h>
#include "Log.h"
#include "FST.h"
#include <vector>
#include "stanlib.h"
#include "RPN.h"
namespace LT {
	LT::Entry retLex(char lex, int numstr, int idx)
	{
		LT::Entry tempEntry;
		tempEntry.lexema[GETLEX] = lex;
		tempEntry.idxTI = idx;
		tempEntry.sn = numstr;
		return tempEntry;
	}

	void LT::LexicalAnalysis(char* str, LT::LexTable& lexTable, IT::IdTable idTable, Log::LOG log)
	{
		if (str == EMPTYSTR)
		{
			throw ERROR_THROW_IN(118, 0, 0);
		}

		int  numLine = 1;
		int  numCol = 0;
		char buffL[TI_STR_MAXSIZE];
		char buff[TI_STR_MAXSIZE];
		char buffType[TI_STR_MAXSIZE];
		char *strCode = str;
		bool flagBuffReady = false;
		bool flagParametr = false;
		bool idFlag = false;
		bool flagMain = false;
		LT::Entry lexEntry;

		for (int i = 0, buffIndL = 0, buffInd = 0; i < strlen(strCode); i++)
		{
			numCol++;

			if (strCode[i] == SPACE && strCode[i + 1] == SPACE)
			{
				continue;
			}
			else if (strCode[i] == QUOTES)
			{
				int j = i;
				buffIndL = 0;
				buffL[buffIndL++] = strCode[i];
				for (j++; strcmp((strCode[j] + EMPTYSTR), QUOTES + EMPTYSTR); j++)
				{
					buffL[buffIndL++] = strCode[j];
					if (j + 1 == strlen(strCode))
					{
						throw ERROR_THROW_IN(116, numLine, numCol);
					}
				}

				i = j;
				buffL[buffIndL++] = strCode[i];
				buffL[buffIndL] = '\0';
				FST::FST fstTypeStr(buffL, FST_STRLIT);
				if (FST::execute(fstTypeStr))
				{
					lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
					Add(lexTable, lexEntry);

					IT::Entry litStrId;
					litStrId.idxfirstLE = lexTable.head;
					litStrId.iddatatype = IT::STR;
					litStrId.idtype = IT::L;
					int len = strlen(buffL);
					strcpy(litStrId.id, "STR LIT");
					litStrId.value.vstr->len = len - 2;
					strncpy(litStrId.value.vstr->str, buffL + 1, len - 2);
					litStrId.value.vstr->str[len - 2] = '\0';
					IT::Add(idTable, litStrId);
				}
				else
				{
					throw ERROR_THROW_IN(119, numLine, numCol);
				}
			}
			else if (strCode[i] == NEWLINE)
			{
				numLine++;
				numCol = 0;
			}
			else if ((strCode[i] == SPACE && strCode[i + 1] != SPACE) || isOperOrSep(strCode[i]))
			{
				buff[buffInd] = '\0';
				buffInd = 0;
				if (!isOperOrSep(buff[0]))
				{
					flagBuffReady = !flagBuffReady;
				}

				if (flagBuffReady)
				{
					FST::FST fstTypeInt(buff, FST_INT);
					if (FST::execute(fstTypeInt) && flagBuffReady)
					{
						lexEntry = retLex(LEX_INTEGER, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						strcpy(buffType, INTEGER);
						flagBuffReady = false;
					}
					FST::FST fstTypeStr(buff, FST_STR);
					if (FST::execute(fstTypeStr) && flagBuffReady)
					{
						lexEntry = retLex(LEX_STRING, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						strcpy(buffType, STRING);
						flagBuffReady = false;
					}
					FST::FST fstFun(buff, FST_FUN);
					if (FST::execute(fstFun) && flagBuffReady)
					{
						lexEntry = retLex(LEX_FUNCTION, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBuffReady = false;
					}
					FST::FST fstDec(buff, FST_DEC);
					if (FST::execute(fstDec) && flagBuffReady)
					{
						lexEntry = retLex(LEX_DECLARE, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBuffReady = false;
					}
					FST::FST fstMain(buff, FST_MAIN);
					if (FST::execute(fstMain) && flagBuffReady)
					{
						flagBuffReady = false;
						if (!flagMain)
						{
							lexEntry = retLex(LEX_MAIN, numLine, LT_TI_NULLIDX);
							Add(lexTable, lexEntry);
							flagMain = !flagMain;
						}
						else
						{
							throw ERROR_THROW_IN(115, numLine, numCol);;
						}
					}
					FST::FST fstPrint(buff, FST_PRINT);
					if (FST::execute(fstPrint) && flagBuffReady)
					{
						lexEntry = retLex(LEX_PRINT, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBuffReady = false;
					}
					FST::FST fstRet(buff, FST_RET);
					if (FST::execute(fstRet) && flagBuffReady)
					{
						lexEntry = retLex(LEX_RETURN, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBuffReady = false;
					}
					FST::FST fstIntLit(buff, FST_INTLIT);
					if (FST::execute(fstIntLit) && flagBuffReady)
					{
						lexEntry = retLex(LEX_LITERAL, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);

						IT::Entry litIntId;
						litIntId.idxfirstLE = lexTable.head;
						litIntId.iddatatype = IT::INT;
						litIntId.idtype = IT::L;
						strcpy(litIntId.id, "INT LIT");
						litIntId.value.vint = std::atoi(buff);
						IT::Add(idTable, litIntId);
						flagBuffReady = false;
					}
					// standart lib ///////////////////////////////////
					FST::FST fstStrlen(buff, FST_STRLEN);
					if (FST::execute(fstStrlen) && flagBuffReady)
					{
						flagParametr = SL::funStrlen(lexTable, idTable, buff, buffType, numLine);
						flagBuffReady = false;

					}

					// standart lib ///////////////////////////////////
					FST::FST fstSubstr(buff, FST_SUBSTR);
					if (FST::execute(fstSubstr) && flagBuffReady)
					{
						flagParametr = SL::funStrlen(lexTable, idTable, buff, buffType, numLine);
						flagBuffReady = false;
					}

					if (flagBuffReady)
					{
						flagBuffReady = false;
						idFlag = true;
					}
					if (idFlag)
					{
						FST::FST fstID(buff, FST_ID);
						if (strlen(buff) <= ID_MAXSIZE && FST::execute(fstID))
						{
							switch (lexTable.table[lexTable.head - 1].lexema[GETLEX])
							{
							case LEX_TYPE:
								IT::Entry indType;
								lexEntry = retLex(LEX_ID, numLine, idTable.head);
								IT::addVarOrPar(idTable, lexTable, lexEntry, buff, buffType, flagParametr, numLine, numCol);
								break;
							case LEX_FUNCTION:
								lexEntry = retLex(LEX_ID, numLine, idTable.head);
								flagParametr = true;
								IT::addFun(idTable, lexTable, lexEntry, buff, buffType);
								break;
							default:
								int findId = IT::IsId(idTable, lexTable, buff);
								if (findId == TI_NULLIDX)
								{
									throw ERROR_THROW_IN(117, numLine, numCol);
								}
								switch (idTable.table[findId].idtype)
								{
								case IT::V:
									lexEntry = retLex(LEX_ID, numLine, findId);
									LT::Add(lexTable, lexEntry);
									break;
								case IT::F:
									lexEntry = retLex(LEX_ID, numLine, findId);
									LT::Add(lexTable, lexEntry);
									break;
								case IT::L:
									lexEntry = retLex(LEX_ID, numLine, findId);
									LT::Add(lexTable, lexEntry);
									break;
								case IT::P:
									lexEntry = retLex(LEX_ID, numLine, findId);
									LT::Add(lexTable, lexEntry);
									break;
								default: throw ERROR_THROW(999);
								}
								break;
							}
						}
						else
						{
							throw ERROR_THROW_IN(114, numLine, numCol);
						}

						idFlag = false;
					}
				}
			}
			else
			{
				buff[buffInd++] = strCode[i];
			}

			if (isOperOrSep(strCode[i]))
			{
				buff[buffInd++] = strCode[i];
				buff[buffInd] = '\0';
				buffInd = 0;

				FST::FST fstLefrBrac(buff, FST_LEFTBRACE);
				if (FST::execute(fstLefrBrac))
				{
					lexEntry = retLex(LEX_LEFTBRACE, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}


				FST::FST fstRightT(buff, FST_BRACELET);
				if (FST::execute(fstRightT))
				{
					lexEntry = retLex(LEX_BRACELET, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstRightBrac(buff, FST_RIGHTTHESIS);
				if (FST::execute(fstRightBrac))
				{
					flagParametr = false;
					lexEntry = retLex(LEX_RIGHTHESIS, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstLeftT(buff, FST_LEFTTHESIS);
				if (FST::execute(fstLeftT))
				{
					lexEntry = retLex(LEX_LEFTHESIS, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstComma(buff, FST_COMMA);
				if (FST::execute(fstComma))
				{
					lexEntry = retLex(LEX_COMMA, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstSemicolon(buff, FST_SEMICOLON);
				if (FST::execute(fstSemicolon))
				{
					lexEntry = retLex(LEX_SEMICOLON, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstEqual(buff, FST_EQUAL);
				if (FST::execute(fstEqual))
				{
					lexEntry = retLex(LEX_EQUAL, numLine, LT_TI_NULLIDX);
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstPlus(buff, FST_PLUS);
				if (FST::execute(fstPlus))
				{
					lexEntry = retLex(LEX_OPERATION, numLine, LT_TI_NULLIDX);
					lexEntry.operation = PLUS;
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstMinus(buff, FST_MINUS);
				if (FST::execute(fstMinus))
				{
					lexEntry = retLex(LEX_OPERATION, numLine, LT_TI_NULLIDX);
					lexEntry.operation = PLUS;
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstStar(buff, FST_STAR);
				if (FST::execute(fstStar))
				{
					lexEntry = retLex(LEX_OPERATION, numLine, LT_TI_NULLIDX);
					lexEntry.operation = STAR;
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstDir(buff, FST_DIR);
				if (FST::execute(fstDir))
				{
					lexEntry = retLex(LEX_OPERATION, numLine, LT_TI_NULLIDX);
					lexEntry.operation = DIRSLASH;
					Add(lexTable, lexEntry);
					continue;
				}
			}
		}
		std::cout << lexTable.head << std::endl;
		/////TABLE OF LEXEM AND IND. ARE ALL RIGHT BEFORE POLISH NOTATION
		std::cout << "LexicalAnalysis is made copmlete" << std::endl;
		// polish notation
	
		LogLA(lexTable, log);
		IT::logIT(idTable, log);
	}

	LT::LexTable LT::Create(int size)
	{
		LexTable *tempLexTable = new LexTable;
		tempLexTable->maxsize = LT_MAXSIZE;
		tempLexTable->size = size;
		tempLexTable->table = new Entry[size];
		return* tempLexTable;
	}

	void LT::Add(LexTable &lextable, Entry entry)
	{
		lextable.table[lextable.head++] = entry;
	}

	LT::Entry LT::GetEntry(LexTable & lextable, int n)
	{
		int count = 0;
		for (int i = 0; i < lextable.head; i++)
		{
			if (lextable.table[i].sn == n)
				count++;
		};
		Entry *lineEntry = new Entry[count];
		for (int i = 0, j = 0; i < lextable.head; ++i)
		{
			if (lextable.table[i].sn == n)
				lineEntry[j++] = lextable.table[i];
		}
		return *lineEntry;
	}

	void LT::Delete(LexTable & lextable)
	{
		delete lextable.table;
	}

	void LT::LogLA(LexTable& lexTable, Log::LOG log)
	{
		for (int i = 0; i < lexTable.head; i++)
		{
			std::cout << lexTable.table[i].lexema[GETLEX];
		}

		char lexAnStr[] = "---Лексический анализатор---";
		char buff[2] = " ";
		char space[5] = "    ";
		char num[6] = "0    ";
		char newLine[2] = "\n";
		Log::WriteLine(log, lexAnStr, EMPTYSTR);

		for (int numLine = 0, ind = 0, strOutPut = 3; ind < lexTable.head; ind++)
		{
			if(lexTable.table[ind].lexema[GETLEX] == '^')
			{
				continue;
			}
			else if (numLine == lexTable.table[ind].sn)
			{
				buff[0] = lexTable.table[ind].lexema[GETLEX];
				Log::WriteLine(log, buff, EMPTYSTR);
			}
			else
			{
				buff[0] = lexTable.table[ind].lexema[GETLEX];
				Log::WriteLine(log, newLine, EMPTYSTR);
				_itoa(numLine, num + 1, 10);
				Log::WriteLine(log, num, space, EMPTYSTR);
				Log::WriteLine(log, buff, EMPTYSTR);

				numLine++;
			}
		}
		Log::WriteLine(log, newLine, EMPTYSTR);
	}

	bool LT::isOperOrSep(char lit)
	{
		switch (lit)
		{
		case RIGHTHESIS: case LEFTHESIS: case LEFTBRACET:
		case RIGHTBRACELET: case  SEMICOLON: case  COMMA:
		case PLUS: case MINUS: case EQUAL:
		case DIRSLASH: case STAR: case ENDNULL: return true;
		default: return false;
		}
	}
}