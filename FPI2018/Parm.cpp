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
			case 3: {
				wcsncpy_s(tempParm.in, argv[1] + wcslen(PARM_IN), wcslen(argv[1]) - wcslen(PARM_IN));
				wcscpy_s(tempParm.out, tempParm.in);
				wcscat_s(tempParm.out, PARM_OUT_DEFAULT_EXT);
				wcscpy_s(tempParm.log, tempParm.in);
				wcscat_s(tempParm.log, PARM_LOG_DEFAULT_EXT);
				wcsncpy_s(tempParm.d, argv[2] + wcslen(PARM_D), wcslen(argv[2]) - wcslen(PARM_D));
				if (wcslen(argv[2]) - wcslen(PARM_D) != 0)
				{
					tempParm.isEmptyD = false;
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}
				else
				{
					wcscpy_s(tempParm.d, tempParm.in);
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}
				break;
			}
			case 4: {
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
				wcsncpy_s(tempParm.d, argv[3] + wcslen(PARM_D), wcslen(argv[3]) - wcslen(PARM_D));
				if (wcslen(argv[2]) - wcslen(PARM_D) != 0)
				{
					tempParm.isEmptyD = false;
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}
				else
				{
					wcscpy_s(tempParm.d, tempParm.in);
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}

				break;
			}
			case 5:{
				wcsncpy(tempParm.in, argv[1] + 4, wcslen(argv[1]) - wcslen(PARM_IN));
				wcsncpy_s(tempParm.out, argv[2] + 5, wcslen(argv[2]) - wcslen(PARM_OUT));
				wcsncpy_s(tempParm.log, argv[3] + 5, wcslen(argv[3]) - wcslen(PARM_LOG));
				wcsncpy_s(tempParm.d, argv[4] + wcslen(PARM_D), wcslen(argv[4]) - wcslen(PARM_D));
				if (wcslen(argv[2]) - wcslen(PARM_D) != 0)
				{
					tempParm.isEmptyD = false;
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}
				else
				{
					wcscpy_s(tempParm.d, tempParm.in);
					wcscat_s(tempParm.d, PARM_D_DEFAULT_EXT);
				}
				break;
			}
			case 1: throw ERROR_THROW(100);break;
			case 2: throw ERROR_THROW(100); break;
		}
		return tempParm;
	}
}