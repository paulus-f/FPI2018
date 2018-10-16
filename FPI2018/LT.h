#pragma once
#include "IT.h"
#include "Log.h"

#define EMPTYSTR ""
#define INTEGER "integer"
#define STRING "string"
#define RETURN "return"
#define DECLARE "declare"
#define PRINT "print"
#define MAIN "main"
#define NOTYPE "NOTYPE"
#define FUNCTION "function"
#define STRLEN "strlen"
#define SUBSTR "substr"
#define SEMICOLON ';'
#define COMMA ','
#define LEFTBRACET '{'
#define RIGHTBRACELET '}'
#define LEFTHESIS '('
#define RIGHTHESIS ')'
#define PLUS '+'
#define MINUS '-'
#define STAR '*'
#define EQUAL '='
#define QUOTES 34
#define DIRSLASH '/'
#define SPACE ' '
#define NEWLINE '\n'
#define ENDNULL '\0'
#define LEX_FIXSIZE 1
#define GETLEX 0
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_TYPE 't'
#define LEX_ID 'i'
#define LEX_MAIN 'm'
#define LEX_LITERAL 'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE 'd'
#define LEX_RETURN 'r'
#define LEX_PRINT 'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_OPERATION 'v'
#define LEX_EQUAL '='
#define LEX_QUOTES '\"' // '"'
#define LEX_DIRSLASH '/'

namespace LT
{
	struct Entry
	{
		char lexema[LEX_FIXSIZE];
		int sn;
		int idxTI;
		short amountArg;
		char operation = NULL;
	};

	Entry Lex(char lexema, int numstr, int idx);

	Entry retLex(char lex, int numstr, int idx);

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		int head = 0;
	};

	bool isOperOrSep(char lit);

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

	bool IsIntLit(char *str);
	bool IsStrLit(char *str);

	void LogLA(LexTable& lexTable, Log::LOG log);

	void Delete(LexTable &lextable);
}
