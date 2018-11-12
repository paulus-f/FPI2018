#include "stdafx.h"
#include "CodeGeneration.h"
#define OUT								*log.stream
#define GETIDFROMLT(i)					idTable.table[lexTable.table[i].idxTI]
#define PARDEF							"DEFP"
#define GLMUV(parm1, parm2)				"\t\tMOV\t" << parm1 << ',' << parm2
#define GLADD(parm1, parm2)				"\t\tADD\t" << parm1 << ',' << parm2
#define GLSUB(parm1, parm2)				"\t\tSUB\t" << parm1 << ',' << parm2
#define GLMUL(parm1)					"\t\tMUL\t" << parm1
#define GLDIV(parm1)					"\t\tDIV\t" << parm1
#define MOV(parm1, parm2, parm3, parm4)	"\t\tMOV\t" << parm1 << parm2 << ',' << parm3 << parm4
#define ADD(parm1, parm2, parm3, parm4)	"\t\tADD\t" << parm1 << parm2 << ',' << parm3 << parm4
#define SUB(parm1, parm2, parm3, parm4)	"\t\tSUB\t" << parm1 << parm2 << ',' << parm3 << parm4
#define RET								'\t' << "\tret"
#define ENDL							std::endl;
#define ASMTEMPLATE						".586\n.model FLAT, C , stdcall\nincludelib libucrt.lib \nincludelib StanLib.lib \nincludelib kernel32.lib \nExitProcess PROTO : DWORD \n.stack 4096" 
#define ASM_CONST						"\n.const" 
#define ASM_CODE						"\n.code" 
#define ASM_DATA						"\n.data"
#define PUSH(VAR)						"\t\tPUSH \t"<< VAR
#define PUSH2(VAR1,VAR2)				"\t\tPUSH \t"<< VAR1 << VAR2
#define POP(VAR)						"\t\tPOP \t"<< VAR
#define POP2(VAR1,VAR2)					"\t\tPOP \t"<< VAR1 << VAR2
#define TINT							"DWORD"
#define TFL								"REAL4"
#define TSTR							"BYTE"
#define TBL								"BYTE"
#define INTLIT(num)						"\tINTLIT" << num << '\t' << '\t' << "DWORD" << '\t'
#define STRLIT(num)						"\tSTRLIT" << num << '\t' << '\t' << "BYTE" << '\t'
#define FLLIT(num)						"\tFLLIT" << num << '\t' << '\t' << "REAL4" << '\t'
#define BLLIT(num)						"\tBLLIT" << num << '\t' << '\t' << "BYTE" << '\t'
#define VARINT(name)					'\t' << name << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define VARSTR(name)					'\t' << name << '\t' << '\t' << '\t' << "BYTE" << '\t'<< 00
#define VARFL(name)						'\t' << name << '\t' << '\t' << '\t' << "REAL4" << '\t'<< "0.0"
#define VARBL(name)						'\t' << name << '\t' << '\t' << '\t' << "BYTE" << '\t'<< "0"
#define VRINT(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define VRSTR(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "BYTE" << '\t'<< 00
#define VRFL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "REAL4" << '\t'<< "0.0"
#define VRBL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "BYTE" << '\t'<< "0"
#define DEFPINT(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define DEFPSTR(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "BYTE" << '\t' << "0"
#define DEFPFL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "REAL4" << '\t' << "0"
#define DEFPBL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "BYTE" << '\t' << "0"
#define PROC(namedef)					'\t' << namedef << " PROC "	
#define ENDP(name)						'\t' << name << " ENDP"	
#define EMPTY							""
#define ISGLOBAL(str)					str[0] == '$'

void CG::StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log)
{
	OUT << ASMTEMPLATE << ENDL;
	addLiterals(idTable, log);
	addData(lexTable, idTable, log);
	//protImplem --- return nummain in lextable;
	mainImplem(lexTable, idTable, log, protImplem(lexTable, idTable, log), (char*)"main" );
}

void CG::branchIf(LT::LexTable& lexTable, IT::IdTable& idTable, int num, char *idfun)
{
}

