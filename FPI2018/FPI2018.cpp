#include "stdafx.h"
#include <iostream>
#include "iomanip"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "LT.h"
#include "RPN.h"
#include "CodeGeneration.h"
#include "MFST.h"
#include "SemanticAnalysis.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Log::LOG log = Log::INITLOG;
	setlocale(LC_CTYPE, "rus");
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		std::wcout << "-in:" << parm.in << ", -out:" << parm.out << ", -log:" << parm.log << ", -d:" << parm.d << std::endl;
		
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		LT::LexTable lexTable = LT::Create(LT_MAXSIZE);
		IT::IdTable  idTable = IT::Create(TI_MAXSIZE);
		LT::LexicalAnalysis((char*)in.text, lexTable, idTable, log);
		Log::WriteIn(log, in);

		log = Log::getlog(parm.d);
		MFST_TRACE_START
		std::cout << std::endl;
		MFST::Mfst mfst(lexTable, GRB::getGreibach());
		if (mfst.start(log)) std::cout << "Syntaxer is COMPLETE" << std::endl;
		if (!parm.isEmptyD)
		{
			mfst.savededucation();
			mfst.printrules(log);
		}
		else
		{
			std::cout << "ERRORS IN SYNTAXER" << std::endl;
			std::cout << "Look in the file with the extension .d" << std::endl;
			return 0;
		}
		log = Log::getlog(parm.log);
		LT::LogLA(lexTable, log);
		IT::logIT(idTable, log);
		if (Semantic::startSemantic(lexTable, idTable, log)) std::cout << "Semantic is COMPLETE" << std::endl;
		if (Polska::doRPNinLexTable(lexTable, idTable)) std::cout << "ALL POLISH NOTATION IS COMPLETE" << std::endl;
		log = Log::getlog(parm.out);
		CG::StartGeneration(lexTable, idTable, log);
		LT::Delete(lexTable);
		IT::Delete(idTable);
		std::cout << in.text << std::endl;

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
