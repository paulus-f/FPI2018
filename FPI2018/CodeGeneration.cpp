#include "stdafx.h"
#include "iostream"
#include "CodeGeneration.h"
#define CURRLEX(i)						lexTable.table[i].lexema[0]
#define CURRLE(i)						lexTable.table[i]	
#define LABEL(name)						name << ':'
#define OUT								*log.stream
#define GETIDFROMLT(i)					idTable.table[lexTable.table[i].idxTI]
#define INCLUDELIB						" inputfpi PROTO: DWORD\n\
 outputstrfpi PROTO : DWORD\n\
 outputflfpi  PROTO : REAL4\n\
 outputintfpi PROTO : DWORD\n\
 msin  PROTO : REAL4\n\
 mcos  PROTO : REAL4\n\
 mtan  PROTO : REAL4\n\
 mctan PROTO : REAL4\n\
 mln   PROTO : REAL4\n\
 mabs  PROTO : DWORD\n\
 msqr  PROTO : DWORD\n\
 strlenfpi PROTO : DWORD\n\
 strfind   PROTO : DWORD, : DWORD"
#define PARDEF							"DEFP"
#define GLMUV(parm1, parm2)				"\t\tMOV\t" << parm1 << ',' << parm2
#define GLADD(parm1, parm2)				"\t\tADD\t" << parm1 << ',' << parm2
#define GLSUB(parm1, parm2)				"\t\tSUB\t" << parm1 << ',' << parm2
#define GLMUL(parm1)					"\t\tMUL\t" << parm1
#define GLDIV(parm1)					"\t\tDIV\t" << parm1
#define MOV(parm1, parm2, parm3, parm4)	"\t\tMOV\t" << parm1 << parm2 << ',' << parm3 << parm4
#define PMOV(parm1, parm2, parm3,parm4) "\t\tMOV\t" << parm1 " , " << parm2 << " " << parm3 << " + " << parm4
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
#define TSTR							"DB"
#define TBL								"DWORD"
#define INTLIT(num)						"\tINTLIT" << num << '\t' << '\t' << "DWORD" << '\t'
#define STRLIT(num)						"\tSTRLIT" << num << '\t' << '\t' << "DB" <<'\t'
#define FLLIT(num)						"\tFLLIT" << num << '\t' << '\t' << "REAL4" << '\t'
#define BLLIT(num)						"\tBLLIT" << num << '\t' << '\t' << "DWORD" << '\t'
#define VARINT(name)					'\t' << name << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define VARSTR(name)					'\t' << name << '\t' << '\t' << '\t' << "DWORD" << '\t'<< 00
#define VARFL(name)						'\t' << name << '\t' << '\t' << '\t' << "REAL4" << '\t'<< "0.0"
#define VARBL(name)						'\t' << name << '\t' << '\t' << '\t' << "DWORD" << '\t'<< "0"
#define VRINT(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define VRSTR(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DB" << '\t'<< 255 << " dup(0)"
#define VRFL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "REAL4" << '\t'<< "0.0"
#define VRBL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t'<< "0"
#define DEFPINT(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define DEFPSTR(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define DEFPFL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "REAL4" << '\t' << "0"
#define DEFPBL(par1, par2)				'\t' << par1 << par2 << '\t' << '\t' << '\t' << "DWORD" << '\t' << "0"
#define PROC(namedef)					'\t' << namedef << " PROC "	
#define ENDP(name)						'\t' << name << " ENDP"	
#define EMPTY							""
#define ISGLOBAL(str)					str[0] == '$'
#define EXITMAIN						"\tPUSH OFFSET system_pause_fpi\n\tcall inputfpi\n\tPUSH 0\n\tCALL ExitProcess\n"
#define ENDMAIN							"end main"
#define CMP(par1, par2, par3, par4) 	"\t\tCMP\t"<< par1 << par2 << ',' << par3 << par4
#define JB(parm1, parm2)				"\t\tJB\t\t" << parm1 << parm2 
#define JE(parm1, parm2)				"\t\tJE\t\t" << parm1 << parm2 
#define JNE(parm1, parm2)				"\t\tJNE\t\t" << parm1 << parm2 
#define JA(parm1, parm2)				"\t\tJA\t\t" << parm1 << parm2 
#define JMP(parm1, parm2)				"\t\tJMP\t\t" << parm1 << parm2 
#define CALL(parm)						"\t\tCALL\t\t" << parm
#define FLD(parm)						"\t\tFLD\t["  << parm << ']'
#define FSTP(parm)						"\t\tFSTP\t[" << parm << ']'
#define FLDREG(parm)					"\t\tFLD\t"  << parm
#define FSTPREG(parm)					"\t\tFSTP\tdword ptr [" << parm << ']'
#define FADD							"\t\tFADD"
#define FDIV							"\t\tFDIV"
#define FSUB							"\t\tFSUB"
#define FMUL							"\t\tFMUL"
#define REPMOVSB						"\t\tREP MOVSB"

