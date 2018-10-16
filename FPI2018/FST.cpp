#include "stdafx.h"
#include "FST.h"
#include <iostream>
#include "Error.h"
#include "LT.h"
#include "IT.h"

FST::NODE::NODE()
	{
		n_relation = 0;
		RELATION *relations = NULL; 
	}

FST::NODE::NODE(short n, RELATION rel, ...)
{
	n_relation = n;
	RELATION *ptrrel = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; ++i)
		relations[i] = ptrrel[i]; 
}

FST::RELATION::RELATION(char c, short nn)
{
	symbol = c;
	nnode = nn;
}

FST::FST::FST(char *s, short ns, NODE n, ...)
{
	string = s;
	nstates = ns;
	nodes = new NODE[ns];
	NODE *ptrn = &n;
	for (int i = 0; i < ns; ++i) nodes[i] = ptrn[i];
	rstates = new short[nstates];
	memset(rstates, 0xff, sizeof(short)*nstates);
	rstates[0] = 0;
	position = -1;
}

bool FST::execute(FST & fst)
{
	short* rstates = new short[fst.nstates];
	memset(rstates, 0xff, sizeof(short)*fst.nstates);
	short lstring = strlen(fst.string);
	bool rc = true;
	for (short i = 0; i < lstring && rc; ++i)
	{
		fst.position++;
		rc = step(fst, rstates);
	}
	delete[] rstates;
	return (rc?(fst.rstates[fst.nstates-1] == lstring):rc);
}



bool FST::step(FST& fst, short* &rstates)
{
	bool rc = false;
	std::swap(rstates, fst.rstates);
	for (short i = 0; i < fst.nstates; i++)
	{
		if(rstates[i] == fst.position)
			for (short j = 0; j < fst.nodes[i].n_relation; ++j)
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
				{
					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}
			}
	}
	return rc;
}

