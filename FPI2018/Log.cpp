#include "stdafx.h"
#include "Log.h"
#include "Error.h"
#include <fstream>
#include <ctime>

namespace Log {
	LOG getlog(wchar_t  logfile[])
	{
		LOG tempLog;
		std::ofstream *fout = new std::ofstream;
		fout->open(logfile);
		tempLog.stream = fout; 
		for (int i = 0; i < wcslen(logfile); ++i)
		{
			tempLog.logfile[i] = logfile[i];
		}
		tempLog.logfile[wcslen(logfile)] = '\0';
		
		if (fout->fail())
		{
			throw ERROR_THROW(112)
		}
		return tempLog;
	}


	void WriteLine(LOG log,  char *c, ...)
	{
		char **ptr = &c;
		for (; **ptr != *"";)
		{
			*log.stream << *ptr;
			ptr++;
		}
		
	}
	void WriteLine(LOG log, wchar_t *c, ...)
	{
		wchar_t **ptr = &c;
		char Buff[300];
		for (;**ptr != *"";)
		{
			wcstombs(Buff, *ptr, 300);
			*(log.stream) << Buff;
			ptr++;
		}
	}
	void WriteLog(LOG log)
	{
		time_t rawtime;
		struct tm * timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		*log.stream << "\n---Протокол--- Дата: "<< asctime(timeinfo) << std::endl;
	}
	void WriteParm(LOG log, Parm::PARM  parm)
	{
		char buff[300];
		*log.stream << "---Параметры--- " << std::endl;
		wcstombs(buff, parm.in, 300);
		*log.stream << "-in: " << buff << std::endl;
		wcstombs(buff, parm.out, 300);
		*log.stream << "-out: " << buff << std::endl;
		wcstombs(buff, parm.log, 300);
		*log.stream << "-log: "<< buff << std::endl;
	}
	void WriteIn(LOG log, In::IN in)
	{
		*log.stream << "---Исходные данные--- " << std::endl;
		*log.stream << "Sym: " << in.size << std::endl;
		*log.stream << "Ignor: " << in.ignor << std::endl;
		*log.stream << "Lines: " << in.lines << std::endl;
	}
	void WriteError(LOG log, Error::ERROR error)
	{
		*log.stream << "ID: " << error.id << " Message: " <<  error.message << " Col: " << error.inext.col << " Line: " << error.inext.line << std::endl;
	}
	void Close(LOG log)
	{
		log.stream->close();
	}
}