void CG::addLiterals(IT::IdTable& idTable, Log::LOG log)
{
	OUT << ASM_CONST << ENDL;
	int numint = 0;
	int numstr = 0;
	int numfl = 0;
	int numbl = 0;
	for (int i = 0; i < idTable.head; ++i)
	{
		if (idTable.table[i].idtype == IT::IDTYPE::L)
		{
			switch (idTable.table[i].iddatatype)
			{
			case IT::INT: 
				OUT << INTLIT(numint++) << idTable.table[i].value.vint << ENDL;
				break;
			case IT::STR:
				OUT << STRLIT(numstr++) << idTable.table[i].value.vstr << ENDL;
				break;
			case IT::FL: 
				OUT << FLLIT(numfl++) << idTable.table[i].value.vfl << ENDL;
				break;
			case IT::BL: 
				OUT << BLLIT(numbl++) << idTable.table[i].value.vbool<< ENDL;
				break;
			}
		}
	}
}

void CG::addData(LT::LexTable& lexTable, IT::IdTable & idTable, Log::LOG log)
{
	OUT << ASM_DATA << ENDL;
	char fun[255];
	for (int i = 0; i < idTable.head; ++i)
	{
		if (idTable.table[i].idtype == IT::IDTYPE::F)
		{
			strcpy(fun, idTable.table[i].id);
		}
		if (idTable.table[i].idtype == IT::IDTYPE::V)
		{
			switch (idTable.table[i].iddatatype)
			{
			case IT::INT:
				if(ISGLOBAL(idTable.table[i].id)) OUT << VARINT(fun, idTable.table[i].id) << ENDL
				else	OUT << VRINT(fun,idTable.table[i].id) << ENDL
				break;
			case IT::STR:
				if (ISGLOBAL(idTable.table[i].id)) OUT << VARSTR(fun, idTable.table[i].id) << ENDL
				else	OUT << VRSTR(fun, idTable.table[i].id) << ENDL
				break;
			case IT::FL:
				if (ISGLOBAL(idTable.table[i].id)) OUT << VARFL(fun, idTable.table[i].id) << ENDL
				else	OUT << VRFL(fun, idTable.table[i].id) << ENDL
				break;
			case IT::BL:
				if (ISGLOBAL(idTable.table[i].id)) OUT << VARBL(fun, idTable.table[i].id) << ENDL
				else	OUT << VRBL(fun, idTable.table[i].id) << ENDL
				break;
			}
		}

		if (idTable.table[i].idtype == IT::IDTYPE::P)
		{
			int numFun = 0;
			char *nameFun;
			for(numFun = i; idTable.table[numFun].idtype != IT::IDTYPE::F; numFun--);
			
			switch (idTable.table[i].iddatatype)
			{
			case IT::INT:
				OUT << DEFPINT(idTable.table[numFun].id, idTable.table[i].id) << ENDL;
				break;
			case IT::STR:
				OUT << DEFPSTR(idTable.table[numFun].id, idTable.table[i].id) << ENDL;
				break;
			case IT::FL:
				OUT << DEFPFL(idTable.table[numFun].id, idTable.table[i].id) << ENDL;
				break;
			case IT::BL:
				OUT << DEFPBL(idTable.table[numFun].id, idTable.table[i].id) << ENDL;
				break;
			}
		}
	}
}

int CG::protImplem(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log)
{
	int numMain = 0;
	OUT << ASM_CODE << ENDL;
	for(int i = 0; i < lexTable.head; i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_MAIN) numMain = i;
		if (lexTable.table[i-1].lexema[GETLEX] == LEX_FUNCTION && lexTable.table[i].lexema[GETLEX] == LEX_ID)
		{
			int amountarg = getAmountPar(idTable, lexTable.table[i].idxTI);
			IT::Entry itentry = GETIDFROMLT(i);
			OUT << PROC(itentry.id);
			i++;
			for (int j = amountarg; j != 0;i++)
			{
				if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
				{
					switch (GETIDFROMLT(i).iddatatype)
					{
					case IT::INT:
						if (j == 1) OUT << itentry.id << GETIDFROMLT(i).id << " : DWORD " << ENDL
						else OUT << itentry.id << GETIDFROMLT(i).id << " : DWORD, ";
						j--;
						break;
					case IT::STR:
						if (j == 1) OUT << itentry.id << GETIDFROMLT(i).id << " : BYTE " << ENDL
						else OUT << itentry.id << GETIDFROMLT(i).id << " : BYTE, ";
						j--;
						break;
					case IT::FL:
						if (j == 1) OUT << itentry.id << GETIDFROMLT(i).id << " : REAL4 " << ENDL
						else OUT << itentry.id << GETIDFROMLT(i).id << " : REAL4, ";
						j--;
						break;
					case IT::BL:
						if (j == 1) OUT << itentry.id << GETIDFROMLT(i).id << " : BYTE "<< ENDL
						else OUT << itentry.id << GETIDFROMLT(i).id << " : BYTE, ";
						j--;
						break;
					}
				}
			}

			i = releaseFun(lexTable, idTable, log, i, itentry.id);
			OUT << ENDP(itentry.id) << ENDL;
			
		}
	}
	OUT << ENDL;
	return numMain;
}

