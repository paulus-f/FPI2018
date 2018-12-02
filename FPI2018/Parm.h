#pragma once
#define PARM_IN L"-in:"
#define PARM_OUT L"-out:"
#define PARM_LOG L"-log:"
#define PARM_D L"-d:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT L".asm"
#define PARM_LOG_DEFAULT_EXT L".log"
#define PARM_D_DEFAULT_EXT L".d"
namespace Parm {
	struct PARM
	{
		wchar_t in[PARM_MAX_SIZE];
		wchar_t out[PARM_MAX_SIZE];
		wchar_t log[PARM_MAX_SIZE];
		wchar_t d[PARM_MAX_SIZE];
		bool isEmptyD = true;
	};

	PARM getparm(int argc, _TCHAR* argv[]);
}; 