bool CG::isStanLib(char * nameid)
{
	if (!strcmp(nameid, MLN) || !strcmp(nameid, MSIN) || !strcmp(nameid, MCOS) || !strcmp(nameid, MTAN) || !strcmp(nameid, MCTAN) ||
		!strcmp(nameid, STRLEN) || !strcmp(nameid, STRFIND) || !strcmp(nameid, MABS) || !strcmp(nameid, MSQR)) return true;
	else return false;
}

void CG::StartGeneration(LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log)
{
	OUT << ASMTEMPLATE << ENDL;
	OUT << INCLUDELIB << ENDL
	addLiterals(idTable, log);
	addData(lexTable, idTable, log);
	protImplem(lexTable, idTable, log);
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
				idTable.table[i].countlex = numint;
				OUT << INTLIT(numint++) << idTable.table[i].value.vint << ENDL;
				break;
			case IT::STR:
				idTable.table[i].countlex = numstr;
				OUT << STRLIT(numstr++) << '"' << idTable.table[i].value.vstr.str << '"' << ", 0" << ENDL;
				break;
			case IT::FL: 
				idTable.table[i].countlex = numfl;
				OUT << FLLIT(numfl++) << idTable.table[i].value.vfl << ENDL;
				break;
			case IT::BL: 
				idTable.table[i].countlex = numbl;
				OUT << BLLIT(numbl++) << idTable.table[i].value.vbool<< ENDL;
				break;
			}
		}
	}
}

void CG::addData(LT::LexTable& lexTable, IT::IdTable & idTable, Log::LOG log)
{
	OUT << ASM_DATA << ENDL;
	char fun[300];
	OUT << VRSTR(EMPTY, "system_pause_fpi") << ENDL;;
	for (int i = 0; i < idTable.head; ++i)
	{
		if (idTable.table[i].idtype == IT::IDTYPE::F)
		{
			strcpy(fun, "foo__");
			strcat(fun, idTable.table[i].id);
		}
		if (idTable.table[i].idtype == IT::IDTYPE::V)
		{
			char idName[300];
			IT::retIDwithScope(idTable, lexTable, idTable.table[i].idxfirstLE, idName);
			switch (idTable.table[i].iddatatype)
			{
			case IT::INT:
				OUT << VRINT(EMPTY,idName) << ENDL;
				break;
			case IT::STR:
				OUT << VRSTR(EMPTY, idName) << ENDL;
				break;
			case IT::FL:
				OUT << VRFL(EMPTY, idName) << ENDL;
				break;
			case IT::BL:
				OUT << VRBL(EMPTY, idName) << ENDL; 
				break;
			}
		}
	}
}

void CG::protImplem(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log)
{
	int numMain = 0;
	OUT << ASM_CODE << ENDL;
	for (int i = 0; i < lexTable.head; i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_MAIN)
		{
			OUT << PROC("main") << ENDL;
			i = releaseFun(lexTable, idTable, log, i, (char*)"programm");
			OUT << ENDP("main") << ENDL;
			OUT << ENDMAIN << ENDL
		}
		if (lexTable.table[i-1].lexema[GETLEX] == LEX_FUNCTION && lexTable.table[i].lexema[GETLEX] == LEX_ID)
		{
			int amountarg = getAmountPar(idTable, lexTable.table[i].idxTI);
			IT::Entry itentry = GETIDFROMLT(i);
			char nameFun[300];
			IT::retNameFun(idTable, lexTable, i, nameFun);
			OUT << PROC(nameFun);
			i++;
			for (int j = amountarg; j != 0;i++)
			{
				if (lexTable.table[i].lexema[GETLEX] == LEX_ID)
				{
					
					switch (GETIDFROMLT(i).iddatatype)
					{
					case IT::INT:
						if (j == 1) OUT << nameFun << GETIDFROMLT(i).id << " : DWORD " << ENDL
						else OUT << nameFun << GETIDFROMLT(i).id << " : DWORD, ";
						j--;
						break;
					case IT::STR:
						if (j == 1) OUT << nameFun << GETIDFROMLT(i).id << " : DWORD " << ENDL
						else OUT << nameFun << GETIDFROMLT(i).id << " : DWORD, ";
						j--;
						break;
					case IT::FL:
						if (j == 1) OUT << nameFun << GETIDFROMLT(i).id << " : REAL4 " << ENDL
						else OUT << nameFun << GETIDFROMLT(i).id << " : REAL4, ";
						j--;
						break;
					case IT::BL:
						if (j == 1) OUT << nameFun << GETIDFROMLT(i).id << " : DWORD "<< ENDL
						else OUT << nameFun << GETIDFROMLT(i).id << " : DWORD, ";
						j--;
						break;
					}
				}
			}

			i = releaseFun(lexTable, idTable, log, i, itentry.id);
			OUT << ENDP(nameFun) << ENDL;
		}
	}
	OUT << ENDL;
}

