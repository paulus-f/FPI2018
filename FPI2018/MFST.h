#pragma once
#include "stdafx.h"
#include "GRB.h"
#include <stack>
#include "LT.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
typedef std::stack<short> MFSTSTSTACK;
#define MFST_TRACE_START	*log.stream << std::setw( 4) << std::left << " Ўаг" << ':'\
										<< std::setw(20) << std::left << " ѕравило "\
										<< std::setw(30) << std::left << " ¬ходна€ лента"\
										<< std::setw(20) << std::left << " —тек" << std::endl;


namespace MFST
{
	struct MfstState				// состо€ние автомата (дл€ сохранени€)
	{
		short lenta_position;		// позици€ на ленте
		short nrulechain;			// номер текущего правила
		short nrule;				// номер текущей цепочки текущего правила
		MFSTSTSTACK st;				// стек автомата
		MfstState();
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain);
		MfstState(
			short pposition,       // позици€ на ленте
			MFSTSTSTACK pst,       // стек автомата
			short pnrule,          // номер текущего правила
			short pnrulechain      // номер текущей цепочки
		);
	};

	struct Mfst
	{

		enum RC_STEP {						// код возврата функции step
			NS_OK,					// найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,				// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,			// не найдена подход€ща€ цепочка правила (ошибка в исходном коде)
			NS_ERROR,				// неизвестный нетерминальный символ грамматики
			TS_OK,					// тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,					// тек. символ ленты != вершине стека, восстановлено состо€ние 
			LENTA_END,				// текуща€ позици€ ленты >= lenta_size
			SURPRISE				// неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis		 // диагностика
		{
			short lenta_position;			// позици€ на ленте
			RC_STEP rc_step;				// код завершени€ шага
			short nrule;					// номер правила
			short nrule_chain;				// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(			 // диагностика
				short plenta_position,	// позици€ на ленте
				RC_STEP prc_step,		// код завершени€ шага
				short pnrule,			// номер правила 
				short pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		int FST_TRACE_n = 0;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lexTable;
		MFSTSTSTACK st;
		std::stack<MfstState> storestate;
		Mfst();
		Mfst(LT::LexTable& lexTable, GRB::Greibach pgrebach);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate(Log::LOG log);
		bool restate(Log::LOG log);
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step(Log::LOG log);
		bool start(Log::LOG log);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules(Log::LOG log);

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; }
		} deducation;
		bool savededucation();
	};
}
