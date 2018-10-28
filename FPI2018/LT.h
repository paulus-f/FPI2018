#pragma once
#include "IT.h"
#include "Log.h"

#define EMPTYSTR ""
#define INTEGER "int"
#define STRING "str"
#define LESS '<'
#define MORE '>'
#define RETURN "=>"
#define INPUT "p<"
#define OUTPUT "p>"
#define BOOL "bool"
#define MSIN "msin"
#define MCOS "mcos"
#define MTAN "mtan"
#define MCTAN "mctan"
#define STRLEN "strlen"
#define SUBSTR "substr"
#define STRFIND "strfind"
#define MABS "mabs"
#define MSQR "msqr"
#define MLN "mln"
#define FLOAT "fl"
#define MAIN "program"
#define NOTYPE "NOTYPE"
#define FUNCTION "def"
//#define STRLEN "strlen"
//#define SUBSTR "substr"
#define SEMICOLON ';'
#define COMMA ','
#define FALSE false
#define TRUE true
#define LEFTBRACET '{'
#define RIGHTBRACELET '}'
#define LEFTHESIS '('
#define RIGHTHESIS ')'
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define EXCLAM '!'
#define EQUAL '='
#define QUOTES 34
#define DIRSLASH '/'
#define SPACE ' '
#define NEWLINE '\n'
#define ENDNULL '\0'
#define TAB '\t'
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
#define LEX_FIXSIZE 1
#define GETLEX 0
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_BOOL 't'
#define LEX_FLOAT 't'
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_TYPE 't'
#define LEX_ID 'i'
#define LEX_BRANCH 'b'
#define LEX_ALIAS 'a'
#define LEX_MAIN 'm'
#define LEX_ÑOMPARISONOPER 's'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_RETURN 'r'
#define LEX_OUTPUT 'o'
#define LEX_INPUT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_CYCLE 'c'
#define LEX_FOR 'x'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_OPERATION 'v'
#define LEX_EQUAL '='
#define LEX_QUOTES '\"' 
#define LEX_DIRSLASH '/'
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
namespace LT
{
	enum CO { m = 1, l = 2, e = 3, ne = 4, me = 5, le = 6};

	struct Entry
	{
		char lexema[LEX_FIXSIZE];
		int sn;
		int idxTI;
		short amountArg;
		char operation = NULL;
		CO co;
	};

	Entry retLex(char lex, int numstr, int idx);

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		int head = 0;
	};

	bool isOperOrSep(char lit);
	bool isCO(char lit);

	LexTable Create(
		int size
	);

	void LexicalAnalysis(char* str, LexTable& lexTable, IT::IdTable idTable, Log::LOG log);

	void Add(
		LexTable& lextable,
		Entry entry
	);

	Entry GetEntry(
		LexTable& lextable,
		int n
	);

	void LogLA(LexTable& lexTable, Log::LOG log);

	void Delete(LexTable &lextable);
}
