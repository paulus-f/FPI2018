#include "stdafx.h"
#include "Parm.h"
#include "Error.h"
namespace Parm {
	PARM getparm(int argc, _TCHAR* argv[])
	{
		if (argc > 1)
		{
			if (wcslen((const wchar_t*)argv[1]) > PARM_MAX_SIZE)
			{
				throw ERROR_THROW(104);
			}
			else if (!wcsstr(argv[1], PARM_IN))
			{
				throw ERROR_THROW(100);
			}
		}
		PARM tempParm; 
		switch (argc)
		{
			case 2: {
				wcsncpy_s(tempParm.in, argv[1] + wcslen(PARM_IN), wcslen(argv[1]) - wcslen(PARM_IN));
				wcscpy_s(tempParm.out, tempParm.in);
				wcscat_s(tempParm.out, PARM_OUT_DEFAULT_EXT);
			
				wcscpy_s(tempParm.log, tempParm.in);
				wcscat_s(tempParm.log, PARM_LOG_DEFAULT_EXT);
				break;
			}
			case 3: {
				if (wcslen(argv[2]) > PARM_MAX_SIZE)
				{
					throw ERROR_THROW(104);
				}
				wcsncpy_s(tempParm.in, argv[1] + wcslen(PARM_IN), wcslen(argv[1]) - wcslen(PARM_IN));
				if (wcsstr(argv[2], PARM_OUT))   
				{
					wcsncpy_s(tempParm.out, argv[2] + wcslen(PARM_OUT), wcslen(argv[2]) - wcslen(PARM_OUT));
					wcscpy_s(tempParm.log, tempParm.in);
					wcscat_s(tempParm.log, PARM_LOG_DEFAULT_EXT);
				}
				else
				{
					wcsncpy_s(tempParm.log, argv[2] + wcslen(PARM_OUT), wcslen(argv[2]) - wcslen(PARM_LOG));
					wcscpy_s(tempParm.out, tempParm.in);
					wcscat_s(tempParm.out, PARM_OUT_DEFAULT_EXT);
				}
				break;
			}
			case 4:{
				wcsncpy(tempParm.in, argv[1] + 4, wcslen(argv[1]) - wcslen(PARM_IN));
				wcsncpy_s(tempParm.out, argv[2] + 5, wcslen(argv[2]) - wcslen(PARM_OUT));
				wcsncpy_s(tempParm.log, argv[3] + 5, wcslen(argv[3]) - wcslen(PARM_LOG));
				break;
			}
			case 1: throw ERROR_THROW(100);break;
		}
		return tempParm;
	}
}