int CG::releaseFun(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log, int pos, char *idfun)
{
	for (int i = pos;; i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_MAIN || lexTable.table[i].lexema[GETLEX] == LEX_FUNCTION || i + 1 == lexTable.head)
		{
			OUT << RET << ENDL;
			return i;
		}
		switch (lexTable.table[i].lexema[GETLEX])
		{
			case LEX_INPUT: break;
			case LEX_OUTPUT: break;
			case LEX_CYCLE: break;
			case LEX_FOR: break;
			case LEX_EQUAL: break;
			case LEX_BRANCH: break;
			case LEX_ALIAS: break;
			case LEX_RETURN:
			//isExpression(lexTable, idTable,log, i++, idfun);
				
					//std::vector<LT::Entry> vecEntr;
				for (;; i++)
				{
					if (lexTable.table[i].lexema[GETLEX] == '^' || lexTable.table[i].lexema[GETLEX] == LEX_SEMICOLON) break;
					if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
					{
						if (ISGLOBAL(GETIDFROMLT(i).id)) OUT << PUSH(GETIDFROMLT(i).id) << ENDL
						else OUT << PUSH2(idfun, GETIDFROMLT(i).id) << ENDL;
					}
					if (lexTable.table[i].lexema[GETLEX] == LEX_LITERAL)
					{
						switch (GETIDFROMLT(i).iddatatype)
						{
						case IT::IDDATATYPE::INT: 
							OUT << POP2("INTLIT", IT::getIDLIT(idTable, IT::IDDATATYPE::INT, GETIDFROMLT(i))) << ENDL
							break;
						case IT::IDDATATYPE::STR:
							OUT << POP2("STRLIT", IT::getIDLIT(idTable, IT::IDDATATYPE::STR, GETIDFROMLT(i))) << ENDL
							break;
						case IT::IDDATATYPE::FL:
							OUT << POP2("FLLIT", IT::getIDLIT(idTable, IT::IDDATATYPE::FL, GETIDFROMLT(i))) << ENDL
							break;
						case IT::IDDATATYPE::BL:
							OUT << POP2("BLLIT", IT::getIDLIT(idTable, IT::IDDATATYPE::BL, GETIDFROMLT(i))) << ENDL
							break;
						}
					}
					if (lexTable.table[i].lexema[GETLEX] == LEX_OPERATION)
					{
						switch (lexTable.table[i].operation)
						{
						case PLUS:
							OUT << POP("EAX") << ENDL
							OUT << POP("EBX") << ENDL
							OUT << GLADD("EAX", "EBX") << ENDL
							OUT << PUSH("EAX") << ENDL
							break;
						case MINUS:
							OUT << POP("EAX") << ENDL
							OUT << POP("EBX") << ENDL
							OUT << GLSUB("EAX", "EBX") << ENDL
							OUT << PUSH("EAX") << ENDL
							break;
						case STAR:
							OUT << POP("EAX") << ENDL
							OUT << POP("EBX") << ENDL
							OUT << GLMUL("EBX") << ENDL
							OUT << PUSH("EAX") << ENDL
							break;
						case DIRSLASH:
							OUT << POP("EAX") << ENDL
							OUT << POP("EBX") << ENDL
							OUT << GLDIV("EBX") << ENDL
							OUT << PUSH("EAX") << ENDL
							break;
						}
					}	
				}

			/*	if (GETIDFROMLT(lexTable.table[i].idxTI).iddatatype == IT::IDDATATYPE::BL)
				{
					for (int count = 0;; i++)
					{
						if (lexTable.table[i].lexema[GETLEX] == LEX_ÑOMPARISONOPER)
						{

						}
					}
				}*/

				OUT << POP("EAX") << ENDL;
			break;
		}
	}
	return -1;
}




void CG::mainImplem(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log, int numMain, char *idfun)
{
}

void CG::isExpression(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log, int num, char *idfun)
{
	int start = num;
	
}

void CG::isInit(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log, int num, char *idfun)
{
}


void CG::branchUnless(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun)
{
}

void CG::cycleWhile(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun)
{
}

void CG::cycleUntil(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun)
{
}

void CG::cycleFor(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun)
{
}

void CG::genProce(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log, int num, char *idfun)
{
}