int CG::releaseFun(LT::LexTable & lexTable, IT::IdTable & idTable, Log::LOG log, int pos, char *idfun)
{
	bool isInverse = false;
	std::vector<LabelStructFPI> stackblock;
	int numBlock = 0;
	int posBlock = 0;
	std::string nameBlock;
	LT::CO co;
	IT::Entry lentry, rentry;
	char buffint[20];
	char *idname1 = new char [300];
	char *idname2 = new char[300];
	for (int i = pos+1;; i++)
	{
		if (lexTable.table[i].lexema[GETLEX] == LEX_MAIN || lexTable.table[i].lexema[GETLEX] == LEX_FUNCTION || i + 1 == lexTable.head)
		{
			if (i + 1 == lexTable.head) OUT << EXITMAIN << ENDL
			else OUT << RET << ENDL;
			delete idname1;
			delete idname2;
			return i-1;
		}
		switch (lexTable.table[i].lexema[GETLEX])
		{
			case LEX_BRACELET: 
				if (stackblock.empty()) continue;
				posBlock = stackblock.back()._posstruct;
				switch (stackblock.back()._tbstruct)
				{
				case typeBlock::f: 
					doExpression(lexTable, idTable, posBlock + 11, idname1, idname2, log);
					lentry = GETIDFROMLT(posBlock + 6);
					rentry = GETIDFROMLT(posBlock + 8);
					co = CURRLE(posBlock + 7).co;
					isInverse = false;
					cmpfun(lentry, rentry, idname1, idname2, lexTable, idTable, log);
					jumpfun(isInverse, co, stackblock.back()._namestruct, log);
					OUT << "end" << LABEL(stackblock.back()._namestruct) << ENDL
					break;
				case typeBlock::w:
				case typeBlock::ut: 
					isInverse = stackblock.back()._tbstruct == typeBlock::ut ? true : false;
					lentry = GETIDFROMLT(posBlock + 2);
					rentry = GETIDFROMLT(posBlock + 4);
					co = CURRLE(posBlock + 3).co;
					cmpfun(lentry, rentry, idname1, idname2, lexTable, idTable, log);
					jumpfun(isInverse, co, stackblock.back()._namestruct, log);
					OUT << "end" << LABEL(stackblock.back()._namestruct) << ENDL
					break;
				case typeBlock::i: 
				case typeBlock::ul: 
					
					if (CURRLEX(i + 1) != LEX_ALIAS)	OUT << "end" << LABEL(stackblock.back()._namestruct) << ENDL
					else
					{
						nameBlock = "alias" + std::string(buffint);
						OUT << JMP("end", nameBlock) << ENDL
						OUT << "end" << LABEL(stackblock.back()._namestruct) << ENDL
					}
					break;
				case typeBlock::a:
					OUT << "end" << LABEL(stackblock.back()._namestruct) << ENDL
					break;
				}
				stackblock.pop_back();
				break;
			case LEX_INPUT:
				IT::retIDwithScope(idTable, lexTable, i + 1, idname1);
				OUT << PUSH2("OFFSET ",idname1) << ENDL
				OUT << CALL("inputfpi") << ENDL
				break;
			case LEX_OUTPUT: 
				if (GETIDFROMLT(i + 1).idtype == IT::IDTYPE::L) IT::retIDlit(GETIDFROMLT(i + 1), idname1);
				else IT::retIDwithScope(idTable, lexTable, i + 1, idname1);
				switch (GETIDFROMLT(i+1).iddatatype)
				{
				case IT::IDDATATYPE::INT:
					OUT << PUSH(idname1) << ENDL
					OUT << CALL("outputintfpi") << ENDL
					break;
				case IT::IDDATATYPE::STR:
					OUT << PUSH2("OFFSET ", idname1) << ENDL
					OUT << CALL("outputstrfpi") << ENDL
					break;
				case IT::IDDATATYPE::FL :
					OUT << PUSH(idname1) << ENDL
					OUT << CALL("outputflfpi") << ENDL
					break;
				}
				break;
			case LEX_CYCLE: 
				if (CURRLE(i).cycling.cycle == LT::Cycle::ut)
				{
					_itoa(numBlock++, buffint, 10);
					nameBlock = "until" + std::string(buffint);
					stackblock.push_back(LabelStructFPI(nameBlock, i, typeBlock::ut));
				}
				else 
				{
					_itoa(numBlock++, buffint, 10);
					nameBlock = "while" + std::string(buffint); 
					stackblock.push_back(LabelStructFPI(nameBlock , i, typeBlock::w));
				}
				OUT << LABEL(stackblock.back()._namestruct) << ENDL
				break;
			case LEX_FOR: 
				_itoa(numBlock++, buffint, 10);
				nameBlock = "for" + std::string(buffint);
				stackblock.push_back(LabelStructFPI(nameBlock, i, typeBlock::f));
				i = doExpression(lexTable, idTable, i + 3, idname1, idname2, log);

				OUT << LABEL(stackblock.back()._namestruct) << ENDL
				for (;; i++)
				{
					if (CURRLEX(i) == LEX_LEFTBRACE) break;
				}
				break;
			case LEX_EQUAL: 
				i =  doExpression(lexTable, idTable, i, idname1, idname2, log);
				break;
			case LEX_BRANCH: 
				if (CURRLE(i).branching.br == LT::Branch::i)
				{
					_itoa(numBlock++, buffint, 10);
					nameBlock = "if0" + std::string(buffint);
					stackblock.push_back(LabelStructFPI(nameBlock, i, typeBlock::i));
				}
				else
				{
					_itoa(numBlock++, buffint, 10);
					nameBlock = "unless" + std::string(buffint);
					stackblock.push_back(LabelStructFPI(nameBlock, i, typeBlock::ul));
				}
				lentry = GETIDFROMLT(i + 2);
				rentry = GETIDFROMLT(i + 4);
				co = CURRLE(i + 3).co;
				isInverse = stackblock.back()._tbstruct == typeBlock::ul ? true : false;
				cmpfun(lentry, rentry, idname1, idname2, lexTable, idTable, log);
				jumpfun(isInverse, co, stackblock.back()._namestruct, log);
				OUT << LABEL(stackblock.back()._namestruct) << ENDL
				break;
			case LEX_ALIAS:
				stackblock.push_back(LabelStructFPI(nameBlock, i, typeBlock::a));
				break;
			case LEX_RETURN:
				i = doExpression(lexTable, idTable, i, idname1, idname2, log);
				break;
		}
	}
	delete idname1;
	delete idname2;
	return -1;
}

