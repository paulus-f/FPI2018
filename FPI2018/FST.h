#include "stdafx.h"

#define FST_E 3,	\
	FST::NODE(1, FST::RELATION('=', 1)),\
	FST::NODE(1, FST::RELATION('=', 2)),\
	FST::NODE()
#define FST_NE 3,	\
	FST::NODE(1, FST::RELATION('!', 1)),\
	FST::NODE(1, FST::RELATION('=', 2)),\
	FST::NODE()
#define FST_M 2,	\
	FST::NODE(1, FST::RELATION('>', 1)),\
	FST::NODE()
#define FST_L 2,	\
	FST::NODE(1, FST::RELATION('<', 1)),\
	FST::NODE()
#define FST_LE 3,	\
	FST::NODE(1, FST::RELATION('<', 1)),\
	FST::NODE(1, FST::RELATION('=', 2)),\
	FST::NODE()
#define FST_ME 3,	\
	FST::NODE(1, FST::RELATION('>', 1)),\
	FST::NODE(1, FST::RELATION('=', 2)),\
	FST::NODE()
#define FST_IF 3,	\
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('f', 2)),\
	FST::NODE()
#define FST_UNLESS 7,	\
	FST::NODE(1, FST::RELATION('u', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE(1, FST::RELATION('s', 6)), \
	FST::NODE()
#define FST_WHILE 6,	\
	FST::NODE(1, FST::RELATION('w', 1)),\
	FST::NODE(1, FST::RELATION('h', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE(1, FST::RELATION('e', 5)),\
	FST::NODE()
#define FST_UNTIL 6,	\
	FST::NODE(1, FST::RELATION('u', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('l', 5)),\
	FST::NODE()
#define FST_FOR 4,	\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE()
#define FST_UNLESS 7,	\
	FST::NODE(1, FST::RELATION('u', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE(1, FST::RELATION('s', 6)), \
	FST::NODE()
#define FST_ALIAS 6,	\
	FST::NODE(1, FST::RELATION('a', 1)),\
	FST::NODE(1, FST::RELATION('l', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('a', 4)),\
	FST::NODE(1, FST::RELATION('s', 5)),\
	FST::NODE()
#define FST_INT 4,	\
	FST::NODE(1, FST::RELATION('i', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE()
#define FST_FLOAT 3,	\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('l', 2)),\
	FST::NODE()
#define FST_STR 4,	\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE()
#define FST_BOOL 5,	\
	FST::NODE(1, FST::RELATION('b', 1)),\
	FST::NODE(1, FST::RELATION('o', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE()
#define FST_FUN 4,	\
	FST::NODE(1, FST::RELATION('d', 1)),\
	FST::NODE(1, FST::RELATION('e', 2)),\
	FST::NODE(1, FST::RELATION('f', 3)),\
	FST::NODE()
#define FST_RET 2,	\
	FST::NODE(1, FST::RELATION('r', 1)),\
	FST::NODE()
#define FST_OUTPUT 3,	\
	FST::NODE(1, FST::RELATION('p', 1)),\
	FST::NODE(1, FST::RELATION('<', 2)),\
	FST::NODE()
#define FST_INPUT 3,	\
	FST::NODE(1, FST::RELATION('p', 1)),\
	FST::NODE(1, FST::RELATION('>', 2)),\
	FST::NODE()
#define FST_STRLEN 7,	\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('l', 4)),\
	FST::NODE(1, FST::RELATION('e', 5)),\
	FST::NODE(1, FST::RELATION('n', 6)),\
	FST::NODE()
#define FST_STRFIND 8,	\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('f', 4)),\
	FST::NODE(1, FST::RELATION('i', 5)),\
	FST::NODE(1, FST::RELATION('n', 6)),\
	FST::NODE(1, FST::RELATION('d', 7)),\
	FST::NODE()
#define FST_MSIN 5, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('s', 2)),\
	FST::NODE(1, FST::RELATION('i', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE()
#define FST_MCOS 5, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('c', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE()

#define FST_MTAN 5, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('a', 3)),\
	FST::NODE(1, FST::RELATION('n', 4)),\
	FST::NODE()

#define FST_MCTAN 6, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('c', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('a', 4)),\
	FST::NODE(1, FST::RELATION('n', 5)),\
	FST::NODE()

#define FST_MABS 5, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('b', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE()

#define FST_MLN 4, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('l', 2)),\
	FST::NODE(1, FST::RELATION('n', 3)),\
	FST::NODE()

#define FST_MSQR 5, \
	FST::NODE(1, FST::RELATION('m', 1)),\
	FST::NODE(1, FST::RELATION('s', 2)),\
	FST::NODE(1, FST::RELATION('q', 3)),\
	FST::NODE(1, FST::RELATION('r', 4)),\
	FST::NODE()

#define FST_SUBSTR 7,	\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('u', 2)),\
	FST::NODE(1, FST::RELATION('b', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE(1, FST::RELATION('t', 5)),\
	FST::NODE(1, FST::RELATION('r', 6)),\
	FST::NODE()

#define FST_STRFIND 8,	\
	FST::NODE(1, FST::RELATION('s', 1)),\
	FST::NODE(1, FST::RELATION('t', 2)),\
	FST::NODE(1, FST::RELATION('r', 3)),\
	FST::NODE(1, FST::RELATION('f', 4)),\
	FST::NODE(1, FST::RELATION('i', 5)),\
	FST::NODE(1, FST::RELATION('n', 6)),\
	FST::NODE(1, FST::RELATION('d', 7)),\
	FST::NODE()

#define FST_UNTIL 6,	\
	FST::NODE(1, FST::RELATION('u', 1)),\
	FST::NODE(1, FST::RELATION('n', 2)),\
	FST::NODE(1, FST::RELATION('t', 3)),\
	FST::NODE(1, FST::RELATION('i', 4)),\
	FST::NODE(1, FST::RELATION('l', 5)),\
	FST::NODE()


#define FST_MAIN 8,	\
	FST::NODE(1, FST::RELATION('P', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('o', 3)),\
	FST::NODE(1, FST::RELATION('g', 4)),\
	FST::NODE(1, FST::RELATION('r', 5)),\
	FST::NODE(1, FST::RELATION('a', 6)),\
	FST::NODE(1, FST::RELATION('m', 7)),\
	FST::NODE()

#define FST_ID 2,	\
	FST::NODE(105,	\
	FST::RELATION('$', 0),\
	FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0), FST::RELATION('f', 0),\
	FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0),\
	FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0), FST::RELATION('r', 0),\
	FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0),\
	FST::RELATION('y', 0), FST::RELATION('z', 0),\
\
	FST::RELATION('A', 0), FST::RELATION('B', 0), FST::RELATION('C', 0), FST::RELATION('D', 0), FST::RELATION('E', 0), FST::RELATION('F', 0),\
	FST::RELATION('G', 0), FST::RELATION('H', 0), FST::RELATION('I', 0), FST::RELATION('J', 0), FST::RELATION('K', 0), FST::RELATION('L', 0),\
	FST::RELATION('M', 0), FST::RELATION('N', 0), FST::RELATION('O', 0), FST::RELATION('P', 0), FST::RELATION('Q', 0), FST::RELATION('R', 0),\
	FST::RELATION('S', 0), FST::RELATION('T', 0), FST::RELATION('U', 0), FST::RELATION('V', 0), FST::RELATION('W', 0), FST::RELATION('X', 0),\
	FST::RELATION('Y', 0), FST::RELATION('Z', 0),\
\
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1)),\
\
	FST::RELATION('A', 1), FST::RELATION('B', 1), FST::RELATION('C', 1), FST::RELATION('D', 1), FST::RELATION('E', 1), FST::RELATION('F', 1),\
	FST::RELATION('G', 1), FST::RELATION('H', 1), FST::RELATION('I', 1), FST::RELATION('J', 1), FST::RELATION('K', 1), FST::RELATION('L', 1),\
	FST::RELATION('M', 1), FST::RELATION('N', 1), FST::RELATION('O', 1), FST::RELATION('P', 1), FST::RELATION('Q', 1), FST::RELATION('R', 1),\
	FST::RELATION('S', 1), FST::RELATION('T', 1), FST::RELATION('U', 1), FST::RELATION('V', 1), FST::RELATION('W', 1), FST::RELATION('X', 1),\
	FST::RELATION('Y', 1), FST::RELATION('Z', 1),\
	FST::NODE()

#define FST_PLUS 2,	\
	FST::NODE(1, FST::RELATION('+', 1)),\
	FST::NODE()
#define FST_MINUS 2,	\
	FST::NODE(1, FST::RELATION('-', 1)),\
	FST::NODE()
#define FST_STAR 2,	\
	FST::NODE(1, FST::RELATION('*', 1)),\
	FST::NODE()
#define FST_DIR 2,	\
	FST::NODE(1, FST::RELATION('/', 1)),\
	FST::NODE()
#define FST_INTLIT 2,	\
	FST::NODE(20,	\
	FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),\
	FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0), FST::RELATION('0', 0),\
	\
	FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
	FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1)),\
	FST::NODE()

#define FST_FLLIT 2,	\
	FST::NODE(21,	\
	FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0), FST::RELATION('6', 0),\
	FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0), FST::RELATION('0', 0), FST::RELATION('.', 0), \
	FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1), FST::RELATION('5', 1), FST::RELATION('6', 1),\
	FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1), FST::RELATION('.', 1)), \
	FST::NODE()

#define FST_STRLIT 2,	\
	FST::NODE(92,	\
	FST::RELATION('a', 0), FST::RELATION('b', 0), FST::RELATION('c', 0), FST::RELATION('d', 0), FST::RELATION('e', 0), FST::RELATION('f', 0),\
	FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('i', 0), FST::RELATION('j', 0), FST::RELATION('k', 0), FST::RELATION('l', 0),\
	FST::RELATION('m', 0), FST::RELATION('n', 0), FST::RELATION('o', 0), FST::RELATION('p', 0), FST::RELATION('q', 0), FST::RELATION('r', 0),\
	FST::RELATION('s', 0), FST::RELATION('t', 0), FST::RELATION('u', 0), FST::RELATION('v', 0), FST::RELATION('w', 0), FST::RELATION('x', 0),\
	FST::RELATION('y', 0), FST::RELATION('z', 0), FST::RELATION('1', 0), FST::RELATION('2', 0), FST::RELATION('3', 0), FST::RELATION('4', 0),\
	FST::RELATION('5', 0), FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0), FST::RELATION('9', 0), FST::RELATION('0', 0),\
	\
	FST::RELATION(' ', 0), FST::RELATION('.', 0), FST::RELATION(',', 0),\
	FST::RELATION('?', 0), FST::RELATION('!', 0), FST::RELATION(';', 0), FST::RELATION(':', 0), FST::RELATION('-', 0), FST::RELATION(')', 0),\
	FST::RELATION('(', 0), \
	\
	FST::RELATION('a', 1), FST::RELATION('b', 1), FST::RELATION('c', 1), FST::RELATION('d', 1), FST::RELATION('e', 1), FST::RELATION('f', 1),\
	FST::RELATION('g', 1), FST::RELATION('h', 1), FST::RELATION('i', 1), FST::RELATION('j', 1), FST::RELATION('k', 1), FST::RELATION('l', 1),\
	FST::RELATION('m', 1), FST::RELATION('n', 1), FST::RELATION('o', 1), FST::RELATION('p', 1), FST::RELATION('q', 1), FST::RELATION('r', 1),\
	FST::RELATION('s', 1), FST::RELATION('t', 1), FST::RELATION('u', 1), FST::RELATION('v', 1), FST::RELATION('w', 1), FST::RELATION('x', 1),\
	FST::RELATION('y', 1), FST::RELATION('z', 1), FST::RELATION('1', 1), FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),\
	FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1), FST::RELATION('8', 1), FST::RELATION('9', 1), FST::RELATION('0', 1),\
	\
	FST::RELATION(' ', 1), FST::RELATION('.', 1), FST::RELATION(',', 1),\
	FST::RELATION('?', 1), FST::RELATION('!', 1), FST::RELATION(';', 1), FST::RELATION(':', 1), FST::RELATION('-', 1), FST::RELATION(')', 1),\
	FST::RELATION('(', 1)),\
	\
	FST::NODE()

#define FST_LITFALSE 6,	\
	FST::NODE(1, FST::RELATION('f', 1)),\
	FST::NODE(1, FST::RELATION('a', 2)),\
	FST::NODE(1, FST::RELATION('l', 3)),\
	FST::NODE(1, FST::RELATION('s', 4)),\
	FST::NODE(1, FST::RELATION('e', 5)),\
	FST::NODE()

#define FST_LITTRUE 5,	\
	FST::NODE(1, FST::RELATION('t', 1)),\
	FST::NODE(1, FST::RELATION('r', 2)),\
	FST::NODE(1, FST::RELATION('u', 3)),\
	FST::NODE(1, FST::RELATION('e', 4)),\
	FST::NODE()

#define FST_SEMICOLON 2,	\
	FST::NODE(1, FST::RELATION(';', 1)),\
	FST::NODE()

#define FST_COMMA 2,	\
	FST::NODE(1, FST::RELATION(',', 1)),\
	FST::NODE()

#define FST_LEFTBRACE 2,	\
	FST::NODE(1, FST::RELATION('{', 1)),\
	FST::NODE()

#define FST_BRACELET 2,	\
	FST::NODE(1, FST::RELATION('}', 1)),\
	FST::NODE()

#define FST_LEFTTHESIS 2,	\
	FST::NODE(1, FST::RELATION('(', 1)),\
	FST::NODE()

#define FST_RIGHTTHESIS 2,	\
	FST::NODE(1, FST::RELATION(')', 1)),\
	FST::NODE()

#define FST_EQUAL 2,	\
	FST::NODE(1, FST::RELATION('=', 1)),\
	FST::NODE()

namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(
			char c = 0x00,
			short ns = NULL
		);
	};

	struct NODE
	{
		short n_relation;
		RELATION *relations;
		NODE();
		NODE(
			short n,
			RELATION rel,
			...
		);
	};

	struct FST
	{
		char* string;
		short position;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST(
			char* s,
			short ns,
			NODE n,
			...
		);
	};
	bool step(FST& fst, short* &rstates);
	bool execute(FST& fst);
}