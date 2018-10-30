#include "stdafx.h"
#include <iostream>
#include "iomanip"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "RPN.h"
#include "MFST.h"
#include "SemanticAnalysis.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_ALL, "Russian");
	std::cout << "----------------------------LOG--------------------------------------" << std::endl;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << std::endl;
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE);
		IT::IdTable  idTable = IT::Create(TI_MAXSIZE);
		LT::LexicalAnalysis((char*)in.text, lexTable, idTable, log);
		MFST_TRACE_START
		//char buff[5];
		/*for (int i = 0; i < lexTable.head; ++i)
		{
			std::cout << lexTable.table[i].idxTI << "-------" << lexTable.table[i].lexema[0] << std::endl;
		}*/
		//std::cout << std::endl;
		//MFST::Mfst mfst(lexTable, GRB::getGreibach());
		//
		//if (mfst.start()) std::cout << "Syntaxer is COMPLETE" << std::endl;
		//else std::cout << "ERROR" << std::endl;
		//
		if (Semantic::startSemantic(lexTable, idTable, log)) std::cout << "Semantic is COMPLETE" << std::endl;
		else std::cout << "ERROR" << std::endl;

	/*	if (Polska::doRPNinLexTable(lexTable, idTable))
		{
			std::cout << "ALL POLISH NOTATION IS COMPLETE" << std::endl;
		}
		else
		{
			std::cout << "There is error in POLISH NOTATION" << std::endl;
		};
		LogLA(lexTable, log);
	*/

		/*mfst.savededucation();
		mfst.printrules();
*/
		LT::Delete(lexTable);
		IT::Delete(idTable);
		Log::WriteIn(log, in);
		std::cout << std::endl;
		std::cout << in.text << std::endl;
		std::cout << "------------------------------------------------------------------" << std::endl;
		Log::Close(log);
		In::clearIn(in);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}