void CG::jumpfun(bool isInverse, LT::CO co, std::string strlable, Log::LOG log)
{
	if (isInverse) 
	{
		switch (co)
		{
		case LT::CO::e:
			OUT << JNE(EMPTY, strlable) << ENDL
				OUT << JE("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::ne:
			OUT << JE(EMPTY, strlable) << ENDL
				OUT << JNE("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::le:
			OUT << JA(EMPTY, strlable) << ENDL
				OUT << JE(EMPTY, strlable) << ENDL
				OUT << JB("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::me:
			OUT << JB(EMPTY, strlable) << ENDL
				OUT << JE(EMPTY, strlable) << ENDL
				OUT << JA("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::l:
			OUT << JA(EMPTY, strlable) << ENDL
				OUT << JB("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::m:
			OUT << JB(EMPTY, strlable) << ENDL
				OUT << JA("end", strlable) << ENDL
				OUT << ENDL
				break;
		}
	}
	else {
		switch (co)
		{
		case LT::CO::e:
			OUT << JE(EMPTY, strlable) << ENDL
				OUT << JNE("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::ne:
			OUT << JE(EMPTY, strlable) << ENDL
				OUT << JNE("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::le:
			OUT << JB(EMPTY, strlable) << ENDL
				OUT << JE(EMPTY, strlable) << ENDL
				OUT << JA("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::me:
			OUT << JA(EMPTY, strlable) << ENDL
				OUT << JE(EMPTY, strlable) << ENDL
				OUT << JB("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::l:
			OUT << JB(EMPTY, strlable) << ENDL
				OUT << JA("end", strlable) << ENDL
				OUT << ENDL
				break;
		case LT::CO::m:
			OUT << JA(EMPTY, strlable) << ENDL
				OUT << JB("end", strlable) << ENDL
				OUT << ENDL
				break;
		}
	}
}

int  CG::doExpression(LT::LexTable& lexTable, IT::IdTable& idTable, int numLT, char* idname1, char* idname2, Log::LOG log)
{
	int  i;
	bool flagReturn = false;
	int countSizeOfStr = 0;
	char buffInt[50];
	if (CURRLEX(numLT) == LEX_RETURN)
	{
		i = numLT + 1;
		flagReturn = !flagReturn;
	}
	else
	{
		i = numLT + 1;
		IT::retIDwithScope(idTable, lexTable, i-2, idname2);
	}
	int numID = 0;
	switch (GETIDFROMLT(i).iddatatype)
	{
	case IT::IDDATATYPE::INT:
		numID = GETIDFROMLT(i).idxfirstLE;
		for (;; i++)
		{
			if (CURRLEX(i) == '^' || CURRLEX(i) == LEX_SEMICOLON || (CURRLEX(i) == LEX_RIGHTHESIS && CURRLEX(i + 1) == LEX_LEFTBRACE)) break;
			if (CURRLEX(i) == LEX_ID)
			{
				IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
				OUT << PUSH(idname1) << ENDL
			}
			if (CURRLEX(i) == '@')
			{
				int posFun = i;
				for (int j = 0; j < CURRLE(posFun).amountArg; i++)
				{
					if (CURRLEX(i) == LEX_LITERAL)
					{
						IT::retIDlit(GETIDFROMLT(i), idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR)
						{
							OUT << PUSH2("OFFSET ", idname1) << ENDL
						}
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
					if (CURRLEX(i) == LEX_ID)
					{
						IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR)
						{
							OUT << PUSH2("OFFSET ", idname1) << ENDL
						}
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
				}
				if (isStanLib(GETIDFROMLT(posFun).id)) strcpy(idname1, GETIDFROMLT(posFun).id);
				else IT::retNameFun(idTable, lexTable, posFun, idname1);
				if (!strcmp(GETIDFROMLT(posFun).id, "strlen")) strcat(idname1, "fpi");
				OUT << CALL(idname1) << ENDL;
				OUT << PUSH("EAX") << ENDL;
			}
			if (CURRLEX(i) == LEX_LITERAL)
			{
				IT::retIDlit(GETIDFROMLT(i), idname1);
				OUT << PUSH(idname1) << ENDL
			}
			if (CURRLEX(i) == LEX_OPERATION)
			{
				switch (CURRLE(i).operation)
				{
				case PLUS:
					OUT << POP("EDX") << ENDL
					OUT << POP("EBX") << ENDL
					OUT << GLADD("EBX", "EDX") << ENDL
					OUT << PUSH("EBX") << ENDL
					break;
				case MINUS:
					OUT << POP("EDX") << ENDL
					OUT << POP("EBX") << ENDL
					OUT << GLSUB("EBX", "EDX") << ENDL
					OUT << PUSH("EBX") << ENDL
					break;
				case STAR:
					OUT << POP("EBX") << ENDL
					OUT << POP("EAX") << ENDL
					OUT << MOV(EMPTY, "EDX", EMPTY, 0) << ENDL
					OUT << GLMUL("EBX") << ENDL
					OUT << MOV(EMPTY, "EBX", EMPTY, "EAX") << ENDL
					OUT << PUSH("EBX") << ENDL
					break;
				case DIRSLASH:
					OUT << POP("EBX") << ENDL
					OUT << POP("EAX") << ENDL
					OUT << MOV(EMPTY, "EDX", EMPTY, 0) << ENDL
					OUT << GLDIV("EBX") << ENDL
					OUT << MOV(EMPTY, "EBX", EMPTY, "EAX") << ENDL
					OUT << PUSH("EBX") << ENDL
					break;
				}
			}
		}
		OUT << POP("EAX") << ENDL;
		if(!flagReturn) OUT << MOV(EMPTY, idname2, EMPTY, "EAX") << ENDL
		break;
	case IT::IDDATATYPE::FL:
		numID = GETIDFROMLT(i).idxfirstLE;
		for (;; i++)
		{
			if (CURRLEX(i) == '^' || CURRLEX(i) == LEX_SEMICOLON || (CURRLEX(i) == LEX_RIGHTHESIS && CURRLEX(i + 1) == LEX_LEFTBRACE)) break;
			if (CURRLEX(i) == LEX_ID)
			{
				IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
				OUT << FLDREG(idname1) << ENDL
			}
			if (CURRLEX(i) == '@')
			{
				int posFun = i;
				for (int j = 0; j < CURRLE(posFun).amountArg; i++)
				{
					if (CURRLEX(i) == LEX_LITERAL)
					{
						IT::retIDlit(GETIDFROMLT(i), idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR) OUT << PUSH2("OFFSET ", idname1) << ENDL
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
					if (CURRLEX(i) == LEX_ID)
					{
						IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR) OUT << PUSH2("OFFSET ", idname1) << ENDL
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
				}
				if (isStanLib(GETIDFROMLT(posFun).id)) strcpy(idname1, GETIDFROMLT(posFun).id);
				else IT::retNameFun(idTable, lexTable, posFun, idname1);

				OUT << CALL(idname1) << ENDL;
				OUT << FLDREG("DWORD PTR [EAX]") << ENDL;
			}
			if (CURRLEX(i) == LEX_LITERAL)
			{
				IT::retIDlit(GETIDFROMLT(i), idname1);
				OUT << FLD(idname1) << ENDL
			}
			if (CURRLEX(i) == LEX_OPERATION)
			{
				switch (CURRLE(i).operation)
				{
				case PLUS:
					OUT << FADD << ENDL
					break;
				case MINUS:
					OUT << FSUB << ENDL
					break;
				case STAR:
					OUT << FMUL << ENDL
					break;
			case DIRSLASH:
					OUT << FDIV << ENDL
					break;
				}
			}
		}
		OUT << FSTP(idname2) << ENDL
		if (flagReturn) OUT << MOV(EMPTY, "EAX", "OFFSET ", idname2) << ENDL
		break;
	case IT::IDDATATYPE::STR:
		
		if (flagReturn)
		{
			if (CURRLEX(numID + 1) == LEX_LITERAL || CURRLEX(numID + 1) == LEX_LITERAL) throw ERROR_THROW_IN(700, CURRLE(numID).sn, -1);
			if (CURRLEX(numID) == LEX_LITERAL) IT::retIDlit(GETIDFROMLT(numID), idname2);
			if (CURRLEX(numID) == LEX_ID) IT::retIDwithScope(idTable, lexTable, numID, idname2);
			OUT << MOV(EMPTY, "EAX", "OFFSET ", idname2) << ENDL
			break;
		}
		numID = GETIDFROMLT(i - 2).idxfirstLE;
		for (;; i++)
		{
			if (CURRLEX(i) == '^' || CURRLEX(i) == LEX_SEMICOLON || (CURRLEX(i) == LEX_RIGHTHESIS && CURRLEX(i + 1) == LEX_LEFTBRACE)) break;
			if (CURRLEX(i) == LEX_ID)
			{
				IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
				if (GETIDFROMLT(i).idtype == IT::IDTYPE::P)
				{
					OUT << MOV(EMPTY, "ESI", EMPTY, idname1) << ENDL
				}
				else OUT << MOV(EMPTY, "ESI", "OFFSET ", idname1) << ENDL
				OUT << PMOV("EDI", "OFFSET", idname2, countSizeOfStr) << ENDL;
				countSizeOfStr += GETIDFROMLT(i).value.vstr.len;
				_itoa(GETIDFROMLT(i).value.vstr.len+1, buffInt, 10);
				OUT << MOV(EMPTY, "ECX", EMPTY, buffInt) << ENDL
				OUT << REPMOVSB << ENDL
				GETIDFROMLT(numID).value.vstr.len = countSizeOfStr;
			}
			if (CURRLEX(i) == LEX_LITERAL)
			{
				IT::retIDlit(GETIDFROMLT(i), idname1);
				OUT << MOV(EMPTY, "ESI", "OFFSET ", idname1) << ENDL
				OUT << PMOV("EDI", "OFFSET ", idname2, countSizeOfStr) << ENDL;
				countSizeOfStr += GETIDFROMLT(i).value.vstr.len;
				_itoa(GETIDFROMLT(i).value.vstr.len+1, buffInt, 10);
				OUT << MOV(EMPTY, "ECX", EMPTY, buffInt) << ENDL
				OUT << REPMOVSB << ENDL
				GETIDFROMLT(numID).value.vstr.len = countSizeOfStr;
			}
		}
		break;
	case IT::IDDATATYPE::BL:
		numID = GETIDFROMLT(i).idxfirstLE;
		for (;; i++)
		{
			if (CURRLEX(i) == '^' || CURRLEX(i) == LEX_SEMICOLON || (CURRLEX(i) == LEX_RIGHTHESIS && CURRLEX(i + 1) == LEX_LEFTBRACE)) break;
			if (CURRLEX(i) == LEX_ID)
			{
				IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
				OUT << PUSH(idname1) << ENDL
			}
			if (CURRLEX(i) == '@')
			{
				int posFun = i;
				for (int j = 0; j < CURRLE(posFun).amountArg; i++)
				{
					if (CURRLEX(i) == LEX_LITERAL)
					{
						IT::retIDlit(GETIDFROMLT(i), idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR) OUT << PUSH2("OFFSET ",idname1) << ENDL
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
					if (CURRLEX(i) == LEX_ID)
					{
						IT::retIDwithScope(idTable, lexTable, GETIDFROMLT(i).idxfirstLE, idname1);
						if (GETIDFROMLT(i).iddatatype == IT::IDDATATYPE::STR) OUT << PUSH2("OFFSET ", idname1) << ENDL
						else OUT << PUSH(idname1) << ENDL
						j++;
					}
				}
				IT::retNameFun(idTable, lexTable, posFun, idname1);
				OUT << CALL(idname1) << ENDL;
				OUT << PUSH("EAX") << ENDL;
			}
			if (CURRLEX(i) == LEX_LITERAL)
			{
				IT::retIDlit(GETIDFROMLT(i), idname1);
				OUT << PUSH(idname1) << ENDL
			}
		}
		OUT << POP("EAX") << ENDL;
		if (!flagReturn) OUT << MOV(EMPTY, idname2, EMPTY, "EAX") << ENDL
		break;
	}
	return i;
}

void CG::cmpfun(IT::Entry lentry, IT::Entry rentry, char * idname1, char * idname2, LT::LexTable& lexTable, IT::IdTable& idTable, Log::LOG log)
{
	if (lentry.idtype == IT::IDTYPE::V && rentry.idtype == IT::IDTYPE::V)
	{
		IT::retIDwithScope(idTable, lexTable, lentry.idxfirstLE, idname1);
		IT::retIDwithScope(idTable, lexTable, rentry.idxfirstLE, idname2);
		OUT << MOV(EMPTY, "EAX",EMPTY ,idname1) << ENDL
		OUT << CMP(EMPTY, "EAX", EMPTY, idname2) << ENDL
	}
	if (lentry.idtype == IT::IDTYPE::L && rentry.idtype == IT::IDTYPE::V)
	{
		IT::retIDwithScope(idTable, lexTable, rentry.idxfirstLE, idname2);
		IT::retIDlit(lentry, idname1);
		OUT << MOV(EMPTY, "EAX", EMPTY, idname1) << ENDL
		OUT << CMP(EMPTY, "EAX", EMPTY, idname2) << ENDL
	}
	if (lentry.idtype == IT::IDTYPE::V && rentry.idtype == IT::IDTYPE::L)
	{
		IT::retIDwithScope(idTable, lexTable, lentry.idxfirstLE, idname1);
		IT::retIDlit(rentry, idname2);
		OUT << MOV(EMPTY, "EAX", EMPTY, idname1) << ENDL
		OUT << CMP(EMPTY, "EAX", EMPTY, idname2) << ENDL
	}
	if (lentry.idtype == IT::IDTYPE::L && rentry.idtype == IT::IDTYPE::L)
	{
		IT::retIDlit(lentry, idname1);
		IT::retIDlit(rentry, idname2);
		OUT << MOV(EMPTY, "EAX", EMPTY, idname1) << ENDL
		OUT << CMP(EMPTY, "EAX", EMPTY, idname2) << ENDL
	}
}
