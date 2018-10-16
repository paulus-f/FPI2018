#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include "In.h"
#include "Error.h"


namespace In {
IN getin(wchar_t infile[])
	{
		IN tempIN;
		
		tempIN.size = 0;
		tempIN.lines = 0;
		std::ifstream fin;
		std::string Buff;
		unsigned char *textTemp = new unsigned char[IN_MAX_LEN_TEXT];
		tempIN.ignor = 0;
		fin.open(infile);
		if (fin.fail())
		{
			throw ERROR_THROW(110);
		}
		for (int t = 0;;)
		{	
			getline(fin, Buff);

			for (int i = 0; i < Buff.length(); ++i)
			{
				if (tempIN.code[(unsigned char)Buff[i]] == IN::F)
				{
					throw ERROR_THROW_IN(111, tempIN.lines, i);
				}
				else if (tempIN.code[(unsigned char)Buff[i]] == IN::I)
				{
					tempIN.ignor++;
				}
				else
				{
					tempIN.size++;
					textTemp[t] = Buff[i];
					++t;
				}
			}
			tempIN.lines++;
			textTemp[t++] = '\n';
			tempIN.size++;
			if (fin.eof())
			{
				tempIN.lines--;
				textTemp[t] = '\0';
				break;
			}
		}
		tempIN.text = textTemp;
		fin.close();
		return tempIN;
	}

	void clearIn(IN in)
	{
		delete in.text;
	}

}
