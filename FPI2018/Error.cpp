#include "stdafx.h"
#include "Error.h"
#include "Log.h"
namespace Error {
	ERROR errors[ERROR_MAX_ENTRY] = 
	{
		ERROR_ENTRY(0, "Недоступный код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"), 
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышега длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка лексического анализатора"),
		ERROR_ENTRY(114, "Имя идентификатора превышен максимального значения"),
		ERROR_ENTRY(115, "Больше одной точки входа 'main' "),
		ERROR_ENTRY(116, "Строка не закртыта"),
		ERROR_ENTRY(117, "Переменная не объявлена"),
		ERROR_ENTRY(118, "Пустая строка"),
		ERROR_ENTRY(119, "Неверный литерал строки"),
		ERROR_ENTRY(120, "Неоткрывающиеся блок кода"),
		ERROR_ENTRY_NODEF10(130),ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200),ERROR_ENTRY_NODEF100(300),ERROR_ENTRY_NODEF100(400),ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "Неверная структура программы"),
		ERROR_ENTRY(601, "Ошибка в операторе"),
		ERROR_ENTRY(602, "Ошибка в выражение"),
		ERROR_ENTRY(603, "Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(700, "Ошибка семантическом анализаторе"),
		ERROR_ENTRY(701, "Не соответствуют типы при сравнение"),
		ERROR_ENTRY(702, "Не возращает нужный тип"),
		ERROR_ENTRY(703, "Не соответствуют типы в операции присваивание"),
		ERROR_ENTRY(704, "Не соответствуют типы в параметрах функции или перебор параметров"),
		ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};
	
	ERROR geterror(int id)
	{
		if (id > ERROR_MAX_ENTRY)
		{	
			return errors[0];
		}
		else
		{
			return errors[id];
		}
	}
	ERROR geterrorin(int id, int line, int col)
	{
		ERROR temp; 
		if (id > ERROR_MAX_ENTRY)
		{
			temp = errors[0];
			return temp;
		}
		else
		{
			temp = errors[id];
			temp.inext.col = col;
			temp.inext.line = line;
			return temp;
		}
	}

	ERROR getarrayerror(ERROR errorarr[], Log::LOG log, int mainId, int size)
	{
		ERROR temp;

		for (int i = 0; i < size; i++)
		{
			Log::WriteError(log, errorarr[i]);
		}

		if (mainId > ERROR_MAX_ENTRY)
		{
			temp = errors[0];
			return temp;
		}
		else
		{
			temp = errors[mainId];
			return temp;
		} 
	}
}