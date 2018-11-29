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
#include <sstream>
#include <iomanip>
#include <fstream>
namespace LT {
	LT::Entry retLex(char lex, int numstr, int idx)
	{
		LT::Entry tempEntry;
		tempEntry.lexema[GETLEX] = lex;
		tempEntry.idxTI = idx;
		tempEntry.sn = numstr;
		return tempEntry;
	}

	void LT::LexicalAnalysis(char* str, LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log)
	{
		if (str == EMPTYSTR)
		{
			throw ERROR_THROW_IN(118, 0, 0);
		}
		int  numLine				= 1;
		int  numCol					= 0;
		int  indCO					= 0;
		char *strCode				= str;
		bool flagBuffReady			= false;
		bool flagParametr			= false;
		bool flagCycle				= false;
		bool flagBranch				= false;
		bool idFlag					= false;
		bool errorLex				= false;
		bool boolOper				= false;
		bool flagMain				= false;
		std::vector<int> checkThesis;
		char buff[TI_STR_MAXSIZE];
		char buffL[TI_STR_MAXSIZE];
		char buffCO[10];
		char buffType[TI_STR_MAXSIZE];
		LT::Entry lexEntry;
		Error::ERROR errarr[100];
		int errhead = 0;

		for (int i = 0, buffIndL = 0, buffInd = 0; i < strlen(strCode); i++)
		{
			numCol++;

			if (strCode[i] == TAB || (strCode[i] == SPACE && strCode[i + 1] == SPACE))
			{
				continue;
			}
			else if (strCode[i] == QUOTES)
			{
				int j = i;
				buffIndL = 0;
				for (j++; strcmp((strCode[j] + EMPTYSTR), QUOTES + EMPTYSTR); j++)
				{
					buffL[buffIndL++] = strCode[j];
					if (j + 1 == strlen(strCode))
					{
						errorLex = true;
						errarr[errhead++] = ERROR_THROW_IN(116, numLine, numCol);
					}
				}
				i = j;
				buffL[buffIndL] = '\0';
				
				FST::FST fstTypeStr(buffL, FST_STRLIT);
				if (FST::execute(fstTypeStr))
				{
					lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
					Add(lexTable, lexEntry);
					IT::Entry litStrId;
					litStrId.scope = IT::SCOPE::LIT;
					litStrId.idxfirstLE = lexTable.head;
					litStrId.iddatatype = IT::STR;
					litStrId.idtype = IT::L;
					int len = strlen(buffL);
					strcpy(litStrId.id, "STR LIT");
					litStrId.value.vstr.len = len;
					strncpy(litStrId.value.vstr.str, buffL, len);
					litStrId.value.vstr.str[len] = '\0';
					IT::Add(idTable, litStrId);
				}
				else
				{
					errorLex = true;
					errarr[errhead++] = ERROR_THROW_IN(119, numLine, numCol);
				}
			}
			else if (strCode[i] == NEWLINE)
			{
				numLine++;
				numCol = 0;
			}
			else if ((strCode[i] == SPACE && strCode[i + 1] != SPACE) || isOperOrSep(strCode[i]))
			{
				if ((strCode[i] == MORE || strCode[i] == LESS) && strCode[i-1] == 'p')
				{
					buff[buffInd++] = strCode[i];
					i++;
					buff[buffInd] = '\0';
					buffInd = 0;
				}
				else
				{
					buff[buffInd] = '\0';
					buffInd = 0;
				}

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

					FST::FST fstBool(buff, FST_BOOL);
					if (FST::execute(fstBool) && flagBuffReady)
					{
						lexEntry = retLex(LEX_BOOL, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						strcpy(buffType, BOOL);
						flagBuffReady = false;
					}

					FST::FST fstFloat(buff, FST_FLOAT);
					if (FST::execute(fstFloat) && flagBuffReady)
					{
						lexEntry = retLex(LEX_FLOAT, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						strcpy(buffType, FLOAT);
						flagBuffReady = false;
					}

					FST::FST fstFun(buff, FST_FUN);
					if (FST::execute(fstFun) && flagBuffReady)
					{
						lexEntry = retLex(LEX_FUNCTION, numLine, LT_TI_NULLIDX);
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
							IT::addFun(idTable, lexTable, lexEntry, (char*)MAIN, (char*)"int");
							flagMain = !flagMain;
						}
						else
						{
							errorLex = true;
							errarr[errhead++] = ERROR_THROW_IN(115, numLine, numCol);;
						}
					}
					
					FST::FST fstOutput(buff, FST_OUTPUT);
					if (FST::execute(fstOutput) && flagBuffReady)
					{
						lexEntry = retLex(LEX_OUTPUT, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBuffReady = false;
					}

					FST::FST fstInput(buff, FST_INPUT);
					if (FST::execute(fstInput) && flagBuffReady)
					{
						lexEntry = retLex(LEX_INPUT, numLine, LT_TI_NULLIDX);
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

					FST::FST fstFor(buff, FST_FOR);
					if (FST::execute(fstFor) && flagBuffReady)
					{
						lexEntry = retLex(LEX_FOR, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagCycle = true;
						flagBuffReady = false;
					}

					FST::FST fstWhite(buff, FST_WHILE);
					if (FST::execute(fstWhite) && flagBuffReady)
					{
						lexEntry = retLex(LEX_CYCLE, numLine, LT_TI_NULLIDX);
						lexEntry.cycling.cycle = Cycle::w;
						Add(lexTable, lexEntry);
						flagCycle = true;
						flagBuffReady = false;
					}

					FST::FST fstUntil(buff, FST_UNTIL);
					if (FST::execute(fstUntil) && flagBuffReady)
					{
						lexEntry = retLex(LEX_CYCLE, numLine, LT_TI_NULLIDX);
						lexEntry.cycling.cycle = Cycle::ut;
						Add(lexTable, lexEntry);
						flagCycle = true;
						flagBuffReady = false;
					}

					FST::FST fstUnless(buff, FST_UNLESS);
					if (FST::execute(fstUnless) && flagBuffReady)
					{
						lexEntry = retLex(LEX_BRANCH, numLine, LT_TI_NULLIDX);
						lexEntry.branching.br = Branch::ul;
						Add(lexTable, lexEntry);
						flagBranch = true;
						flagBuffReady = false;
					}

					FST::FST fstIf(buff, FST_IF);
					if (FST::execute(fstIf) && flagBuffReady)
					{
						lexEntry = retLex(LEX_BRANCH, numLine, LT_TI_NULLIDX);
						lexEntry.branching.br = Branch::i;
						Add(lexTable, lexEntry);
						flagBranch = true;
						flagBuffReady = false;
					}

					FST::FST fstAlias(buff, FST_ALIAS);
					if (FST::execute(fstAlias) && flagBuffReady)
					{
						lexEntry = retLex(LEX_ALIAS, numLine, LT_TI_NULLIDX);
						Add(lexTable, lexEntry);
						flagBranch = true;
						flagBuffReady = false;
					}

					FST::FST fstTrueLit(buff, FST_LITTRUE);
					if (FST::execute(fstTrueLit) && flagBuffReady)
					{
						lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
						Add(lexTable, lexEntry);

						IT::Entry litTrueid;
						litTrueid.scope = IT::SCOPE::LIT;
						litTrueid.idxfirstLE = lexTable.head - 1;
						litTrueid.iddatatype = IT::BL;
						litTrueid.idtype = IT::L;
						strcpy(litTrueid.id, "BOOL LIT");
						litTrueid.value.vbool = true;
						IT::Add(idTable, litTrueid);
						flagBuffReady = false;
					}

					FST::FST fstFalseLit(buff, FST_LITFALSE);
					if (FST::execute(fstFalseLit) && flagBuffReady)
					{
						lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
						Add(lexTable, lexEntry);

						IT::Entry litFalse;
						litFalse.scope = IT::SCOPE::LIT;
						litFalse.idxfirstLE = lexTable.head - 1;
						litFalse.iddatatype = IT::BL;
						litFalse.idtype = IT::L;
						strcpy(litFalse.id, "BOOL LIT");
						litFalse.value.vbool = false;
						IT::Add(idTable, litFalse);
						flagBuffReady = false;
					}

					FST::FST fstIntLit(buff, FST_INTLIT);
					if (FST::execute(fstIntLit) && flagBuffReady)
					{
						lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
						Add(lexTable, lexEntry);

						IT::Entry litIntId;
						litIntId.scope = IT::SCOPE::LIT;
						litIntId.idxfirstLE = lexTable.head - 1;
						litIntId.iddatatype = IT::INT;
						litIntId.idtype = IT::L;
						strcpy(litIntId.id, "INT LIT");
						litIntId.value.vint = std::atoi(buff);
						IT::Add(idTable, litIntId);
						flagBuffReady = false;
					}
					
					FST::FST fstFlLit(buff, FST_FLLIT);
					if (FST::execute(fstFlLit) && flagBuffReady)
					{
						lexEntry = retLex(LEX_LITERAL, numLine, idTable.head);
						Add(lexTable, lexEntry);

						IT::Entry litFlid;
						litFlid.scope = IT::SCOPE::LIT;
						litFlid.idxfirstLE = lexTable.head-1;
						litFlid.iddatatype = IT::FL;
						litFlid.idtype = IT::L;
						strcpy(litFlid.id, "FL LIT");
						std::istringstream ss(buff);
						ss >> litFlid.value.vfl;
						IT::Add(idTable, litFlid);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstStrlen(buff, FST_STRLEN);
					if (FST::execute(fstStrlen) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}
				
					// standart lib ///////////////////////////////////
					FST::FST fstSubstr(buff, FST_SUBSTR);
					if (FST::execute(fstSubstr) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMsin(buff, FST_MSIN);
					if (FST::execute(fstMsin) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMcos(buff, FST_MCOS);
					if (FST::execute(fstMcos) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMtan(buff, FST_MTAN);
					if (FST::execute(fstMtan) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMctan(buff, FST_MCTAN);
					if (FST::execute(fstMctan) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMabs(buff, FST_MABS);
					if (FST::execute(fstMabs) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMln(buff, FST_MLN);
					if (FST::execute(fstMln) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstMsqr(buff, FST_MSQR);
					if (FST::execute(fstMsqr) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
						flagBuffReady = false;
					}

					// standart lib ///////////////////////////////////
					FST::FST fstStrfind(buff, FST_STRFIND);
					if (FST::execute(fstStrfind) && flagBuffReady)
					{
						flagParametr = SL::funStandLib(lexTable, idTable, buff, numLine);
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
									errorLex = true;
									errarr[errhead++] = ERROR_THROW_IN(117, numLine, numCol);
								}
								else
								{
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
									default:
										errorLex = true;
										errarr[errhead++] = ERROR_THROW(999);
									}
									break;
								}
							}
						}
						else
						{
							errorLex = true;
							errarr[errhead++] = ERROR_THROW_IN(114, numLine, numCol);
						}
						idFlag = false;
					}
				}
			}
			else
			{
				buff[buffInd++] = strCode[i];
			}
			
			if (isCO(strCode[i]))
			{
				buffCO[indCO++] = strCode[i];

				if (isCO(strCode[i + 1]))
				{
					buffCO[indCO++] = strCode[i + 1];
				}
				buffCO[indCO] = NULL;

				FST::FST fstLogEqual(buffCO, FST_E);
				if (FST::execute(fstLogEqual))
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::e;
					indCO = 0;
					Add(lexTable, lexEntry);
					i = i + 2;
					continue;
				}

				FST::FST fstLogNotEqual(buffCO, FST_NE);
				if (FST::execute(fstLogNotEqual))
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::ne;
					indCO = 0;
					Add(lexTable, lexEntry);
					i = i + 2;
					continue;
				}

				FST::FST fstLogMore(buffCO, FST_M);
				if (FST::execute(fstLogMore) && strCode[i - 1] != 'p')
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::m;
					indCO = 0;
					Add(lexTable, lexEntry);
					i = i + 1;
					continue;
				}

				FST::FST fstLogLess(buffCO, FST_L);
				if (FST::execute(fstLogLess) && strCode[i - 1] != 'p')
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::l;
					indCO = 0;
					Add(lexTable, lexEntry);
					continue;
				}

				FST::FST fstLogLessEqual(buffCO, FST_LE);
				if (FST::execute(fstLogLessEqual))
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::le;
					indCO = 0;
					Add(lexTable, lexEntry);
					i = i + 2;
					continue;
				}

				FST::FST fstLogMoreEqual(buffCO, FST_ME);
				if (FST::execute(fstLogMoreEqual))
				{
					lexEntry = retLex(LEX_ÑOMPARISONOPER, numLine, LT_TI_NULLIDX);
					lexEntry.co = CO::me;
					indCO = 0;
					Add(lexTable, lexEntry);
					i = i + 2;
					continue;
				}

				indCO = 0;
			}

			if (isOperOrSep(strCode[i]) && strCode[i+1] != '>')
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
					flagParametr	= false;
					flagBranch		= false;
					flagCycle		= false;
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
		for (int i = 0; i < lexTable.head; i++)
		{
			std::cout << lexTable.table[i].lexema[0];
		}

		for (int i = 0; i < lexTable.head; i++)
		{
			if (lexTable.table[i].lexema[GETLEX] == LEX_LEFTHESIS)
			{
				checkThesis.push_back(-1);
				checkThesis.push_back(lexTable.table[i].sn);
			}
			if (lexTable.table[i].lexema[GETLEX] == LEX_RIGHTHESIS)
			{
				if (checkThesis.empty())
				{
					errorLex = true;
					errarr[errhead++] = ERROR_THROW_IN(109, lexTable.table[i].sn, -1);
				}
				for (int j = 0; j < checkThesis.size(); j++)
				{
					if (checkThesis[j] == -1 && checkThesis[j + 1] == lexTable.table[i].sn)
					{
						checkThesis.pop_back();
						checkThesis.pop_back();
						j++;
					}
					else
					{
						errorLex = true;
						errarr[errhead++] = ERROR_THROW_IN(109, checkThesis[j + 1], -1);
						checkThesis.pop_back();
						checkThesis.pop_back();
						j++;
					}
				}
			}
		}
		if (errorLex)
		{	
			throw Error::getarrayerror(errarr, log, 113, errhead);
		}
		/////TABLE OF LEXEM AND IND. ARE ALL RIGHT BEFORE POLISH NOTATION
		std::cout << "LexicalAnalysis is made copmlete" << std::endl;
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
		char lexAnStr[] = "---Ëåêñè÷åñêèé àíàëèçàòîð---";
		char newLine[2] = "\n";
		Log::WriteLine(log, lexAnStr, EMPTYSTR);

		*log.stream << std::endl;
		*log.stream << 0 << 1 << "   ";

		for (int numLine = 1, ind = 0; ind < lexTable.head; ind++)
		{
			if(lexTable.table[ind].lexema[GETLEX] == '^')
			{
				continue;
			}
			else if (numLine != lexTable.table[ind+1].sn)
			{
				*log.stream << lexTable.table[ind].lexema[GETLEX] << std::endl;
				*log.stream << 0 << numLine++ << std::setw(5) << std::left << "   ";
			}
			else if (numLine == lexTable.table[ind].sn)
			{
				*log.stream << lexTable.table[ind].lexema[GETLEX];
			}
		}
		*log.stream << std::endl;
	}

	bool LT::isOperOrSep(char lit)
	{
		switch (lit)
		{
		case RIGHTHESIS: case LEFTHESIS: case LEFTBRACET:
		case RIGHTBRACELET: case  SEMICOLON: case  COMMA:
		case PLUS: case MINUS: case EQUAL:
		case MORE: case LESS: case EXCLAM:
		case DIRSLASH: case STAR: case ENDNULL: return true;
		default: return false;
		}
	}

	bool LT::isCO(char lit)
	{
		switch (lit)
		{
		case MORE: case LESS: case EQUAL: case EXCLAM:
		return true;
		default: return false;
		}
	}
}